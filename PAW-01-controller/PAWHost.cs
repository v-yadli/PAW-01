using System;
using System.Threading;
using System.Linq;
using System.Linq.Expressions;
using System.IO.Ports;
using System.Runtime.InteropServices;
using WindowsInput;
using WindowsInput.Native;
using Sanford.Multimedia;
using Sanford.Multimedia.Midi;

namespace YadliTechnology.PAW01
{
    enum MouseButton : Int32
    {
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2,
    }
    class PAWHost
    {
        static volatile int mx = 0, my = 0;
        const int DEADZONE = 15;
        const double MAXZONE = 110.0;
        static InputSimulator simulator;
        static OutputDevice midiout;
        static volatile bool stopped;
        static int octave = 0;

        static void Main(string[] args)
        {
            Console.WriteLine("PAW-01 Signal Converter Host, v0.1");
            stopped = false;

            Console.WriteLine("Opening controller port...");
            SerialPort controllerPort = new SerialPort("COM127", 250000);
            controllerPort.ReadTimeout = 1000;
            controllerPort.Open();
            Console.WriteLine("Opening keyboard port...");
            SerialPort keyboardPort = new SerialPort("COM255", 250000);
            keyboardPort.ReadTimeout = 1000;
            keyboardPort.Open();
            Console.WriteLine("Opening Midi output port...");
            midiout = new OutputDevice(1);
            Console.WriteLine("Opening input simulator...");
            simulator = new InputSimulator();

            Console.WriteLine("Initializing mouse...");
            Thread mouseProc = new Thread(MouseProc);
            mouseProc.Start(null);

            Console.WriteLine("Initializing keyboard...");
            Thread keyboardProc = new Thread(KeyboardProc);
            keyboardProc.Start(keyboardPort);

            Console.WriteLine("Initializing controller...");
            Thread controllerProc = new Thread(ControllerProc);
            controllerProc.Start(controllerPort);

            Console.WriteLine("PAW-01 Host started. Press anykey to pause...");
            Console.ReadKey();
            Console.WriteLine("PAW-01 Host shutting down...");
            stopped = true;

            midiout.Close();
            midiout.Dispose();

            mouseProc.Join();
            keyboardProc.Join();
            controllerProc.Join();
            Console.WriteLine("Processors offline.");
            keyboardPort.Close();
            controllerPort.Close();
            Console.WriteLine("Ports offline.");

            Console.WriteLine("PAW-01 Host paused. Press anykey to restart...");
            Console.ReadKey();
            Main(args);
        }

        private static void KeyboardProc(object state)
        {
            var serialPort = (SerialPort)state;
            while (true)
            {
                if(stopped)return;

                string content = "";
                try{ content = serialPort.ReadLine(); }catch{continue;}
                System.Console.WriteLine(content);
                var split = content.Split(',', StringSplitOptions.RemoveEmptyEntries).Select(_ => _.Trim()).ToArray();
                switch (split[0])
                {
                    case "KON":
                    KeyOn(ParseArgs(split));
                    break;
                    case "KOFF":
                    KeyOff(ParseArgs(split)[0]);
                    break;
                }
            }
        }

// http://tonalsoft.com/pub/pitch-bend/pitch.2005-08-31.17-00.aspx
// The General MIDI specification assigns the number 69 to A440
// That is, Key 69 = AM37 Key 16, at OCT=0
        private static int AM37toMidiNote(int key)
        {
            return (key - 16 + 69) + 12 * octave;
        }

        private static int AM37toMidiVelocity(int v)
        {
            // return 90;
            v = Math.Max(0, Math.Min(80, v));
            return 110 - v;
            // double val = (127-v) / 127.0f;
            // val = Math.Pow(val, 2);
            // return (int)(val * 127.0f * 2);
        }

        private static void KeyOff(int k)
        {
            var msg = new ChannelMessage(ChannelCommand.NoteOff, 0, AM37toMidiNote(k));
            midiout.Send(msg);
        }

        private static void KeyOn(int[] v)
        {
            var msg = new ChannelMessage(ChannelCommand.NoteOn, 0, AM37toMidiNote(v[0]), AM37toMidiVelocity(v[1]));
            midiout.Send(msg);
        }

        private static void ControllerProc(object state)
        {
            var serialPort = (SerialPort)state;
            while (true)
            {
                if(stopped)return;

                string content = "";
                try{ content = serialPort.ReadLine(); }catch{continue;}
                var split = content.Split(',', StringSplitOptions.RemoveEmptyEntries).Select(_ => _.Trim()).ToArray();
                switch (split[0])
                {
                    case "VLD":
                        VolumeUp();
                        break;
                    case "VLU":
                        VolumeDown();
                        break;
                    case "VLM":
                        VolumeMute();
                        break;
                    case "XY":
                        XY(ParseArgs(split));
                        break;
                    case "XY_PUSH":
                        XY_PEDAL(true);
                        break;
                    case "XY_RELEASE":
                        XY_PEDAL(false);
                        break;
                    case "MM":
                        MouseMove(ParseArgs(split));
                        break;
                    case "MP":
                        MousePress(ParseArgs(split), true);
                        break;
                    case "MR":
                        MousePress(ParseArgs(split), false);
                        break;
                    case "OCU":
                        OctaveShift(1);
                        break;
                    case "OCD":
                        OctaveShift(-1);
                        break;
                    case "OCR":
                        octave=0;
                        break;
                    case "KEY_UP":
                        simulator.Keyboard.KeyPress(VirtualKeyCode.UP);
                        break;
                    case "KEY_DOWN":
                        simulator.Keyboard.KeyPress(VirtualKeyCode.DOWN);
                        break;
                    case "KEY_ENTER":
                        simulator.Keyboard.KeyPress(VirtualKeyCode.RETURN);
                        break;
                    case "MEDIA_PREV":
                        MediaPrev();
                        break;
                    case "MEDIA_PLAY":
                        MediaPlay();
                        break;
                    case "MEDIA_NEXT":
                        MediaNext();
                        break;
                }
            }
        }

        private static void XY_PEDAL(bool on)
        {
            ChannelMessage msg = new ChannelMessage(ChannelCommand.Controller, 0, 64, on? 127:0);
            midiout.Send(msg);
        }

        // http://sites.uci.edu/camp2014/2014/04/30/managing-midi-pitchbend-messages/
        // PITCH LSB MSB, 7bit (0-127) each, summing up to 0~16383
        // http://www.indiana.edu/~emusic/cntrlnumb.html
        // controller table
        private static void XY(int[] v)
        {
            double x = (v[0] + 512) / 1024.0;
            double y = (v[1]) / 1024.0;

            int ix = (int)(x * 16384);
            int lsb = ix % 128;
            int msb = ix / 128;

            ChannelMessage msgx = new ChannelMessage(ChannelCommand.PitchWheel, 0, lsb, msb);
            midiout.Send(msgx);

            ChannelMessage msgy;
            if(y >= 0.0)
            {
                int mody = (int)(y * 254);
                msgy = new ChannelMessage(ChannelCommand.Controller, 0, 1, mody); //mod
            }else{
                int c = (int)(y * -254);
                msgy = new ChannelMessage(ChannelCommand.Controller, 0, 2, c); //2=breath
                // msgy = new ChannelMessage(ChannelCommand.Controller, 0, 84, c); //84=porta control
            }
            midiout.Send(msgy);
        }

        private static void MouseProc(object state)
        {
            while(true)
            {
                if(stopped)return;

                Thread.Sleep(10);
                if (Math.Abs(mx) < DEADZONE && Math.Abs(my) < DEADZONE) continue;
                double len = Math.Sqrt(Math.Pow(mx, 2) + Math.Pow(my, 2));
                double dx = Math.Abs(mx) / len;
                double dy = Math.Abs(my) / len;

                dx = Math.Pow(dx, 2);
                dy = Math.Pow(dy, 2);
                len = Math.Min(len, MAXZONE) / MAXZONE * 4;
                simulator.Mouse.MoveMouseBy((int)(dx * len * Math.Sign(mx)), (int)(dy * len * Math.Sign(my)));
            }
        }

        private static int[] ParseArgs(string[] split)
        {
            return split.Skip(1).Select(Int32.Parse).ToArray();
        }

        private static void OctaveShift(int offset)
        {
            octave += offset;
            System.Console.WriteLine($"octave = {octave}");
            //TODO range check
        }

        private static void MediaPrev()
        {
            simulator.Keyboard.KeyPress(VirtualKeyCode.MEDIA_PREV_TRACK);
        }

        private static void MediaPlay()
        {
            simulator.Keyboard.KeyPress(VirtualKeyCode.MEDIA_PLAY_PAUSE);
        }

        private static void MediaNext()
        {
            simulator.Keyboard.KeyPress(VirtualKeyCode.MEDIA_NEXT_TRACK);
        }

        private static void MousePress(int[] v, bool isPress)
        {
            MouseButton mb = (MouseButton)v[0];
            // MouseEvent e = MouseEvent.MOUSEEVENTF_LEFTDOWN;
            switch (mb)
            {
                case MouseButton.LEFT:
                    if(isPress) simulator.Mouse.LeftButtonDown();
                    else simulator.Mouse.LeftButtonUp();
                    break;
                case MouseButton.MIDDLE:
                    if(isPress) simulator.Mouse.XButtonDown(2);
                    else simulator.Mouse.XButtonUp(2);
                    break;
                case MouseButton.RIGHT:
                    if(isPress) simulator.Mouse.RightButtonDown();
                    else simulator.Mouse.RightButtonUp();
                    break;
            }
        }
        private static void MouseMove(int[] v)
        {
            bool isWheel = v[2] != 0;
            int x = v[0];
            int y = v[1];

            if (!isWheel)
            {
                mx = x;
                my = y;
            }
            else
            {
                simulator.Mouse.VerticalScroll(y);
            }
        }

        private static void VolumeUp()
        {
            simulator.Keyboard.KeyPress(VirtualKeyCode.VOLUME_UP);
        }

        private static void VolumeDown()
        {
            simulator.Keyboard.KeyPress(VirtualKeyCode.VOLUME_DOWN);
        }

        private static void VolumeMute()
        {
            simulator.Keyboard.KeyPress(VirtualKeyCode.VOLUME_MUTE);
        }
    }
}
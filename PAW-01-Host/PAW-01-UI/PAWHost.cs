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
    public static class PAWHost
    {
        static volatile int mx = 0, my = 0;
        const double MAXZONE = 512;
        static InputSimulator simulator;
        static OutputDevice midiout;
        static InputDevice midiin;
        static volatile bool stopped;
        static int octave = 0;
        private static readonly char[] s_split = new char[] { ',' };

        public static event Action ControllerConnected = delegate{ };

        public static void Start()
        {
            Log.WriteLine("PAW-01 Signal Converter Host, v0.1");
            stopped = false;

            Log.WriteLine("Opening controller port...");
            controllerPort = new SerialPort("COM127", 250000);
            controllerPort.ReadTimeout = 1000;
            controllerPort.Open();
            Log.WriteLine("Opening keyboard port...");
            keyboardPort = new SerialPort("COM255", 250000);
            keyboardPort.ReadTimeout = 1000;
            keyboardPort.Open();
            Log.WriteLine("Opening Midi output port...");
            midiout = new OutputDevice(1);
            Log.WriteLine("Opening Midi input port...");
            midiin = new InputDevice(1);
            midiin.ChannelMessageReceived += (o, e) => MidiInHandler(e.Message);
            midiin.StartRecording();
            Log.WriteLine("Opening input simulator...");
            simulator = new InputSimulator();

            Log.WriteLine("Initializing mouse...");
            mouseProc = new Thread(MouseProc);
            mouseProc.Start(null);

            Log.WriteLine("Initializing keyboard...");
            keyboardProc = new Thread(KeyboardProc);
            keyboardProc.Start(keyboardPort);

            Log.WriteLine("Initializing controller...");
            controllerProc = new Thread(ControllerProc);
            controllerProc.Start(controllerPort);

            Log.WriteLine("PAW-01 Host started.");
        }

        internal static void SetSettings(int menu_mode, int dial_mode, int joy_mode, int mon_mode)
        {
            lock(controllerPort)
            {
                byte[] buffer = new byte[]{ 0x03, (byte)menu_mode, (byte)dial_mode, (byte)joy_mode, (byte)mon_mode, (byte)'\n' };
                controllerPort.Write(buffer, 0, buffer.Length);
            }
        }

        internal static void GetSettings(out int menu_mode, out int dial_mode, out int joy_mode, out int mon_mode)
        {
            lock(controllerPort)
            {
                byte[] buffer = new byte[]{ 0x02, (byte)'\n' };
                controllerPort.Write(buffer, 0, buffer.Length);
                var s = controllerPort.ReadLine();
                var cols = s.Split(',');
                if (cols[0] != "SETTING") throw new InvalidOperationException("PAW-01 controller Wrong response");
                menu_mode = int.Parse(cols[1]);
                dial_mode = int.Parse(cols[2]);
                joy_mode = int.Parse(cols[3]);
                mon_mode = int.Parse(cols[4]);
            }
        }

        public static void Stop()
        {
            Log.WriteLine("PAW-01 Host shutting down...");
            stopped = true;

            lock (keyboardPort)
            {
                midiin.StopRecording();
                midiin.Close();
                midiin.Dispose();
                midiout.Close();
                midiout.Dispose();
            }

            mouseProc.Join();
            keyboardProc.Join();
            controllerProc.Join();
            Log.WriteLine("Processors offline.");
            keyboardPort.Close();
            controllerPort.Close();
            Log.WriteLine("Ports offline.");
        }

        private static void MidiInHandler(ChannelMessage msg)
        {
            if(!stopped && msg.Command == ChannelCommand.Controller)
            {
                lock (controllerPort)
                {
                    try
                    {
                        byte[] val = new byte[] { 0x01, (byte)msg.Data1, (byte)msg.Data2, (byte)'\n'};
                        Log.WriteLine($"CC Out {msg.Data1}, {msg.Data2}");
                        controllerPort.Write(val, 0, 4);
                    }
                    catch { }
                }
            }
            /*
            lock (keyboardPort)
            {
                if (stopped) return;
                try
                {
                    byte[] val = new byte[] { 0x01, 0x00, (byte)(msg.Data2 * 2),0x00, 0x00, (byte)'\n' };
                    switch (msg.Command)
                    {
                        case ChannelCommand.Controller:
                            if (msg.Data1 == 102)
                            {
                                Log.WriteLine(msg.Data2 * 2);
                                keyboardPort.Write(val, 0, 6);
                                keyboardPort.Write(val, 0, 6);
                            }
                            else if (msg.Data1 == 103)
                            {
                                Log.WriteLine(msg.Data2 * 2);
                                val[1] = 0x01;
                                keyboardPort.Write(val, 0, 6);
                                keyboardPort.Write(val, 0, 6);
                            }
                            break;
                    }
                }
                catch { }
            }
            */
        }

        private static void KeyboardProc(object state)
        {
            var serialPort = (SerialPort)state;
            while (true)
            {
                if (stopped) return;

                string content = "";
                lock (serialPort)
                {
                    try { content = serialPort.ReadLine(); } catch { continue; }
                }
                try
                {
                    var split = content.Split(s_split, StringSplitOptions.RemoveEmptyEntries).Select(_ => _.Trim()).ToArray();
                    switch (split[0])
                    {
                        case "INFO":
                            Log.WriteLine(content);
                            break;
                        case "KON":
                            KeyOn(ParseArgs(split));
                            break;
                        case "KOFF":
                            KeyOff(ParseArgs(split)[0]);
                            break;
                        case "CC":
                            CC(ParseArgs(split));
                            break;
                    }

                }
                catch (Exception)
                {
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

        private static int[] CC_TABLE = new[] { 104, 105, 106, 107 };
        private static bool AfterTouch_On = false;
        private static SerialPort keyboardPort;
        private static SerialPort controllerPort;
        private static Thread controllerProc;
        private static Thread keyboardProc;
        private static Thread mouseProc;

        private static void CC(int[] v)
        {
            // if(v[0] > 1) return;
            int cc = CC_TABLE[v[0]];
            int val = v[1];
            ChannelMessage msg = null;
            // Log.WriteLine($"{cc},{val}");
            if (cc == 107)
            { // aftertouch pin
                val = 128 - val / 8;
                if (val < 32)
                {
                    val = 0;
                    if (!AfterTouch_On) return;
                    AfterTouch_On = false;
                }
                AfterTouch_On = true;
                msg = new ChannelMessage(ChannelCommand.ChannelPressure, 0, val);
                midiout.Send(msg);
            }
            //else
            //{
            //    val = val / 8;
            //    msg = new ChannelMessage(ChannelCommand.Controller, 0, cc, val);
            //}
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
                if (stopped) return;

                string content = "";
                try { lock (serialPort) { content = serialPort.ReadLine(); } } catch { continue; }
                var split = content.Split(s_split, StringSplitOptions.RemoveEmptyEntries).Select(_ => _.Trim()).ToArray();
                switch (split[0])
                {
                    case "START":
                        Log.WriteLine("PAW-01 controller connected.");
                        ControllerConnected();
                        break;
                    case "INFO":
                        Log.WriteLine(content);
                        break;
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
                    case "DMP":
                        simulator.Keyboard.KeyPress(VirtualKeyCode.TAB);
                        break;
                    case "DML":
                        simulator.Mouse.RightButtonClick();
                        break;
                    case "OCR":
                        octave = 0;
                        break;
                    case "KEY_K1":
                        simulator.Keyboard.KeyPress(VirtualKeyCode.UP);
                        break;
                    case "KEY_K2":
                        simulator.Keyboard.KeyPress(VirtualKeyCode.DOWN);
                        break;
                    case "KEY_K3":
                        simulator.Keyboard.KeyPress(VirtualKeyCode.RETURN);
                        break;
                    case "KEY_K4":
                        simulator.Keyboard.KeyPress(VirtualKeyCode.TAB);
                        break;
                    case "KEY_K5":
                        simulator.Keyboard.KeyPress(VirtualKeyCode.DOWN);
                        break;
                    case "KEY_K6":
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
            ChannelMessage msg = new ChannelMessage(ChannelCommand.Controller, 0, 64, on ? 127 : 0);
            midiout.Send(msg);
        }

        // http://sites.uci.edu/camp2014/2014/04/30/managing-midi-pitchbend-messages/
        // PITCH LSB MSB, 7bit (0-127) each, summing up to 0~16383
        // http://www.indiana.edu/~emusic/cntrlnumb.html
        // controller table
        private static void XY(int[] v)
        {
            double x = (v[0] + 520) / 1024.0;
            double y = (v[1]) / 1024.0;

            int ix = (int)(x * 16384);
            int lsb = ix % 128;
            int msb = ix / 128;

            ChannelMessage msgx = new ChannelMessage(ChannelCommand.PitchWheel, 0, lsb, msb);
            midiout.Send(msgx);

            ChannelMessage msgy;
            if (y >= 0.0)
            {
                int mody = (int)(y * 254);
                if (mody < 0) mody = 0;
                if (mody > 127) mody = 127;
                msgy = new ChannelMessage(ChannelCommand.Controller, 0, 1, mody); //mod
            }
            else
            {
                int c = (int)(y * -254);
                if (c < 0) c = 0;
                if (c > 127) c = 127;
                msgy = new ChannelMessage(ChannelCommand.Controller, 0, 2, c); //2=breath
                // msgy = new ChannelMessage(ChannelCommand.Controller, 0, 84, c); //84=porta control
            }
            midiout.Send(msgy);
        }

        private static void MouseProc(object state)
        {
            double accel = 0.0;
            double _dx = 0.0; double _dy = 0.0;
            double a = 0.55;
            double base_speed = 3.0;
            double accel_max = 7.0;
            double accel_incr = 0.05;
            while (true)
            {
                if (stopped) return;

                Thread.Sleep(10);

                //  Project the Rectangular X-Y range to Circular.

                double len = Math.Sqrt(Math.Pow(mx, 2) + Math.Pow(my, 2));
                double dx = Math.Abs(mx) / len;
                double dy = Math.Abs(my) / len;

                //   Now, (dx, dy) falls on the circle of R=1
                //   Update len to normalize it according to the angle
                double k = Math.Sqrt(1 + Math.Pow(Math.Min(dx, dy), 2));
                len = Math.Min(len, MAXZONE) / MAXZONE;
                len = len / k; // normalized
                len = Math.Pow(20, len) / 20.0;
                len = len * (base_speed + accel);



                if (len > 0.97)
                {
                    accel = Math.Min(accel + accel_incr, accel_max);
                }
                else
                {
                    accel = Math.Max(accel - 1, 0.0);
                }

                if (mx == 0 && my == 0) continue;

                dx = _dx * a + dx * (1.0 - a);
                dy = _dy * a + dy * (1.0 - a);
                _dx = dx;
                _dy = dy;

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
            Log.WriteLine($"octave = {octave}");
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
                    if (isPress) simulator.Mouse.LeftButtonDown();
                    else simulator.Mouse.LeftButtonUp();
                    break;
                case MouseButton.MIDDLE:
                    if (isPress) simulator.Mouse.XButtonDown(2);
                    else simulator.Mouse.XButtonUp(2);
                    break;
                case MouseButton.RIGHT:
                    if (isPress) simulator.Mouse.RightButtonDown();
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
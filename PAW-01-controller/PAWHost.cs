using System;
using System.Threading;
using System.Linq;
using System.Linq.Expressions;
using System.IO.Ports;
using System.Runtime.InteropServices;
using WindowsInput;
using WindowsInput.Native;

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
        static InputSimulator simulator = new InputSimulator();

        static void Main(string[] args)
        {
            SerialPort serialPort = new SerialPort("COM5", 250000);
            Timer timer = new Timer(MouseProc, null, 0, 15);
            serialPort.Open();
            while (true)
            {
                string content = serialPort.ReadLine();
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
                    case "MM":
                        MouseMove(ParseArgs(split));
                        break;
                    case "MP":
                        MousePress(ParseArgs(split), true);
                        break;
                    case "MR":
                        MousePress(ParseArgs(split), false);
                        break;
                }
            }
        }

        private static void MouseProc(object state)
        {
            if (Math.Abs(mx) < DEADZONE && Math.Abs(my) < DEADZONE) return;
            double len = Math.Sqrt(Math.Pow(mx, 2) + Math.Pow(my, 2));
            double dx = Math.Abs(mx) / len;
            double dy = Math.Abs(my) / len;

            dx = Math.Pow(dx, 2);
            dy = Math.Pow(dy, 2);
            len = Math.Min(len, MAXZONE) / MAXZONE * 4;
            simulator.Mouse.MoveMouseBy((int)(dx * len * Math.Sign(mx)), (int)(dy * len * Math.Sign(my)));
        }

        private static int[] ParseArgs(string[] split)
        {
            return split.Skip(1).Select(Int32.Parse).ToArray();
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
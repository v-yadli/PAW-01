using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using YadliTechnology.PAW01;

namespace YadliTechnology
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        System.Windows.Forms.NotifyIcon m_icon;
        ControlPanel m_win;

        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);
            m_win = new ControlPanel();

            Log.LogWritten += m_win.LogWritten;
            PAWHost.ControllerConnected += PAWHost_ControllerConnected;
            PAWHost.Start();

            m_icon = new System.Windows.Forms.NotifyIcon();
            m_icon.Icon = new System.Drawing.Icon("reason.ico");
            m_icon.Visible = true;
            m_icon.MouseClick += TrayIconMouseClick;

            SetSettings();
        }

        private void PAWHost_ControllerConnected()
        {
            SetSettings();
        }

        private void TrayIconMouseClick(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            m_win.Show();
        }

        protected override void OnExit(ExitEventArgs e)
        {
            base.OnExit(e);
            m_icon.Visible = false;
            m_icon.Dispose();
            PAW01.PAWHost.Stop();
        }

        public static void SetSettings()
        {
            var s = PAWSetting.Default;
            s.Reload();
            PAW01.PAWHost.SetSettings(s.menu_mode, s.dial_mode, s.joy_mode, s.mon_mode, s.aftertouch_threshold);
            Log.WriteLine("Settings set to the controller.");
        }

        public static void GetSettings()
        {
            var s = PAWSetting.Default;
            int menu_mode, dial_mode, joy_mode, mon_mode, aftertouch_threshold;
            try
            {
                PAW01.PAWHost.GetSettings(out menu_mode, out dial_mode, out joy_mode, out mon_mode, out aftertouch_threshold);
                s.menu_mode = menu_mode;
                s.dial_mode = dial_mode;
                s.joy_mode = joy_mode;
                s.mon_mode = mon_mode;
                s.aftertouch_threshold = aftertouch_threshold;
                s.Save();
                Log.WriteLine("Settings loaded from the controller.");
            }
            catch(Exception ex)
            {
                Log.WriteLine(ex.ToString());
            }
        }
    }
}

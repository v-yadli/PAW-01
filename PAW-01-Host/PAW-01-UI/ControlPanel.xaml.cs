using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using MahApps.Metro.Controls;
using YadliTechnology.PAW01;

namespace YadliTechnology
{
    /// <summary>
    /// Interaction logic for ControlPanel.xaml
    /// </summary>
    public partial class ControlPanel
    {
        int logcnt_ = 0;

        public ControlPanel()
        {
            InitializeComponent();
        }

        internal void LogWritten(string obj)
        {
            m_logConsole.Text += obj + "\n";
            ++logcnt_;

            if(logcnt_ >= 1024)
            {
                logcnt_ = 0;
                m_logConsole.Text = "";
            }

            m_logConsole.ScrollToEnd();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            e.Cancel = true;
            this.Hide();
        }

        private void LoadSettings(object sender, RoutedEventArgs e)
        {
            App.SetSettings();
        }

        private void SaveSettings(object sender, RoutedEventArgs e)
        {
            App.GetSettings();
        }

        private void Exit(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}

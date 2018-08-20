using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
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
        ObservableCollection<string> logbuf_;

        public ControlPanel()
        {
            InitializeComponent();
            DataContext = logbuf_ = new ObservableCollection<string>();
        }

        internal void LogWritten(string obj)
        {
            Dispatcher.Invoke(() =>
            {
                logbuf_.Add(obj);
                if (logbuf_.Count >= 1024)
                {
                    logbuf_.RemoveAt(0);
                }
            });
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

        private void SetAftertouchThreshold(object sender, RoutedEventArgs e)
        {
            PAWHost.AfterTouch_Threshold = (int)(e.Source as Slider)?.Value;
        }
    }
}

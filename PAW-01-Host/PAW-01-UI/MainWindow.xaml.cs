using System;
using System.Collections.Generic;
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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace YadliTechnology
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class UIMainWin : Window
    {
        public UIMainWin()
        {
            InitializeComponent();
        }

        private void UIMainWin_Closed(object sender, EventArgs e)
        {
            PAW01.PAWHost.Stop();
        }

        private void UILoaded(object sender, RoutedEventArgs e)
        {
            this.Top = 0;
            this.Left = 1920;
            this.WindowState = WindowState.Maximized;

            PAW01.PAWHost.Start();
        }
    }
}

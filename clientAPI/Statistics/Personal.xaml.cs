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
using System.Windows.Shapes;
using clientAPI;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for Personal.xaml
    /// </summary>
    private Client client;
    public partial class Personal : Window
    {
        public Personal(ref Client appClient)
        {
            InitializeComponent();

            client = appClient;
        }


        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }
        private void ClickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu=new menu(ref client);
            menu.Show();
        }

        private void updateStrings(string timeText, string correctText, string totalText)
        {
            
            time.SetValue(TextBlock.TextProperty, timeText);
            correct.SetValue(TextBlock.TextProperty, correctText);
            total.SetValue(TextBlock.TextProperty, totalText);

        }
    }
}

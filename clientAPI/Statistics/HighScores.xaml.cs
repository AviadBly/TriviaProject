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

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for HighScores.xaml
    /// </summary>
    public partial class HighScores : Window
    {
        private Client client;
        public HighScores(ref Client appClient)
        {
            client = appClient;
            InitializeComponent();
            updateStrings();
        }

        private void ClickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu(ref client);
            menu.Show();
        }
        private void updateStrings()
        {
            string string1 = "hello";
            string string2 = "goodbye";
            string string3 = "thank you";

            
            player1.SetValue(TextBlock.TextProperty,string1);
            player2.SetValue(TextBlock.TextProperty,string2);
            player3.SetValue(TextBlock.TextProperty,string3);

            
        }


    }
}

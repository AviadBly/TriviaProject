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
    /// Interaction logic for Personal.xaml
    /// </summary>
    public partial class Personal : Window
    {
        public Personal()
        {
            InitializeComponent();
            updateStrings(); 
        }


        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }
        private void ClickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu=new menu();
            menu.Show();
        }

        private void updateStrings()
        {
            string string1 = "hello";
            string string2 = "goodbye";
            string string3 = "thank you";


            time.SetValue(TextBlock.TextProperty, string1);
            correct.SetValue(TextBlock.TextProperty, string2);
            total.SetValue(TextBlock.TextProperty, string3);
        }
    }
}

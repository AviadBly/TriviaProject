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
    /// Interaction logic for SignUpWindow.xaml
    /// </summary>
    public partial class SignUpWindow : Window
    {
        public SignUpWindow()
        {
            InitializeComponent();
        }

        private void clickSignUp(object sender, RoutedEventArgs e)
        {

            TextBox? usernameText = sender as TextBox;

            string username = UsernameText.Text;
            string password = PasswordText.Password.ToString();
            string email = EmailText.Text;

            if (username != null)
                Console.WriteLine(username);


            menu menuWindow = new menu();
            menuWindow.Show();
            this.Close();
        }
    }
}

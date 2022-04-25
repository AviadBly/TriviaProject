using clientAPI.Requests_and_Responses ;
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


            if (username.Length > 8 || password.Length > 8|| username.Length<4||password.Length<4)
            {
                MessageBox.Show("Username or password length must be under 8 characters and over 4 characters!");

            }
            else
            {
                SignUpRequest signUpRequest = new SignUpRequest(username, password, email);
                //
                //


                MessageBox.Show("Username Created successfully!");



                menu menuWindow = new menu();
                menuWindow.Show();
                this.Close();
            }
        }
    }
}

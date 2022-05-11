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
using clientAPI.Requests_and_Responses;
using clientAPI;
using System.Threading;
using System.Globalization;


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

        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void clickSignUp(object sender, RoutedEventArgs e)
        {

            TextBox? usernameText = sender as TextBox;

            string username = UsernameText.Text;
            string password = PasswordText.Password.ToString();
            string email = EmailText.Text;
            string search = "@";
            int indexSearch = email.IndexOf(search);
            string subEmail = email.Substring(indexSearch+1);

            if (username.Length > 10 || password.Length > 10 || username.Length < 4 || password.Length < 4)
            {
                MessageBox.Show("Username or password length must be under 10 characters and over 4 characters!");

            }
            
            else if(email.Contains('@') == false || subEmail.Equals("gmail.com")==false)
            {
                MessageBox.Show("email must be used in @gmail.com format!");
            }
            else
            { 
                
                SignUpRequest signUpRequest = new SignUpRequest(username, password, email);

                
                byte[] data = JsonHelpers.JsonFormatSerializer.signUpSerializer(signUpRequest);
                Console.WriteLine(data);
                MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.SIGN_UP_REQUEST_CODE);

                byte[] returnMsg = MainProgram.appClient.receiver();
                Console.Write(returnMsg);

                SignUpResponse signUpResponse = JsonHelpers.JsonFormatDeserializer.signUpResponseDeserializer(returnMsg.Skip(5).ToArray());

                //login failed
                if (signUpResponse.Status == Response.status_error)
                {
                    MessageBox.Show("Error: Username already exists");
                    return;
                }


                MessageBox.Show("Username Created successfully!");

                MainProgram.mainUser = username;
                menu menuWindow = new menu(MainProgram.mainUser);
                menuWindow.Show();
                this.Close();
            }
        }

        private void click_Login(object sender, RoutedEventArgs e)
        {
            LoginWindow window = new LoginWindow();
            window.Show();
            this.Close();
        }

        private void PasswordBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                clickSignUp(this, new RoutedEventArgs());
            }
        }
    }
}

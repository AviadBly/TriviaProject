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
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text.Json;
using clientAPI.Requests_and_Responses;
using clientAPI.JsonHelpers;
using clientAPI;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        

        public LoginWindow()
        {
            
            
            InitializeComponent();

            
        }


        private void clickLogin(object sender, RoutedEventArgs e)
        {
          
            string username = UsernameText.Text;
            string password = PasswordText.Password.ToString();

            
            if (username == null || password == null)
            {
                MessageBox.Show("Please Enter a valid username!");
                return;
            }
            else
            {
                //create a login request
                LoginRequest loginRequest = new LoginRequest(username, password);

                byte[] data = JsonHelpers.JsonFormatSerializer.loginSerializer(loginRequest);

                MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.LOGIN_REQUEST_CODE);

                byte[] returnMsg = MainProgram.appClient.receiver();
                Console.Write(returnMsg);

                LoginResponse loginResponse = JsonHelpers.JsonFormatDeserializer.loginResponseDeserializer(returnMsg.Skip(5).ToArray());

                //login failed
                if (loginResponse.Status == Response.status_error)
                {
                    MessageBox.Show("Error! Username or password is incorrect!");
                    return;
                }

                


                menu menuWindow = new menu(username);
                menuWindow.Show();
                Close();
            }

           
        }
        
        private void signClick(object sender, RoutedEventArgs e)
        {
            
            SignUpWindow window = new SignUpWindow();          
            window.Show();
            Close();
        }

        private void PasswordBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                clickLogin(this, new RoutedEventArgs());
            }
        }
    }
}

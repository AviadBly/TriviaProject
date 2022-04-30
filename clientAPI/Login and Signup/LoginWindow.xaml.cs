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
        public static Client appClient;

        public LoginWindow()
        {
            load(this, null);
            
            InitializeComponent();

            
            appClient = new Client("127.0.0.1", 8200);
        }

        
        private void clickLogin(object sender, RoutedEventArgs e)
        {
          
            string username = UsernameText.Text;
            string password = PasswordText.Password.ToString();

            
            if (username == null || password == null)
            {
                return;
            }

            //create a login request
            LoginRequest loginRequest = new LoginRequest(username, password);
          
            byte[] data = JsonHelpers.JsonFormatSerializer.loginSerializer(loginRequest);

            appClient.sender(System.Text.Encoding.Default.GetString(data), 20);

            byte[] returnMsg = appClient.receiver();
            Console.Write(returnMsg);
            
            LoginResponse loginResponse = JsonHelpers.JsonFormatDeserializer.loginResponseDeserializer(returnMsg.Skip(5).ToArray());

            //login failed
            if(loginResponse.Status == Response.status_error)
            {
                return;               
            }

            menu menuWindow = new menu(ref appClient);
            menuWindow.Show();
            Hide();
        }

        private void load(object sender, EventArgs e)
        {
            AllocConsole();
        }
      
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();

        private void signClick(object sender, RoutedEventArgs e)
        {
            //this.Close();
            SignUpWindow window = new SignUpWindow(ref appClient);
            Hide();
            window.Show();
            
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

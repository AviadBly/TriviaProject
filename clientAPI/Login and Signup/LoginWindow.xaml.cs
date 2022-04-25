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
            load(this, null);
           
            InitializeComponent();

            
        }


        private void clickLogin(object sender, RoutedEventArgs e)
        {

            //NetworkStream? stream = client("127.0.0.1");
            //if(stream == null)
            //{
            //    return;
            //}

            

            string username = UsernameText.Text;
            string password = PasswordText.Password.ToString();

            
            if (username == null || password == null)
            {
                return;
            }


            LoginRequest loginRequest = new LoginRequest(username, password);

            Client client = new Client("127.0.0.1", 8200);
            byte[] data = JsonHelpers.JsonFormatSerializer.loginSerializer(loginRequest);

            client.sender(System.Text.Encoding.Default.GetString(data), 4);

            byte[] returnMsg = client.receiver();
            Console.Write(returnMsg);

            menu menuWindow = new menu();
            menuWindow.Show();
            this.Close();
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
            this.Close();
            SignUpWindow window=new SignUpWindow();
            window.Show();
        }
    }
}

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
using clientAPI.Requests;

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

        
        public class gg {
            //public gg(int status)
            //{
            //    this.status = status;
            //}

            //public int status = 0;
            //public int g
            //{
            //    get => status;

            //}

            //set { myPropertyVar = value; }
            public gg(int status)
            {
                this.status = status;
            }
            public int Status { get; set; } 
            public int status = 0;
            
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

        
    }
}

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
using System.Text.Json;
using clientAPI.Requests_and_Responses;
using clientAPI.JsonHelpers;
using clientAPI;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for menu.xaml
    /// </summary>
    /// 
    //private Client client;
    public partial class menu : Window
    {
        public menu()
        {
            InitializeComponent();
            JoinRoom joinRoom = new JoinRoom();
           
        }
        
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            
            //LoginRequest login = new LoginRequest("14", "jfkaja");
            //test g = new test(1);
        }

        private void JoinClick(object sender, RoutedEventArgs e)
        {
           JoinRoom joinRoom = new JoinRoom();
            joinRoom.Show();
            this.Close();
        }

        private void clickCreate(object sender, RoutedEventArgs e)
        {
            //LoginRequest l = new LoginRequest("15", "ta");

            //byte[] buffer = JsonHelpers.JsonFormatSerilizer.loginSerilizer(l);

            //LoginResponse response = new LoginResponse(1);
            //byte[] msg = Encoding.ASCII.GetBytes(JsonSerializer.Serialize(response));
            //LoginResponse loginR = JsonHelpers.JsonFormatDeserilizer.loginResponseDeserilizer(msg);

            //Console.WriteLine(loginR.ToString());

            CreateRoom createRoom = new CreateRoom();
            createRoom.Show();
            this.Close();
        }
        private void clickLogin(object sender, RoutedEventArgs e)
        {
            LoginWindow loginRoom = new LoginWindow();
            loginRoom.Show();
            this.Close();
        }
        private void clickSign(object sender, RoutedEventArgs e)
        {
            //SignUpWindow signWindow = new SignUpWindow();
            //signWindow.Show();
            this.Close();
        }

        private void clickStats(object sender, RoutedEventArgs e)
        {
            Statistics statsWindow = new Statistics();
            statsWindow.Show();
            this.Close();
        }

        private void clickSurprise(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start(new System.Diagnostics.ProcessStartInfo
            {
                FileName = "https://m.knesset.gov.il/about/occasion/pages/declaration.aspx",
                UseShellExecute = true
            });
        }

        private void clickExit(object sender, RoutedEventArgs e)
        {

            System.Windows.Application.Current.Shutdown();


        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

        }
    }
}

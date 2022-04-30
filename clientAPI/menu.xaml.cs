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
using System.Globalization;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for menu.xaml
    /// </summary>
    /// 
    public class NotEmptyValidationRule : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            return string.IsNullOrWhiteSpace((value ?? "").ToString())
                ? new ValidationResult(false, "Field is required.")
                : ValidationResult.ValidResult;
        }
    }
    public partial class menu : Window
    {
        private Client client;
        public menu(ref Client appClient)
        {
            InitializeComponent();
            
           
        }
        
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            
            //LoginRequest login = new LoginRequest("14", "jfkaja");
            //test g = new test(1);
        }

        private void JoinClick(object sender, RoutedEventArgs e)
        {
            JoinRoom joinRoom = new JoinRoom(ref client);
            joinRoom.Show();
            this.Close();
        }

        private void clickCreate(object sender, RoutedEventArgs e)
        {
            

            CreateRoom createRoom = new CreateRoom(ref client);
            createRoom.Show();
            this.Close();
        }
        private void clickLogin(object sender, RoutedEventArgs e)
        {
            //LoginWindow loginRoom = new LoginWindow();
            //loginRoom.Show();
            this.Close();
        }
        private void clickSign(object sender, RoutedEventArgs e)
        {
            SignUpWindow signWindow = new SignUpWindow(ref client);
            signWindow.Show();
            this.Close();
        }

        private void clickStats(object sender, RoutedEventArgs e)
        {
            Statistics statsWindow = new Statistics(ref client);
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

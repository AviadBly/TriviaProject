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

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for Personal.xaml
    /// </summary>
    
    public partial class Personal : Window
    {
        private Client client;
        public Personal(ref Client appClient)
        {
            InitializeComponent();

            client = appClient;
        }


        private void Button_Click(object sender, RoutedEventArgs e)
        {
            
            client.sender("", Requests.GET_STATISTICS_REQUEST_CODE);
            
            byte[] returnMsg = client.receiver();
            

            GetPersonalStatsResponse getPersonalStatsResponse = JsonHelpers.JsonFormatDeserializer.GetPersonalStatsResponseDeserializer(returnMsg.Skip(5).ToArray());

            Console.Write(getPersonalStatsResponse);
            //login failed
            if (getPersonalStatsResponse.Status == Response.status_error)
            {
                return;
            }

            List<string> statsList = getPersonalStatsResponse.Statistics;
            string[] statsArr = new string[3];

            int i = 0;
            foreach (string stat in statsList)
            {
                statsArr[i] = stat;
            }

            updateStrings(statsArr[0], statsArr[1], statsArr[2]);
        }
        private void ClickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu(ref client);
            menu.Show();
        }

        private void updateStrings(string timeText, string correctText, string totalText)
        {
            
            time.SetValue(TextBlock.TextProperty, timeText);
            correct.SetValue(TextBlock.TextProperty, correctText);
            total.SetValue(TextBlock.TextProperty, totalText);

        }
    }
}

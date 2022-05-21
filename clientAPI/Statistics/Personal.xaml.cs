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
        
        public Personal()
        {
            InitializeComponent();

            string[] statsArr = getPersonalStatistics();
            updateStrings(statsArr[0], statsArr[1], statsArr[2], statsArr[3]);
        }

        private string[] getPersonalStatistics()
        {
            MainProgram.appClient.sender("", Requests.GET_PERSONAL_STATISTICS_REQUEST_CODE);

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();


            GetPersonalStatsResponse getPersonalStatsResponse = JsonHelpers.JsonFormatDeserializer.GetPersonalStatsResponseDeserializer(returnMsg.Message);

            Console.Write(getPersonalStatsResponse);
            //login failed
            if (getPersonalStatsResponse.Status == Response.status_error)
            {
                return null;
            }

            List<string> statsList = getPersonalStatsResponse.PersonalStatistics;
            string[] statsArr = new string[4];

            int i = 0;
            foreach (string stat in statsList)
            {
                statsArr[i] = stat;
                i++;
            }

            return statsArr;
        }
      
        private void ClickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu(MainProgram.MainUsername);
            menu.Show();
        }

        
        private void updateStrings(string avgAnswerTime, string correctAnswers, string totalAnswers, string numberOfGames)
        {
            
            time.SetValue(TextBlock.TextProperty, avgAnswerTime);
            correct.SetValue(TextBlock.TextProperty, correctAnswers);
            total.SetValue(TextBlock.TextProperty, totalAnswers);
            games.SetValue(TextBlock.TextProperty, numberOfGames);
            

        }
    }
}

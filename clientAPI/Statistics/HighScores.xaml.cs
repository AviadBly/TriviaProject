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
    /// Interaction logic for HighScores.xaml
    /// </summary>
    public partial class HighScores : Window
    {
        
        public HighScores()
        {
            
            InitializeComponent();
            string[] places = getHighScorePlayers();
            updateStrings(places[0], places[1], places[2]);
        }

        private void ClickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu(MainProgram.MainUsername);
            menu.Show();
        }

        private string[] getHighScorePlayers()
        {
            MainProgram.appClient.sender("", Requests_and_Responses.Requests.GET_HIGH_SCORES_REQUEST_CODE);

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();
            Console.Write(returnMsg);

            Requests_and_Responses.GetHighScoreResponse highScoreResponse = JsonHelpers.JsonFormatDeserializer.GetHighScoreResponseDeserializer(returnMsg.Message.Skip(5).ToArray());

            //login failed
            if (highScoreResponse.Status == Requests_and_Responses.Response.status_error)
            {
                Console.WriteLine("Error");
                return null;
            }

            string[] place = new string[3];
            place[0] = highScoreResponse.HighScorePlayers[0];
            place[1] = highScoreResponse.HighScorePlayers[1];
            place[2] = highScoreResponse.HighScorePlayers[2];

            return place;
        }

        private void updateStrings(string firstPlace, string secondPlace, string thirdPlace)
        {                      
            player1.SetValue(TextBlock.TextProperty, firstPlace);
            player2.SetValue(TextBlock.TextProperty, secondPlace);
            player3.SetValue(TextBlock.TextProperty, thirdPlace);

        }


    }
}

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
            
            menu.goToMenu();
            this.Close();
        }

        private string[] getHighScorePlayers()
        {
            MainProgram.appClient.sender("", Requests_and_Responses.Requests.GET_HIGH_SCORES_REQUEST_CODE);

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();
            Console.Write(returnMsg);

            Requests_and_Responses.GetHighScoreResponse highScoreResponse = JsonHelpers.JsonFormatDeserializer.GetHighScoreResponseDeserializer(returnMsg.Message);

            if (returnMsg.IsErrorMsg)   //if error
            {
                MessageBox.Show(Encoding.UTF8.GetString(returnMsg.Message));
                return new string[3];
            }

            string[] place = new string[3];
            if(highScoreResponse.HighScorePlayers.Count<3)
            {
                place[0] = "Please";
                place[1] = "Make";
                place[2] = "Scores :D";
            }
            else
            {
                place[0] = highScoreResponse.HighScorePlayers[0];
                place[1] = highScoreResponse.HighScorePlayers[1];
                place[2] = highScoreResponse.HighScorePlayers[2];
            }


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

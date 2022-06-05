using clientAPI.Requests_and_Responses;
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

namespace clientAPI.GameFolder
{
    /// <summary>
    /// Interaction logic for Results.xaml
    /// </summary>
    public partial class Results : Window
    {
        private static GetGameResultsResponse data;
        public Results()
        {
            InitializeComponent();
            data= ShowPlayers();

        }

        private void ClickExit(object sender, RoutedEventArgs e)
        {
            Close();
            menu menu = new menu(MainProgram.MainUsername);
            menu.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            menu.Show();
        }

        private GetGameResultsResponse ShowPlayers()
        {
            MainProgram.appClient.sender("", Requests.GET_GAME_RESULT_REQUEST_CODE);    //ask for rooms

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();


            GetGameResultsResponse getGameResultsResponse = JsonHelpers.JsonFormatDeserializer.GetGameResultsResponseDeserializer(returnMsg.Message);

            if (getGameResultsResponse == null)
            {
                Console.WriteLine("Received empty or wrong answer from server");

            }
            
            foreach(PlayerResults playerResults in getGameResultsResponse.Results)
            {
                PlayerList.Items.Add(playerResults.Username);
            }
            return getGameResultsResponse;
        }

        private void PlayerList_SelectionChanged(object sender, SelectionChangedEventArgs e,)
        {
            string username = PlayerList.SelectedItem.ToString();
            foreach(PlayerResults playerResult in data.Results)
            {
                if(playerResult.Username == username)
                {
                    Correct.Content = playerResult.CorrectAnswerCount;
                    Wrong.Content = playerResult.WrongAnswerCount;
                    Average.Content = playerResult.AverageAnswerCount;
                    break;
                }
            }
        }
    }


    
}

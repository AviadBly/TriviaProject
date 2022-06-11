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
using System.Windows.Threading;

namespace clientAPI.GameFolder
{
    /// <summary>
    /// Interaction logic for Results.xaml
    /// </summary>
    public partial class Results : Window
    {
        private static GetGameResultsResponse data;
        private DispatcherTimer timer;

        private const int REFRESH_SEND_TIME = 3; //in seconds
        
        public Results()
        {

            InitializeComponent();
            timer = new DispatcherTimer();
            timer.Interval = new TimeSpan(0, 0, REFRESH_SEND_TIME);

            timer.Tick += Timer_Tick;

            timer.Start();
        }

        private void Timer_Tick(object? sender, EventArgs e)
        {
            data = ShowPlayers();
        }

        private void ClickExit(object sender, RoutedEventArgs e)
        {
            MainProgram.appClient.sender("", Requests.LEAVE_GAME_REQUEST_CODE);    //ask for rooms

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();


            LeaveGameResponse leaveGameResponse = JsonHelpers.JsonFormatDeserializer.LeaveGameResponseDeserializer(returnMsg.Message);

            if (leaveGameResponse == null)
            {
                Console.WriteLine("Received empty or wrong answer from server");

            }


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
                if (!PlayerList.Items.Contains(playerResults.Username))
                    PlayerList.Items.Add(playerResults.Username);
            }
            return getGameResultsResponse;
        }

        private void PlayerList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string username = PlayerList.SelectedItem.ToString();
            foreach(PlayerResults playerResult in data.Results)
            {
                if(playerResult.Username == username)
                {
                    Correct.Content = playerResult.CorrectAnswerCount;
                    Wrong.Content = playerResult.WrongAnswerCount;
                    Average.Content = playerResult.AverageAnswerTime;
                    break;
                }
            }
        }
    }


    
}

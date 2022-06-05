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
        public Results()
        {
            InitializeComponent();
        }

        private void ClickExit(object sender, RoutedEventArgs e)
        {
            Close();
            menu menu = new menu(MainProgram.MainUsername);
            menu.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            menu.Show();
        }

        private void ShowResults(object sender, RoutedEventArgs e)
        {
            MainProgram.appClient.sender("", Requests.GET_GAME_RESULT_REQUEST_CODE);    //ask for rooms

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();


            GetGameResultsResponse getGameResultsResponse = JsonHelpers.JsonFormatDeserializer.GetGameResultsResponseDeserializer(returnMsg.Message);

            if (getGameResultsResponse == null)
            {
                Console.WriteLine("Received empty or wrong answer from server");

            }

            
        }

        private void roomsList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }


    
}

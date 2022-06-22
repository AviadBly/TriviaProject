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

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class StatisticsWindow : Window
    {
        
        public StatisticsWindow()
        {
            
            InitializeComponent();
        }

       

        private void backClick(object sender, RoutedEventArgs e)
        {
            menu.goToMenu();
            Close();
        }

        private void ClickPersonal(object sender, RoutedEventArgs e)
        {
            Personal personal = new Personal();
            personal.WindowStartupLocation = WindowStartupLocation.CenterScreen;

            personal.Show();
            this.Close();
        }

        private void ClickScores(object sender, RoutedEventArgs e)
        {
            HighScores scores = new HighScores();
            scores.WindowStartupLocation = WindowStartupLocation.CenterScreen;

            scores.Show();
            this.Close();
        }

        //gives the user access to add a question, only if hes trusted (25  correct answers)
        private void AddQuestion(object sender, RoutedEventArgs e)
        {
            MainProgram.appClient.sender("", Requests.GET_PERSONAL_STATISTICS_REQUEST_CODE);

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();


            GetPersonalStatsResponse getPersonalStatsResponse = JsonHelpers.JsonFormatDeserializer.GetPersonalStatsResponseDeserializer(returnMsg.Message);

            if (returnMsg.IsErrorMsg)   //if error
            {
                MessageBox.Show(Encoding.UTF8.GetString(returnMsg.Message));
                return;
            }

            if(Int32.Parse(getPersonalStatsResponse.PersonalStatistics[1]) < 25)
            {
                MessageBox.Show("Player must have at least 25 correct answers in order to insert a question!");

            }
            else
            {
                clientAPI.Statistics.AddQuestion addQuestion = new clientAPI.Statistics.AddQuestion();
                addQuestion.WindowStartupLocation = WindowStartupLocation.CenterScreen;
                addQuestion.Show();
                Close();
            }
        }
    }
}

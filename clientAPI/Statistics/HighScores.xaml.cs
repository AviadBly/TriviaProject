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
            updateStrings();
        }

        private void ClickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu();
            menu.Show();
        }
        private void updateStrings()
        {
            MainProgram.appClient.sender("", Requests_and_Responses.Requests.GET_HIGH_SCORES_REQUEST_CODE);

            byte[] returnMsg = MainProgram.appClient.receiver();
            Console.Write(returnMsg);

            Requests_and_Responses.GetHighScoreResponse highScoreResponse = JsonHelpers.JsonFormatDeserializer.GetHighScoreResponseDeserializer(returnMsg.Skip(5).ToArray());

            //login failed
            if (highScoreResponse.Status == Requests_and_Responses.Response.status_error)
            {
                return;
            }

            for (int i = 0; i < highScoreResponse.highest.Count; i++)
            {
                if(i==0)
                {
                    player1.SetValue(TextBlock.TextProperty, highScoreResponse.highest[i]);

                }
                if (i == 1)
                {
                    player2.SetValue(TextBlock.TextProperty, highScoreResponse.highest[i]);

                }
                if (i == 2)
                {
                    player3.SetValue(TextBlock.TextProperty, highScoreResponse.highest[i]);

                }
            }

        }


    }
}

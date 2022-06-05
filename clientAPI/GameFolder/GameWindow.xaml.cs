using clientAPI.Create_and_Join;
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
using clientAPI.GameFolder;


namespace clientAPI.GameFolder
{
    /// <summary>
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    
    public partial class GameWindow : Window
    {
        Game m_game;
        public GameWindow()
        {
            InitializeComponent();
        }

        public Question GetNextQuestion()
        {
            MainProgram.appClient.sender("", Requests.GET_QUESTION_REQUEST_CODE);    //ask for rooms

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();


            GetQuestionResponse getQuestionResponse = JsonHelpers.JsonFormatDeserializer.GetQuestionResponseDeserializer(returnMsg.Message);

            if (getQuestionResponse == null)
            {
                Console.WriteLine("Received empty or wrong answer from server");
                
            }


            return getQuestionResponse.Question;


        }
    }
}

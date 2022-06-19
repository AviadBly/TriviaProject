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

namespace clientAPI.Statistics
{
    /// <summary>
    /// Interaction logic for AddQuestion.xaml
    /// </summary>
    public partial class AddQuestion : Window
    {
        public AddQuestion()
        {
            InitializeComponent();
        }

        private void ClickExit(object sender, RoutedEventArgs e)
        {

            menu.goToMenu();
            this.Close();
        }

        private void CreateQuestion(object sender, RoutedEventArgs e)
        {
            string question = QuestionText.Text.ToString();
            string false1 = False1.Text.ToString();
            string false2= False2.Text.ToString();
            string false3=False3.Text.ToString();
            string correct= Correct.Text.ToString();

            CreateQuestionRequest createQuestion = new CreateQuestionRequest(question,false1,false2,false3,correct);

            byte[] data = JsonHelpers.JsonFormatSerializer.CreateQuestionSerializer(createQuestion);

            MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.CREATE_QUESTION_REQUEST_CODE);

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();

            if (returnMsg.IsErrorMsg)   //if error
            {
                MessageBox.Show(Encoding.UTF8.GetString(returnMsg.Message));
                return;
            }

            Console.Write(returnMsg);

            CreateQuestionResponse createQuestionResponse = JsonHelpers.JsonFormatDeserializer.createQuestionResponseDeserializer(returnMsg.Message);

            if(createQuestionResponse.Status==Response.status_ok)
            {
                MessageBox.Show("Question Submited!");
                menu.goToMenu();
            }
            else
            {
                MessageBox.Show("Error!");
            }
        }
    }

}

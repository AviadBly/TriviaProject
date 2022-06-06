using clientAPI.Requests_and_Responses;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Threading;
using System.Threading.Tasks;

namespace clientAPI.GameFolder
{
    /// <summary>
    /// Interaction logic for GameWindow.xaml
    /// </summary>

    public partial class GameWindow : Window
    {
        Game m_game;
        uint m_id;
        int _count;

        public GameWindow()
        {
            InitializeComponent();

            startGame();
        }

        public async void startGame()
        {
            for (int i = 0; i < 10; i++)
            {
                m_id = 999;

                
                await displayQuestionOnScreen();
                
                await SubmitAnswer(m_id);
                
            }
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
            Question question = new Question(getQuestionResponse.QuestionText, getQuestionResponse.Answers);

            return question;

        }

        
        public async Task displayQuestionOnScreen()
        {
            ResetColors();
            Question question = GetNextQuestion();
            ResetColors();
            questionLabel.Content = question.QuestionText.ToString();
            Answer1.Content = question.Answers[0].ToString();
            Answer2.Content = question.Answers[1].ToString();
            Answer3.Content = question.Answers[2].ToString();
            Answer4.Content = question.Answers[3].ToString();

            await Task.Delay(3000);
            
        }

        private void AnswerClicked(object sender, RoutedEventArgs e)
        {
            string buttonId = (sender as Button).Name.ToString();
            char charId = buttonId[buttonId.Length - 1];
            uint id = Convert.ToUInt32(charId.ToString()) - 1;  //id start with 0

            m_id = id;
          
        }

        private async Task SubmitAnswer(uint id)
        {
            
            SubmitAnswerRequest submitAnswerRequest = new SubmitAnswerRequest(id);
            byte[] data = JsonHelpers.JsonFormatSerializer.SubmitAnswerSerializer(submitAnswerRequest);
            Console.WriteLine(data);

            MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.SUBMIT_ANSWER_REQUEST_CODE);


            ReceivedMessage returnMsg = MainProgram.appClient.receiver();

            SubmitAnswerResponse submitAnswerResponse = JsonHelpers.JsonFormatDeserializer.SubmitAnswerResponseDeserializer(returnMsg.Message);

            if (submitAnswerResponse == null)
            {
                Console.WriteLine("Received empty or wrong answer from server");
                return;
            }

            switchColors(m_id, submitAnswerResponse.CorrectAnswerId == id);

            await Task.Delay(2000);
           
            //TODO
        }

        private void switchColors(uint id, bool isCorrect)
        {
            if(isCorrect)
            {
                switchId(id, Brushes.Green);
            }
            else
            {
                switchId(id, Brushes.Red);
            }

        }


        private void switchId(uint id,SolidColorBrush solidColorBrush)
        {
            switch(id)
            {
                case 1:
                    Answer1.Background = solidColorBrush;
                    break;

                case 2:
                    Answer2.Background = solidColorBrush;
                    break;

                case 3:
                    Answer3.Background = solidColorBrush;
                    break;

                case 4:
                    Answer4.Background = solidColorBrush;

                    break;


            }
            
        }

        private void ResetColors()
        {
            Answer1.Background= new SolidColorBrush(Color.FromArgb(100, 103, 58, 183));
            Answer2.Background = new SolidColorBrush(Color.FromArgb(100, 103, 58, 183));
            Answer3.Background = new SolidColorBrush(Color.FromArgb(100, 103, 58, 183));
            Answer4.Background = new SolidColorBrush(Color.FromArgb(100, 103, 58, 183));
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
    }
}

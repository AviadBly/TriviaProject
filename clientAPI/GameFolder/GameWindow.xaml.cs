using clientAPI.Requests_and_Responses;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Threading;

namespace clientAPI.GameFolder
{
    /// <summary>
    /// Interaction logic for GameWindow.xaml
    /// </summary>

    public partial class GameWindow : Window
    {
        string name;
        uint numberOfQuestions;
        uint timePerQuestion; //in seconds

        bool isUserAnswered;
        uint totalWaitingTime; //in miliseconds

        const int ANSWER_SHOW_TIME = 1300; //in miliseconds
        const int REFRESH_TIME = 100; //in miliseconds
        const uint FAKE_WRONG_ID = 999;

        uint tempTime;
        private DispatcherTimer timer;

        public GameWindow(uint timePerQuestion, string name, uint numberOfQuestions)
        {
            InitializeComponent();
            this.timePerQuestion = timePerQuestion;
            this.name = name;
            this.numberOfQuestions = numberOfQuestions;
            tempTime = timePerQuestion;
            TimerLabel.Content = tempTime;
            timer = new DispatcherTimer();
            timer.Interval = new TimeSpan(0, 0, 0,0, 993);
            
            timer.Tick += Timer_Tick;
        
            startGame();
        }

        private void Timer_Tick(object? sender, EventArgs e)
        {
            if(tempTime>0)
            {
                tempTime--;
                TimerLabel.Content = tempTime;
            }
            else
            {
                tempTime = timePerQuestion-1;
                
                
            }
            
        }

        public async void startGame()
        {

            totalWaitingTime = timePerQuestion * numberOfQuestions * 1000;

            for (int i = 0; i < numberOfQuestions; i++)
            {
                            
                await displayQuestionOnScreen();                                             
                if (!isUserAnswered)
                {                    
                    await SubmitAnswer(FAKE_WRONG_ID);
                }                            
            }

            Results resultsWindow = new Results();
            resultsWindow.Show();
            Close();
        }

        public async Task QuestionWaiter()  
        {
            for(int i = 0; i < timePerQuestion * 1000 / REFRESH_TIME; i++)
            {
                if (!isUserAnswered) {
                    totalWaitingTime -= REFRESH_TIME;
                    await Task.Delay(REFRESH_TIME);
                }
                else
                {
                    await Task.Delay(ANSWER_SHOW_TIME);
                    return;
                }
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
            timer.Start();
            ResetColors();
            Question question = GetNextQuestion();
            isUserAnswered = false;
            questionLabel.Content = question.QuestionText.ToString();
            Answer1.Content = question.Answers[0].ToString();
            Answer2.Content = question.Answers[1].ToString();
            Answer3.Content = question.Answers[2].ToString();
            Answer4.Content = question.Answers[3].ToString();
            //await Task.Delay(ANSWER_SHOW_TIME * 4);
            await QuestionWaiter();
        }

        private async void AnswerClicked(object sender, RoutedEventArgs e)
        {
            
            string buttonId = (sender as Button).Name.ToString();
            char charId = buttonId[buttonId.Length - 1];
            uint id = Convert.ToUInt32(charId.ToString()) - 1;  //id start with 0

            
            isUserAnswered = true;
            await SubmitAnswer(id);
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

            switchColors(id, submitAnswerResponse.CorrectAnswerId == id);//switch the user answer to the required color
            switchColors(submitAnswerResponse.CorrectAnswerId, true); //turn the correct answer to green
            if (isUserAnswered)
            {
                await Task.Delay(ANSWER_SHOW_TIME);
                tempTime = timePerQuestion-1;
            }
            
            
        }

        private void switchColors(uint id, bool isCorrect)
        {
            if(isCorrect)
            {
                switchId(id, Brushes.Green);
            }
            else {
                switchId(id, Brushes.Red);
            }

        }


        private void switchId(uint id,SolidColorBrush solidColorBrush)
        {
            switch(id)
            {
                case 0:
                    Answer1.Background = solidColorBrush;
                    break;
                case 1:
                    Answer2.Background = solidColorBrush;
                    break;
                case 2:
                    Answer3.Background = solidColorBrush;
                    break;
                case 3:
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

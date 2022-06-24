using clientAPI.Requests_and_Responses;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Threading;
using System.Media;
using clientAPI.Properties;

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

        bool isGameExited;
        bool isUserAnswered;
        

        const int ANSWER_SHOW_TIME = 1000; //in miliseconds
        const int REFRESH_TIME = 100; //in miliseconds
        const uint FAKE_WRONG_ID = 999;
        const int DISPATCHER_TICK = 993;

        uint tempTime;
        private DispatcherTimer timer;

        //DISPATCHER TIMER: responsible for the visual timer to use the countdown.
        public GameWindow(uint timePerQuestion, string name, uint numberOfQuestions)
        {
            InitializeComponent();
            this.timePerQuestion = timePerQuestion;
            this.name = name;
            this.numberOfQuestions = numberOfQuestions;
            tempTime = timePerQuestion;
            TimerLabel.Content = tempTime;
            timer = new DispatcherTimer();
            timer.Interval = new TimeSpan(0, 0, 0,0, DISPATCHER_TICK);
            
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

            

            for (int i = 0; i < numberOfQuestions; i++)
            {
                            
                await displayQuestionOnScreen();                                             
                if (!isUserAnswered)
                {                    
                    await SubmitAnswer(FAKE_WRONG_ID);
                }                            
            }

            Results resultsWindow = new Results();
            resultsWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            resultsWindow.Show();
            Close();
        }

        public async Task QuestionWaiter()  
        {
            for(int i = 0; i < timePerQuestion * 1000 / REFRESH_TIME; i++)
            {
                if (!isUserAnswered) {
                    
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
            if (isGameExited) { return; }
            timer.Start();
            ResetColors();
            Question question = GetNextQuestion();
            isUserAnswered = false;
            questionLabel.Content = question.QuestionText.ToString();
            Answer1.Content = question.Answers[0].ToString();
            Answer2.Content = question.Answers[1].ToString();
            Answer3.Content = question.Answers[2].ToString();
            Answer4.Content = question.Answers[3].ToString();

            
            await QuestionWaiter();
        }

        private async void AnswerClicked(object sender, RoutedEventArgs e)
        {
            if (isUserAnswered){ return; }  //if answer was already chosen, ignore this click

            string buttonId = (sender as Button).Name.ToString();
            char charId = buttonId[buttonId.Length - 1];
            uint id = Convert.ToUInt32(charId.ToString()) - 1;  //id start with 0

            
            isUserAnswered = true;
            await SubmitAnswer(id);
        }

        private async Task SubmitAnswer(uint id)
        {
            if (isGameExited) { return; }
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
            if(submitAnswerResponse.CorrectAnswerId==id)
            {
                SoundPlayer s = new SoundPlayer(Properties.Resources.mixkit_arcade_game_complete_or_approved_mission_205);
                s.Play();
            }
            else
            {
                SoundPlayer s = new SoundPlayer(Properties.Resources.mixkit_wrong_answer_fail_notification_946);
                s.Play();
            }

            switchColors(submitAnswerResponse.CorrectAnswerId, true); //turn the correct answer to green
            
            if (isUserAnswered) //show the answer for sometime
            {
                await Task.Delay(ANSWER_SHOW_TIME);
                tempTime = timePerQuestion-1;
            }
            
            
        }
        //marks the correct answer green, and the wrong one red.
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
        //every new question. for the answers to return to their original colors.
        private void ResetColors()
        {
            Answer1.Background= new SolidColorBrush(Color.FromArgb(100, 103, 58, 183));
            Answer2.Background = new SolidColorBrush(Color.FromArgb(100, 103, 58, 183));
            Answer3.Background = new SolidColorBrush(Color.FromArgb(100, 103, 58, 183));
            Answer4.Background = new SolidColorBrush(Color.FromArgb(100, 103, 58, 183));
        }

        private void ClickExit(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            MainProgram.appClient.sender("", Requests.LEAVE_GAME_REQUEST_CODE);    //ask for rooms

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();


            LeaveGameResponse leaveGameResponse = JsonHelpers.JsonFormatDeserializer.LeaveGameResponseDeserializer(returnMsg.Message);

            if (leaveGameResponse == null)
            {
                Console.WriteLine("Received empty or wrong answer from server");

            }

            isGameExited = true;

            Close();
            menu.goToMenu();


        }
    }
}

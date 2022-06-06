﻿using clientAPI.Requests_and_Responses;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Threading;


namespace clientAPI.GameFolder
{
    /// <summary>
    /// Interaction logic for GameWindow.xaml
    /// </summary>

    public partial class GameWindow : Window
    {
        Game m_game;
        uint m_id;
        public GameWindow()
        {
            InitializeComponent();
            for(int i = 0; i < 10; i++)
            {
                m_id = 999;
                Thread.Sleep(5000);
                SubmitAnswer(m_id);
                
                displayQuestionOnScreen();
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


        public void displayQuestionOnScreen()
        {
            Question question = GetNextQuestion();
            //SortedDictionary<uint, string> dict = new SortedDictionary<uint, string>();
            //dict.Add(1, "Fine");
            //dict.Add(2, "okay");
            //dict.Add(3, "brara");
            //dict.Add(4, "kill me");
            //Question question = new Question("How are you today??", dict);
            questionLabel.Content = question.QuestionText.ToString();
            Answer1.Content = question.Answers[0].ToString();
            Answer2.Content = question.Answers[1].ToString();
            Answer3.Content = question.Answers[2].ToString();
            Answer4.Content = question.Answers[3].ToString();

        }

        private void AnswerClicked(object sender, RoutedEventArgs e)
        {
            string buttonId = (sender as Button).Name.ToString();
            char charId = buttonId[buttonId.Length - 1];
            uint id = Convert.ToUInt32(charId.ToString()) - 1;  //id start with 0

            m_id = id;

            
        }

        private void SubmitAnswer(uint id)
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
            
             
            //TODO
        }

        private void switchColors(uint id, bool isCorrect)
        {
            switch (id)
            {

            }
            //if (submitAnswerResponse.CorrectAnswerId == id)
            //{
            //    (sender as Button).Background = Brushes.Green;
            //}
            //else
            //{
            //    (sender as Button).Background = Brushes.Red;

            //}
        }

        private void ResetColors()
        {

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

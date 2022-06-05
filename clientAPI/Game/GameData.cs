using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using clientAPI.Login_and_Signup;


namespace clientAPI.Game
{
    public class Question
    {
        public Question(string questionText, SortedDictionary<uint, string> answers)
        {
            QuestionText = questionText;
            Answers = answers;
        }
        public string QuestionText { get; set; } = default(string);
        public SortedDictionary<uint, string> Answers { get; set; }
    }
    public class GameData
    {
          
        public Question CurrentQuestion { get; set; }
        public uint CorrectAnswerCount { get; set; }
        public uint WrongAnswerCount { get; set; }
        public double AverageAnswerTime { get; set; }
        public bool HasPlayerFinished { get; set; }
        public GameData(Question currentQuestion, uint correctAnswerCount, uint wrongAnswerCount, double averageAnswerTime, bool hasPlayerFinished)
        {
            CurrentQuestion = currentQuestion;
            CorrectAnswerCount = correctAnswerCount;
            WrongAnswerCount = wrongAnswerCount;
            AverageAnswerTime = averageAnswerTime;
            HasPlayerFinished = hasPlayerFinished;
        }
    }

    public class Game
    {
        public uint Id { get; set; }

        public List<Question> Questions { get; set; }
        public SortedDictionary<User, GameData> PlayersGameData { get; set; }       
        public uint TimePerQuestion { get; set; }
        public bool HasGameEnded { get; set; }
        public Game(uint id, List<Question> questions, SortedDictionary<User, GameData> playersGameData, uint timePerQuestion, bool hasGameEnded)
        {
            Id = id;
            Questions = questions;
            PlayersGameData = playersGameData;
            TimePerQuestion = timePerQuestion;
            HasGameEnded = hasGameEnded;
        }
    }
}

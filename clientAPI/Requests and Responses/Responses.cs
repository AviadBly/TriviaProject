using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using clientAPI.Create_and_Join;
using clientAPI.GameFolder;
namespace clientAPI.Requests_and_Responses
{
	internal class Response
	{

        
        public const byte status_ok = 2;
		public const byte status_error = 5;

        public Response(byte status)
        {
            Status = status;
        }
		public byte Status { get; set; }

    }
    internal class LoginResponse : Response
    {
        public LoginResponse(byte status) : base(status)
        {
			
        }
		
	};
	internal class SignUpResponse : Response
	{
		public SignUpResponse(byte status) : base(status)
		{

		}

	};

	internal class  ErrorResponse : Response
	{
		
        public const uint errorMsgCode = 50;
        public const uint SERVER_DICONECT_CODE = 66;
        public ErrorResponse(string message, byte status) : base(status)
        {
            Message = message;
        }
		public string Message { get; set; } = default!;
    };
	internal class LogOutResponse : Response
	{
		public LogOutResponse(byte status) : base(status)
		{

		}

	};

    internal class GetRoomsResponse : Response
    {
        public const uint roomNotFoundStatus = 7;
        public const uint startedGameStatus = 10;
        public GetRoomsResponse(List<Room> rooms, byte status) : base(status)
        {
            Rooms = rooms;
        }
        public List<Room> Rooms { get; set; }
    };


    internal class  GetPlayersInRoomResponse : Response
    {
		
        public const uint roomNotFoundStatus = 7;
        public GetPlayersInRoomResponse(List<string> players, byte status) :base(status) {
            Players = players;
        }
		public List<string> Players { get; set; }
    }
    internal class  GetHighScoreResponse : Response
	{

        public GetHighScoreResponse(List<string> highScorePlayers, byte status) :base (status)
        {
            HighScorePlayers = highScorePlayers;
        }

        public List<string> HighScorePlayers { get;set; }

       
       
	};
	internal class  GetPersonalStatsResponse :  Response
	{
		
        public GetPersonalStatsResponse(List<string> personalStatistics, byte status) : base(status)
        {
            PersonalStatistics = personalStatistics;
        }
                            
        public List<string> PersonalStatistics { get; set; }

    }

    internal class JoinRoomResponse : Response
    {
        public JoinRoomResponse(byte status) : base(status)
        {
        }
    }
    internal class CreateRoomResponse : Response
    {
        public CreateRoomResponse(byte status) : base(status)
        {
        }
    }
    internal class CloseRoomResponse : Response
    {
        public CloseRoomResponse(byte status) : base(status)
        {

        }
    }
    internal class LeaveRoomResponse : Response
    {
        public LeaveRoomResponse(byte status) : base(status)
        {
        }
    }
    internal class StartGameResponse : Response
    {
        public StartGameResponse(byte status) : base(status)
        {
        }
    }
    internal class GetRoomStateResponse : Response
    {
        public const int statusRoomNotFound = 7;
        public GetRoomStateResponse(byte status,bool hasGameBegun, List<string> players, uint answerCount, uint answerTimeOut) : base(status)
        {
            HasGameBegun = hasGameBegun;
            Players = players;
            AnswerCount = answerCount;
            AnswerTimeOut = answerTimeOut;

        }
        public bool HasGameBegun { get; set; }

        public List<string> Players { get; set; }
        public  uint AnswerCount { get; set; }

        public uint AnswerTimeOut { get; set; }
    }

    internal class LeaveGameResponse : Response
    {
        public LeaveGameResponse(byte status) : base(status)
        {
        }
    }

    internal class TemporaryGetQuestionResponse : Response
    {
        public TemporaryGetQuestionResponse(byte status, string questionText, List<string> answers) : base(status)
        {
            QuestionText = questionText;
            Answers = answers;
        }
        public string QuestionText { get; set; }
        public List<string> Answers { get; set; }

    }

    internal class GetQuestionResponse : Response
    {
        public GetQuestionResponse(byte status, string questionText, SortedDictionary<uint, string> answers) : base(status)
        {
            QuestionText = questionText;
            Answers = answers;
        }
        public string QuestionText { get; set; }
        public SortedDictionary<uint,string> Answers { get; set; }

    }

    internal class SubmitAnswerResponse : Response
    {
        public SubmitAnswerResponse(byte status,uint correctAnswerId) : base(status)
        {
            CorrectAnswerId= correctAnswerId;
        }
        public uint CorrectAnswerId { get; set; }
    }

    internal class PlayerResults
    {
        public PlayerResults(string username, uint correctAnswerCount, uint wrongAnswerCount, double averageAnswerTime)
        {
            Username = username;
            CorrectAnswerCount = correctAnswerCount;
            WrongAnswerCount = wrongAnswerCount;
            AverageAnswerTime = averageAnswerTime;
        }

        public string Username { get; set; }
        public uint CorrectAnswerCount { get; set; }
        public uint WrongAnswerCount { get; set; }
        public double AverageAnswerTime { get; set; }
    }
    
    
    internal class GetGameResultsResponse : Response
    {    
        public GetGameResultsResponse(List<PlayerResults> results, byte status) : base(status)
        {
            Results = results;
        }
        public List<PlayerResults> Results { get; set; }
    }

    internal class CreateQuestionResponse : Response
    {
        public CreateQuestionResponse(byte status) : base(status)
        {

        }
    }

}

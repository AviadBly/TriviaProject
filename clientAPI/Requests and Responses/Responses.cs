using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using clientAPI.Create_and_Join;

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

	internal class  ErrorResponse
	{
		string message;

        public ErrorResponse(string message)
        {
            this.message = message;
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
        
        public GetRoomsResponse(List<Room> rooms, byte status) : base(status)
        {
            Rooms = rooms;
        }
        public List<Room> Rooms { get; set; }
    };

    internal class  GetPlayersInRoomResponse
    {
		

        public GetPlayersInRoomResponse(List<string> players)
        {
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

}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace clientAPI.Requests_and_Responses
{

 
    internal class Requests
    {
        public const byte SIGN_UP_REQUEST_CODE  = 10;
        public const byte LOGIN_REQUEST_CODE = 20;
        public const byte ERROR_RESPONSE_CODE = 50;
        public const byte LOGOUT_REQUEST_CODE = 21;

        public const byte CREATE_ROOM_CODE = 30;
        public const byte GET_ROOM_REQUEST = 31;
        public const byte GET_PLAYERS_IN_ROOM_REQUEST_CODE = 32;
        public const byte JOIN_ROOM_REQUEST_CODE = 33;
        public const byte GET_STATISTICS_REQUEST_CODE = 34;
        public const byte GET_HIGH_SCORES_REQUEST_CODE = 35;
        

        string username;
        string password;
        public Requests(string username, string password)
        {
            this.username = username;
            this.password = password;
        }
        public string Username { get; set; }
        public string Password { get; set; }

    }
    internal class SignUpRequest:  Requests
    {
        string email;

        public SignUpRequest(string username, string password,string email) : base(username, password)
        {
            this.Username = username;
            this.Password = password;
            this.email = email;
        }
        public string Email { get; set; }
    }
    

    internal class LoginRequest
    {
        string? username;
        string? password;

        public LoginRequest(string? username, string? password)
        {
            Username = username;
            Password = password;
        }
        public string? Username { get; set; } = default!;
        public string? Password { get; set; } = default!;
    }

    internal class JoinRoomRequest
    {
        uint roomId;
        public JoinRoomRequest(uint roomId)
        {
            this.roomId=roomId;
        }
        public uint RoomId { get; set; }
    };

    internal class  CreateRoomRequest
    {
        string roomName;
        uint maxUsers;
        uint questionCount;
        uint answerTimeout;

        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
        {
            this.roomName = roomName;
            this.maxUsers = maxUsers;
            this.questionCount = questionCount;
            this.answerTimeout = answerTimeout;
        }
        public string RoomName { get; set; }
        public uint MaxUsers { get; set; }
        public uint QuestionCount { get; set; }
        public uint AnswerTimeout { get; set; }
            

    }

    internal class GetPlayersInRoomRequest
    {
        uint roomId;

        public GetPlayersInRoomRequest(uint roomId)
        {
            this.roomId = roomId;
        }
        public uint RoomId { get; set; }

    }
}

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
        public const byte GET_PERSONAL_STATISTICS_REQUEST_CODE = 34;
        public const byte GET_HIGH_SCORES_REQUEST_CODE = 35;

        public const byte CLOSE_ROOM_REQUEST_CODE = 41;
        public const byte START_GAME_REQUEST_CODE = 42;
        public const byte LEAVE_ROOM_REQUEST_CODE = 43;
        public const byte GET_ROOM_STATE_REQUEST_CODE = 45;

        public const byte LEAVE_GAME_REQUEST_CODE = 46;
        public const byte GET_QUESTION_REQUEST_CODE = 47;
        public const byte SUBMIT_ANSWER_REQUEST_CODE = 48;
        public const byte GET_GAME_RESULT_REQUEST_CODE = 49;

        public const byte CREATE_QUESTION_REQUEST_CODE = 60;

    }

    internal class LoginRequest
    {
        

        public LoginRequest(string? username, string? password)
        {
            Username = username;
            Password = password;
        }
        public string? Username { get; set; } = default!;
        public string? Password { get; set; } = default!;
    }
    internal class SignUpRequest: LoginRequest
    {
              
        public SignUpRequest(string username, string password,string email) : base(username, password)
        {
            
            Email = email;
        }
        
        public string Email { get; set; }
    }
    
    internal class JoinRoomRequest
    {
        
        public JoinRoomRequest(uint roomId)
        {
            RoomId = roomId;
        }
        public uint RoomId { get; set; }
    };

    internal class  CreateRoomRequest
    {
        

        public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
        {
            RoomName = roomName;
            MaxUsers = maxUsers;
            QuestionCount = questionCount;
            AnswerTimeout = answerTimeout;
        }
        
        public string RoomName { get; set; }
        public uint MaxUsers { get; set; }
        public uint QuestionCount { get; set; }
        public uint AnswerTimeout { get; set; }
            

    }

    internal class GetPlayersInRoomRequest
    {
        

        public GetPlayersInRoomRequest(uint roomId)
        {
            RoomId = roomId;
        }
        public uint RoomId { get; set; }

    }

    internal class SubmitAnswerRequest
    {


        public SubmitAnswerRequest(uint answerId)
        {
            AnswerId = answerId;
        }
        public uint AnswerId { get; set; }

    }

   

}

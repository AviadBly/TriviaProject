using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace clientAPI.Requests_and_Responses
{

    internal class test
    {
        int t;
        test(int g)
        {
            t = g;
        }
    }
    internal class Requests
    {
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
    internal class GetPlayersInRoom
    {
        uint roomId;

        public GetPlayersInRoom(uint roomId)
        {
            this.roomId = roomId;
        }
        public uint RoomId { get; set; }

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
}

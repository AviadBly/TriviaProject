using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace clientAPI.Requests
{
    internal class LoginRequest
    {
        string username;
        string password;
        public LoginRequest(string username, string password)
        {
            this.username = username;
            this.password = password;
        }
        public string Username { get; set; }
        public string Password { get; set; }

    }
    internal class SignUpRequest:  LoginRequest
    {
        string email;

        public SignUpRequest(string username, string password,string email) : base(username, password)
        {
            this.Username = username;
            this.Password = password;
            this.email = email;
        }
    }
    internal class GetPlayersInRoom
    {
        uint roomId;

        public GetPlayersInRoom(uint roomId)
        {
            this.roomId = roomId;
        }
    }
    struct JoinRoomRequest
    {
        unsigned int roomId;
    };

    struct CreateRoomRequest
    {
        std::string roomName;
        unsigned int maxUsers;
        unsigned int questionCount;
        unsigned int answerTimeout;
    };

}

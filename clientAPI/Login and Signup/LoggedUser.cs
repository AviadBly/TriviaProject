using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace clientAPI.Login_and_Signup
{
    public class User
    {
        public User(string name, uint id)
        {
            Name = name;
            Id = id;
        }
        public string Name { get; set; }
        public uint Id { get; set; }
    }
    internal class LoggedUser : User
    {
            

        public LoggedUser(string password, string name, string mail, uint id) : base(name, id)
        {
            Password = password;
            Mail = mail;
        }
        public string Password { get; set; }
        public string Mail { get; set; }
    }
}

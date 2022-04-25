using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace clientAPI.Login_and_Signup
{
    internal class LoggedUser
    {
     
        private string m_password;
        private string m_name;
        private string m_mail;

        public LoggedUser(string password, string name, string mail)
        {
            m_password = password;
            m_name = name;
            m_mail = mail;
        }
        public string Password { get; set; }
        public string Name { get; set; }
        public string Mail { get; set; }
    }
}

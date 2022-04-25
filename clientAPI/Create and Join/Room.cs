using clientAPI.Login_and_Signup;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace clientAPI.Create_and_Join
{
    internal class Room
    {
	struct RoomData
	{
		uint  id;
		string name;
		uint  maxPlayers;
		uint numOfQuestionsInGame;
		uint timePerQuestion;
		uint isActive;
	};

	private RoomData m_metadata;
	private List<LoggedUser>  m_users;

	}
}

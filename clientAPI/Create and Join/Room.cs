using clientAPI.Login_and_Signup;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace clientAPI.Create_and_Join
{
	public class RoomData
	{

		public uint Id { get; set; }
		public string Name { get; set; } = string.Empty;
		public uint MaxPlayers { get; set; }
		public uint NumOfQuestionsInGame { get; set; }
		public uint TimePerQuestion { get; set; }
		public bool IsActive { get; set; }

	};

	internal class Room
    {

		public Room(RoomData metaData, IList<string> players)
        {
			Metadata = metaData;
			Players = players;

		}
		
		public RoomData Metadata { get; set; }
		public IList<string> Players { get; set; }
	}
}

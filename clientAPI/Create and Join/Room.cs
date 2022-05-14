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
		public RoomData(uint id,string name,uint maxPlayers, uint numOfQuestions, uint timePerQuestion, bool isActive)
        {
			Id = id;
			Name = name;
			MaxPlayers = maxPlayers;
			NumOfQuestionsInGame = numOfQuestions;
			TimePerQuestion=timePerQuestion;
			IsActive = isActive;
        }

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

		public event Action<IList<string>> PlayersUpdated;

		public void UpdatePlayers(IList<string> players)
        {
			if (Players == null)
				Players = new List<string>();

			Players.Clear();
			
			foreach (var player in players)
            {
				Players.Add(player);
            }

			PlayersUpdated?.Invoke(Players);
        }
	}
}

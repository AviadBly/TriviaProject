using clientAPI.Create_and_Join;
using clientAPI.Requests_and_Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;


namespace clientAPI.Game
{
    /// <summary>
    /// Interaction logic for WaitingRoom.xaml
    /// </summary>
    public partial class WaitingRoom : Window
    {
        private Room room;
        List<string> players;
        public WaitingRoom()
        {
            players = getPlayers();
            InitializeComponent();
            showPlayers();
        }





        private List<string> getPlayers()
        {


            MainProgram.appClient.sender("", Requests.GET_PLAYERS_IN_ROOM_REQUEST_CODE);    //ask for rooms

            byte[] returnMsg = MainProgram.appClient.receiver();


            GetPlayersInRoomResponse getPlayersResponse = JsonHelpers.JsonFormatDeserializer.GetPlayersInRoomResponseDeserializer(returnMsg.Skip(5).ToArray());

            Console.Write(getPlayersResponse.ToString());
            //login failed
            if (getPlayersResponse.Status == Response.status_error)
            {
                return new List<string>();
            }

            return getPlayersResponse.Players;
        }


        private void showPlayers()
        {
            
            foreach (string player in this.players)
            {
                

                if (PlayerList.Items.Contains(player) == false)
                {

                        PlayerList.Items.Add(player);
                }

            }

        }
       
    }


}

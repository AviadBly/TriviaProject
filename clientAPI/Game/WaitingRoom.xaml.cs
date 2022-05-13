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
        private Room m_room;
        List<string> players;
        public WaitingRoom(RoomData metaData)
        {
            players = getPlayers();
            m_room = new Room(metaData, players);
            
            InitializeComponent();
            showPlayers();
        }


        //TO DO, ask getPlayers every 1 second
        private List<string> getPlayers()
        {


            MainProgram.appClient.sender("", Requests.GET_PLAYERS_IN_ROOM_REQUEST_CODE);    //ask for rooms

            byte[] returnMsg = MainProgram.appClient.receiver();


            GetPlayersInRoomResponse getPlayersResponse = JsonHelpers.JsonFormatDeserializer.GetPlayersInRoomResponseDeserializer(returnMsg.Skip(5).ToArray());

            
            if(getPlayersResponse == null)
            {
                return new List<string>();
            }

            //login failed
            if (getPlayersResponse.Status == GetPlayersInRoomResponse.roomNotFoundStatus)
            {
                MessageBox.Show("Closed Room");
                leaveRoom();
            }
            Console.WriteLine(getPlayersResponse.Players);

            Console.WriteLine(getPlayersResponse.Status);

            return getPlayersResponse.Players;
        }

        private void leaveRoom()
        {
            MessageBox.Show("Left Room");

            menu menuWindow = new menu(MainProgram.username);      //go to menu
            menuWindow.Show();
            Close();
        }

        private void showPlayers()
        {
            Current.Content = m_room.Metadata.Name.ToString();
            MaxPlayers.Content = m_room.Metadata.MaxPlayers.ToString();

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

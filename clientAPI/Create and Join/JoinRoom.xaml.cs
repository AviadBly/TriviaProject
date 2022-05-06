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
using clientAPI.Create_and_Join;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private List<Room> rooms;
        public JoinRoom()
        {
            
            InitializeComponent();
            this.rooms = getRooms();
            //maybe check here if rooms isnt empty
            
            showActiveRooms();
        }

        
        private void clickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu();
            menu.Show();
        }

        
        private void showActiveRooms()
        {
            foreach(Room room in this.rooms)
            {
                if(room.Metadata.IsActive==true)
                {
                    string fullRoom = room.Metadata.Name;
                    if (roomsList.Items.Contains(fullRoom)==false)
                    {
                        
                        roomsList.Items.Add(fullRoom);
                    }
                    
                }
                
            }
        }

        

        private List<Room> getRooms()
        {
            

            MainProgram.appClient.sender("", Requests.GET_ROOM_REQUEST);    //ask for rooms

            byte[] returnMsg = MainProgram.appClient.receiver();

            
            GetRoomsResponse getRoomsResponse = JsonHelpers.JsonFormatDeserializer.GetRoomsResponseDeserializer(returnMsg.Skip(5).ToArray());

            Console.Write(getRoomsResponse.ToString());
            //login failed
            if (getRoomsResponse.Status == Response.status_error)
            {
                return new List<Room>();
            }

            return getRoomsResponse.Rooms;
        }

        private void clickJoin(object sender, RoutedEventArgs e)
        {
            uint id = 0;
            if (roomsList.SelectedItem != null)
            {

                
                string item= roomsList.SelectedItem.ToString();
                foreach (Room room in this.rooms)
                {
                    if (room.Metadata.Name == item)
                    {
                        id = room.Metadata.Id;
                        break;
                    }
                }
                if(id==0)
                {
                    MessageBox.Show("Selection Error!");
                }
                else
                {
                    sendJoinRoomRequest(id);
                }
               
            }
            else
            {
                MessageBox.Show("Selection Empty!");
            }
              
                    
        }

        private bool sendJoinRoomRequest(uint roomId)
        {
            JoinRoomRequest joinRoomRequest = new JoinRoomRequest(roomId);

            byte[] data = JsonHelpers.JsonFormatSerializer.joinRoomSerializer(joinRoomRequest);

            MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.JOIN_ROOM_REQUEST_CODE);

            byte[] returnMsg = MainProgram.appClient.receiver();
            Console.Write(returnMsg);

            JoinRoomResponse joinRoomResponse = JsonHelpers.JsonFormatDeserializer.JoinRoomResponseDeserializer(returnMsg.Skip(5).ToArray());

            //login failed
            if (joinRoomResponse.Status == Response.status_error)
            {
                return false;
            }
            sendGetPlayersInRoom();
            return true;
        }

        private List<string> sendGetPlayersInRoom()
        {
            MainProgram.appClient.sender("", Requests.GET_PLAYERS_IN_ROOM_REQUEST_CODE);    //ask for rooms

            byte[] returnMsg = MainProgram.appClient.receiver();


            GetPlayersInRoomResponse getPlayersInRoomResponse = JsonHelpers.JsonFormatDeserializer.GetPlayersInRoomResponseDeserializer(returnMsg.Skip(5).ToArray());

            Console.Write(getPlayersInRoomResponse.ToString());
            //login failed
            if (getPlayersInRoomResponse.Status == Response.status_error)
            {
                return null;
            }

            return getPlayersInRoomResponse.Players;
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            
        }
    }
}

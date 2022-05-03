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
        
        public JoinRoom()
        {
            
            InitializeComponent();
            List<Room> rooms = getRooms();
            //maybe check here if rooms isnt empty
            showActiveRooms(rooms);
        }

        
        private void clickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu();
            menu.Show();
        }

        
        private void showActiveRooms(List<Room> rooms)
        {
            //TO DO, AVIAD,  show the rooms on the screen
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
            string id;
            if (roomsList.SelectedItem != null)
            {
                id = roomsList.SelectedItem.ToString();
                uint fixedId = Convert.ToUInt32(id);
                JoinRoomRequest joinRoomRequest = new JoinRoomRequest(fixedId);

                byte[] data = JsonHelpers.JsonFormatSerializer.joinRoomSerializer(joinRoomRequest);

                MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.JOIN_ROOM_REQUEST_CODE);

                byte[] returnMsg = MainProgram.appClient.receiver();
                Console.Write(returnMsg);

                JoinRoomResponse joinRoomResponse = JsonHelpers.JsonFormatDeserializer.JoinRoomResponseDeserializer(returnMsg.Skip(5).ToArray());

                //login failed
                if (joinRoomResponse.Status == Response.status_error)
                {
                    return;
                }
            }
            else
            {
                MessageBox.Show("Selection Empty!");
            }
              
                    
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            
        }
    }
}

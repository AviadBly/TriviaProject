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
using clientAPI.GameFolder;
using System.Windows.Threading;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        private List<Room> rooms;
        private DispatcherTimer dispatcherTimer;

        private const int GET_ROOMS_REFRESH_TIME = 3; //in seconds
        public JoinRoom()
        {

            InitializeComponent();

            //  DispatcherTimer setup
            dispatcherTimer = new System.Windows.Threading.DispatcherTimer();
            dispatcherTimer.Tick += new EventHandler(dispatcherTimer_Tick);
            dispatcherTimer.Interval = new TimeSpan(0, 0, GET_ROOMS_REFRESH_TIME);
            dispatcherTimer.Start();
            
        }

        private void dispatcherTimer_Tick(object sender, EventArgs e)
        {
            rooms = getRooms();
            showActiveRooms();
            
                       
        }

        private void clickExit(object sender, RoutedEventArgs e)
        {

            dispatcherTimer.Stop();
            Close();
            menu.goToMenu();
           
        }

        
        private void showActiveRooms()
        {
            roomsList.Items.Clear();
            if(rooms == null) { return; }

            foreach (Room room in this.rooms)
            {
                
                string fullRoom = room.Metadata.Name;
                if (!roomsList.Items.Contains(fullRoom))
                {                       
                    roomsList.Items.Add(fullRoom);
                }                                               
            }
           
        }
       
        private List<Room> getRooms()
        {
            

            MainProgram.appClient.sender("", Requests.GET_ROOM_REQUEST);    //ask for rooms

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();
            

            if (returnMsg.IsErrorMsg)
            {
              
                MessageBox.Show(returnMsg.Message.ToString());
                return new List<Room>(); ;

            }

            GetRoomsResponse getRoomsResponse = JsonHelpers.JsonFormatDeserializer.GetRoomsResponseDeserializer(returnMsg.Message);
            
            return getRoomsResponse.Rooms;
        }

        private void clickJoin(object sender, RoutedEventArgs e)
        {
            
            rooms = getRooms();
            dispatcherTimer.Stop();
            if (roomsList.SelectedItem == null)
            {
                MessageBox.Show("Selection Empty!");
                return;
            }

            string? roomName = roomsList.SelectedItem.ToString();

            if(roomName == null)
            {
                MessageBox.Show("Selection Error!");
                return;
            }
            RoomData? roomMetaData = getRoomData(roomName);

            if(roomMetaData == null)
            {
                MessageBox.Show("Room not found");
                return;
            }

            if (sendJoinRoomRequest(roomMetaData.Id))
            {
                
                WaitingRoom waitingRoom = new WaitingRoom(roomMetaData, false);
                waitingRoom.WindowStartupLocation = WindowStartupLocation.CenterScreen;
                waitingRoom.Show();
                Close();
            }
                            
        }

        private RoomData? getRoomData(string roomName)
        {
            foreach (Room room in rooms)
            {
                if (room.Metadata.Name == roomName)
                {
                    return room.Metadata;
                }
            }

            return null;
        }

        private bool sendJoinRoomRequest(uint roomId)
        {
            JoinRoomRequest joinRoomRequest = new JoinRoomRequest(roomId);

            byte[] data = JsonHelpers.JsonFormatSerializer.joinRoomSerializer(joinRoomRequest);

            MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.JOIN_ROOM_REQUEST_CODE);

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();
            

            if (returnMsg.IsErrorMsg)   //if error
            {
                MessageBox.Show(Encoding.UTF8.GetString(returnMsg.Message));
                return false;
            }

            JoinRoomResponse joinRoomResponse = JsonHelpers.JsonFormatDeserializer.JoinRoomResponseDeserializer(returnMsg.Message);

            return true;
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            
        }
    }
}

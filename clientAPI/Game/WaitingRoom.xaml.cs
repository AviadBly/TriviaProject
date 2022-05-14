using clientAPI.Create_and_Join;
using clientAPI.Requests_and_Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
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
        private const int PLAYERS_UPDATE_INTERVAL_SECONDS = 1;

        private Room m_room;

        private CancellationTokenSource m_updatePlayersCancellationToken;
        private Task m_updatePlayersTask;
        private bool isAdmin;
        
        public WaitingRoom(RoomData metaData, bool isUserAdmin)
        {
            InitializeComponent();
            isAdmin = isUserAdmin;
            m_room = new Room(metaData, new List<string>());
            m_room.PlayersUpdated += RoomPlayersUpdated;

            this.Loaded += WaitingRoom_Loaded;
            this.Closed += WaitingRoom_Closed;

            // Task.Run(TimelyUpdatePlayers);
        }

        private void WaitingRoom_Loaded(object sender, RoutedEventArgs e)
        {
            if (m_updatePlayersCancellationToken != null)
            {
                m_updatePlayersCancellationToken?.Dispose();
                m_updatePlayersCancellationToken = null;
            }

            m_updatePlayersCancellationToken = new CancellationTokenSource();
            m_updatePlayersTask = Task.Run(TimelyUpdatePlayers, m_updatePlayersCancellationToken.Token);
        }

        private void WaitingRoom_Closed(object? sender, EventArgs e)
        {
            m_updatePlayersCancellationToken?.Cancel();
            m_updatePlayersTask.Wait(TimeSpan.FromSeconds(PLAYERS_UPDATE_INTERVAL_SECONDS * 3));
            
            m_updatePlayersTask.Dispose();
            m_updatePlayersTask = null;
        }

        private void UpdatePlayers()
        {
            var players = getPlayers();
            m_room.UpdatePlayers(players);
        }

        private void TimelyUpdatePlayers()
        {
            while (!m_updatePlayersCancellationToken.IsCancellationRequested)
            {
                UpdatePlayers();
                Task.Delay(TimeSpan.FromSeconds(PLAYERS_UPDATE_INTERVAL_SECONDS)).Wait();
            }
        }

        private void RoomPlayersUpdated(IList<string> players)
        {
            if (!Dispatcher.CheckAccess())
                Dispatcher.Invoke(() => showPlayers(players));
            else
                showPlayers(players);
        }

        //TO DO, ask getPlayers every 1 second
       
        private IList<string> getPlayers()
        {
            MainProgram.appClient.sender("", Requests.GET_ROOM_STATE_REQUEST_CODE);    //ask for rooms

            byte[] returnMsg = MainProgram.appClient.receiver();


            GetRoomStateResponse getRoomStateResponse = JsonHelpers.JsonFormatDeserializer.GetRoomStateResponseDeserializer(returnMsg.Skip(5).ToArray());

            Console.WriteLine(getRoomStateResponse._players);

            Console.WriteLine(getRoomStateResponse.Status);
            switch (getRoomStateResponse.Status)
            {
                
                //if room wasnt found, it is closed
                //so go to menu
                case GetRoomStateResponse.statusRoomNotFound:

                    menu menu = new menu(MainProgram.MainUsername);
                    menu.Show();
                    
                    Close();
                    break;

                case GetRoomStateResponse.status_ok:    //if room found
                    if (getRoomStateResponse._hasGameBegun)
                    {
                        //next, go to game room, not for this version
                    }
                    
                    break;

                case GetRoomStateResponse.status_error: //some error
                    MessageBox.Show("error");
                    Close();
                    break;
            }
            

            return getRoomStateResponse._players;
        }

        private void leaveRoom(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Left Room");

            menu menuWindow = new menu(MainProgram.MainUsername);      //go to menu
            menuWindow.Show();
            Close();
        }

        private void showPlayers(IList<string> players)
        {
            Current.Content = m_room.Metadata.Name.ToString();
            MaxPlayers.Content = m_room.Metadata.MaxPlayers.ToString();

            foreach (string player in players)
            {
                if (!PlayerList.Items.Contains(player))
                {
                    PlayerList.Items.Add(player);
                }
            }
        }

        
    }


}

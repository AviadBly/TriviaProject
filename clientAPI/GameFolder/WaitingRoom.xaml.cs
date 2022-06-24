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
using clientAPI.GameFolder;

namespace clientAPI.GameFolder
{
    /// <summary>
    /// Interaction logic for WaitingRoom.xaml
    /// </summary>
    public partial class WaitingRoom : Window
    {
        private const int PLAYERS_UPDATE_INTERVAL_SECONDS = 3;

        private Room m_room;

        private CancellationTokenSource m_updatePlayersCancellationToken;
        private Task m_updatePlayersTask;
        private bool isAdmin;
        
//Instead of disapatcher timer, "Task" was used in this file.
        public WaitingRoom(RoomData metaData, bool isUserAdmin)
        {
            InitializeComponent();
            isAdmin = isUserAdmin;
            //checks for each client if he's the admin. only admin can start the game.
            if(isAdmin)
            {
                StartButton.Visibility = Visibility.Visible;
            }
            m_room = new Room(metaData, new List<string>());
            m_room.PlayersUpdated += RoomPlayersUpdated;

            this.Loaded += WaitingRoom_Loaded;
            
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
            m_updatePlayersTask.Wait(TimeSpan.FromSeconds(PLAYERS_UPDATE_INTERVAL_SECONDS * 0.1));
            
            if (m_updatePlayersTask.IsCompleted)
                m_updatePlayersTask.Dispose();
            leaveRoom();
            m_updatePlayersTask = null;
        }

        //will add new players joined, and remove the ones who left.
        private void UpdatePlayers()
        {
            var players = getPlayers();

            
            if (players.Item1 == GetRoomStateResponse.statusRoomNotFound)    //go back to menu
            {
                Application.Current.Dispatcher.Invoke((Action)delegate {
                    menu.goToMenu();

                    stopTask();

                    byte status = sendLeaveRoom();
                    
                    if (status == Response.status_error) {
                        return;
                    }
                    Close();
                });
                
            }
            
            m_room.UpdatePlayers(players.Item2);
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
        
        private void stopTask()
        {
            m_updatePlayersCancellationToken?.Cancel();
            m_updatePlayersTask.Wait(TimeSpan.FromSeconds(PLAYERS_UPDATE_INTERVAL_SECONDS * 0.1));
        }
        
       
        private (byte, IList<string>) getPlayers()
        {
            MainProgram.appClient.sender("", Requests.GET_ROOM_STATE_REQUEST_CODE);    //ask for rooms

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();

            GetRoomStateResponse getRoomStateResponse = JsonHelpers.JsonFormatDeserializer.GetRoomStateResponseDeserializer(returnMsg.Message);

            if (getRoomStateResponse == null)
            {
                Console.WriteLine("Received empty or wrong answer from server");
                return (0, new List<string>());
            }

            
            switch (getRoomStateResponse.Status)
            {
                
                //if room wasnt found, it is closed
                //so go to menu
                case GetRoomStateResponse.statusRoomNotFound:

                    return (GetRoomStateResponse.statusRoomNotFound, new List<string>());
                    
                case Response.status_ok:    //if room found
                    if (getRoomStateResponse.HasGameBegun)
                    {
                        byte status = sendStartGame();
                        if(status != Response.status_ok)
                        {
                            break;
                        }
                        Application.Current.Dispatcher.Invoke((Action)delegate {
                            stopTask();
                            GameWindow gameWindow = new GameWindow(m_room.Metadata.TimePerQuestion, m_room.Metadata.Name, m_room.Metadata.NumOfQuestionsInGame);
                            gameWindow.Show();
                            Close();
                        });                                               
                    }                   
                    break;

                case GetRoomStateResponse.status_error: //some error
                    MessageBox.Show("error");
                    Close();
                    break;
            }
            

            return (1, getRoomStateResponse.Players);
        }

        private void leaveRoom()
        {
                      
            byte status = sendLeaveRoom();

            if(status == Response.status_error) {
                return;
            }

            menu.goToMenu();
            Close();
        }

        private byte sendLeaveRoom()
        {
            if (isAdmin)
            {
                MainProgram.appClient.sender("", Requests.CLOSE_ROOM_REQUEST_CODE);    
            }
            else
            {
                MainProgram.appClient.sender("", Requests.LEAVE_ROOM_REQUEST_CODE);
            }

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();
            Console.WriteLine(returnMsg);

            if (returnMsg.IsErrorMsg)
            {
                MessageBox.Show(returnMsg.Message.ToString());                
                return Response.status_error;
            }

            if (isAdmin)
            {
                CloseRoomResponse closeRoomResponse = JsonHelpers.JsonFormatDeserializer.CloseRoomResponseDeserializer(returnMsg.Message);
                return closeRoomResponse.Status;
            }
            else
            {
                LeaveRoomResponse leaveRoomResponse = JsonHelpers.JsonFormatDeserializer.LeaveRoomResponseDeserializer(returnMsg.Message);
                return leaveRoomResponse.Status;
            }

            
        }

        private void showPlayers(IList<string> players)
        {
            Current.Content = m_room.Metadata.Name.ToString();
            MaxPlayers.Content = m_room.Metadata.MaxPlayers.ToString();

            PlayerList.Items.Clear();

            foreach (string player in players)
            {
                
                PlayerList.Items.Add(player);
                              
            }
            
        }

        private void StartClick(object sender, RoutedEventArgs e)
        {
            byte status = sendStartGame();

            if (status == Response.status_ok)
            {
                GameWindow gameWindow = new GameWindow(m_room.Metadata.TimePerQuestion, m_room.Metadata.Name, m_room.Metadata.NumOfQuestionsInGame);
                gameWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
                gameWindow.Show();
                Close();
            }

        }

        public byte sendStartGame()
        {
            stopTask();
            MainProgram.appClient.sender("", Requests.START_GAME_REQUEST_CODE);

            ReceivedMessage returnMsg = MainProgram.appClient.receiver();

            if (returnMsg.IsErrorMsg)   //if error
            {
                MessageBox.Show(Encoding.UTF8.GetString(returnMsg.Message));
                return Response.status_error;
            }

            StartGameResponse startGameResponse = JsonHelpers.JsonFormatDeserializer.StartGameResponseDeserializer(returnMsg.Message);


            return startGameResponse.Status;
        }
    }


}

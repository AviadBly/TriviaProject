using clientAPI.Create_and_Join;
using clientAPI.Login_and_Signup;
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
static class constants
{
    public const int MAXQUESTIONS = 10;
}

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for CreateRoom.xaml
    /// </summary>
    public partial class CreateRoom : Window
    {
        
        public CreateRoom()
        {
            
            InitializeComponent();
        }

        private void clickExit(object sender, RoutedEventArgs e)
        {
            this.Close();
            menu menu = new menu();
            menu.Show();
        }

        private void clickCreate(object sender, RoutedEventArgs e)
        {
            uint players = Convert.ToUInt32(Players.Text);
            uint time = Convert.ToUInt32(Time.Text);

            CreateRoomRequest createRoomRequest = new CreateRoomRequest(roomName.Text,players, constants.MAXQUESTIONS,time);

            

            byte[] data = JsonHelpers.JsonFormatSerializer.createSerializer(createRoomRequest);

            MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.CREATE_ROOM_CODE);

            byte[] returnMsg = MainProgram.appClient.receiver();
            Console.Write(returnMsg);

            CreateRoomResponse createRoomResponse = JsonHelpers.JsonFormatDeserializer.CreateRoomResponseDeserializer(returnMsg.Skip(5).ToArray());
            Console.Write(createRoomResponse);
            //login failed
            if (createRoomResponse.Status == Response.status_error)
            {
                return;
            }

            

        }
    }
}

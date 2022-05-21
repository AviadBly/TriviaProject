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
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text.Json;
using clientAPI.Requests_and_Responses;
using clientAPI.JsonHelpers;
using clientAPI;
using clientAPI.Create_and_Join;
using System.Collections.Generic;
using System;

namespace clientAPI
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {

        
        public LoginWindow()
        {
            
            
            InitializeComponent();
            //List<Room> list = new List<Room>();
            //IList<string> list2 = new List<string>();
            //list2.Add("first");

            //list.Add(new Room(new RoomData(1, "shahar", 3, 4, 5, true), list2));
            //GetRoomsResponse g = new GetRoomsResponse(list, 4);

            //string j = JsonSerializer.Serialize(g);
            //Console.WriteLine();

            //Console.WriteLine(j);
            //Console.WriteLine();

            //string jsonString = j;//"{\"Rooms\":[{\"Metadata\":{\"Id\":1,\"IsActive\":true,\"MaxPlayers\":5,\"Name\":\"firstR\",\"NumOfQuestionsInGame\":6,\"TimePerQuestion\":12},\"Players\":[\"sha\"]}],\"Status\":2}";
            //Console.WriteLine(jsonString);
            //Console.WriteLine();
            //GetRoomsResponse? response = JsonSerializer.Deserialize<GetRoomsResponse>(jsonString);

            //Console.WriteLine(response.Rooms.ToString());
        }


        private void clickLogin(object sender, RoutedEventArgs e)
        {
          
            string username = UsernameText.Text;
            string password = PasswordText.Password.ToString();

            
            if (username == null || password == null)
            {
                MessageBox.Show("Please Enter a valid username!");
                return;
            }
            else
            {
                //create a login request
                LoginRequest loginRequest = new LoginRequest(username, password);

                byte[] data = JsonHelpers.JsonFormatSerializer.loginSerializer(loginRequest);

                MainProgram.appClient.sender(System.Text.Encoding.Default.GetString(data), Requests.LOGIN_REQUEST_CODE);

                ReceivedMessage returnMsg = MainProgram.appClient.receiver();

                if (returnMsg.IsErrorMsg)   //if error
                {
                    //MessageBox.Show("Error! Username or password is incorrect!");
                    MessageBox.Show(returnMsg.Message.ToString());
                    return;
                }

                Console.Write(returnMsg);

                LoginResponse loginResponse = JsonHelpers.JsonFormatDeserializer.loginResponseDeserializer(returnMsg.Message);

                //login failed
                if (loginResponse.Status == Response.status_error)
                {
                    
                }



                MainProgram.MainUsername = username;
                menu menuWindow = new menu(username);
                menuWindow.Show();
                Close();
            }

           
        }
        
        private void signClick(object sender, RoutedEventArgs e)
        {
            
            SignUpWindow window = new SignUpWindow();          
            window.Show();
            Close();
        }

        private void PasswordBox_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                clickLogin(this, new RoutedEventArgs());
            }
        }
    }
}

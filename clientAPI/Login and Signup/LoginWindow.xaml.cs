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
using clientAPI.GameFolder;
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


            //SortedDictionary<uint, string> dict = new SortedDictionary<uint, string>();
            //dict.Add(0, "Golda Meir ");
            //dict.Add(1, "*David Ben Gurion ");
            //dict.Add(2, "Benyamin Netanyhau ");
            //dict.Add(3, "Ariel Sharon ");
            //Question question = new Question("Who was the first prime minisiter of Israel? ", dict);
            //string jj = "{\"QuestionText\":\"How are you today??\",\"Answers\":{\"1\":\"Fine\",\"2\":\"okay\",\"3\":\"brara\",\"4\":\"kill me\"},\"Status\":4}";
            //GetQuestionResponse qq = JsonHelpers.JsonFormatDeserializer.GetQuestionResponseDeserializer(System.Text.Encoding.UTF8.GetBytes(jj));

            //GetQuestionResponse getQuestionResponse = new GetQuestionResponse(4, question.QuestionText, dict);
            //string resultStringJson = JsonSerializer.Serialize(getQuestionResponse);
            //Console.WriteLine(resultStringJson);
            ////            "{\"Answers\":{\"0\":\"Golda Meir \",\"1\":\"*David Ben Gurion \",\"2\":\"Benyamin Netanyhau \",\"3\":\"Ariel Sharon \"},\"QuestionText\":\"Who was the first prime minisiter of Israel? \",\"Status\":4}"
            //string test = "{\"Answers\":[[0,\"Golda Meir \"],[1,\"*David Ben Gurion \"],[2,\"Benyamin Netanyhau \"],[3,\"Ariel Sharon \"]],\"QuestionText\":\"Who was the first prime minisiter of Israel? \",\"Status\":2}";
            
            //GetQuestionResponse? response = JsonSerializer.Deserialize<GetQuestionResponse>(test);

            //GameWindow g = new GameWindow();

            //Question q = g.GetNextQuestion();
            //Console.WriteLine(q);
            //List<Room> list = new List<Room>();
            //IList<string> list2 = new List<string>();
            //list2.Add("first");

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
                menuWindow.WindowStartupLocation = WindowStartupLocation.CenterScreen;
                menuWindow.Show();
                Close();
            }

           
        }
        
        private void signClick(object sender, RoutedEventArgs e)
        {
            
            SignUpWindow window = new SignUpWindow();
            window.WindowStartupLocation = WindowStartupLocation.CenterScreen;
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

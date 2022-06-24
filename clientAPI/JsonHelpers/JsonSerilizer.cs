using clientAPI.Requests_and_Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;


//applies for all: serializes the specific data and sends it to server for updating.

namespace clientAPI.JsonHelpers
{
    internal class JsonFormatSerializer
    {
        public static byte[] loginSerializer(LoginRequest loginRequest)
        {

            string resultStringJson = JsonSerializer.Serialize(loginRequest);
            Console.WriteLine(resultStringJson);
            return Encoding.UTF8.GetBytes(resultStringJson);

        }

        public static byte[] signUpSerializer(SignUpRequest signUpRequest)
        {
            string resultStringJson =  JsonSerializer.Serialize(signUpRequest);
            Console.WriteLine(resultStringJson);
            return Encoding.UTF8.GetBytes(resultStringJson.ToString());
        }

        public static byte[] getPlayersInRoomSerializer(GetPlayersInRoomRequest getPlayersInRoomRequest)
        {
            string resultStringJson = JsonSerializer.Serialize(getPlayersInRoomRequest);
            Console.WriteLine(resultStringJson);
            return Encoding.UTF8.GetBytes(resultStringJson.ToString());
        }

        public static byte[] joinRoomSerializer(JoinRoomRequest joinRoomRequest)
        {
            string resultStringJson = JsonSerializer.Serialize(joinRoomRequest);
            Console.WriteLine(resultStringJson);
            return Encoding.UTF8.GetBytes(resultStringJson.ToString());
        }

        public static byte[] createSerializer(CreateRoomRequest createRoomRequest)
        {
            string resultStringJson = JsonSerializer.Serialize(createRoomRequest);
            Console.WriteLine(resultStringJson);
            return Encoding.UTF8.GetBytes(resultStringJson.ToString());
        }

        public static byte[] SubmitAnswerSerializer(SubmitAnswerRequest submitAnswerRequest)
        {
            string resultStringJson = JsonSerializer.Serialize(submitAnswerRequest);
            Console.WriteLine(resultStringJson);
            return Encoding.UTF8.GetBytes(resultStringJson.ToString());
        }

        public static byte[] CreateQuestionSerializer(CreateQuestionRequest createQuestionRequest)
        {
            string resultStringJson = JsonSerializer.Serialize(createQuestionRequest);
            Console.WriteLine(resultStringJson);
            return Encoding.UTF8.GetBytes(resultStringJson.ToString());
        }

    }

}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using clientAPI.Requests_and_Responses;
using System.Text.Json;

namespace clientAPI.JsonHelpers
{
    internal class JsonFormatDeserilizer
    {
        //byte[0] - code, byte[1,2,3,4] - length, rest = jsonstring
        public static LoginResponse? loginResponseDeserilizer(byte[] buffer)
        {
            //byte code = buffer[0];

            string jsonString = System.Text.Encoding.Default.GetString(buffer);
            //jsonString = jsonString.Substring(5);

            LoginResponse? l = JsonSerializer.Deserialize<LoginResponse>(jsonString);

            return l;
        }
    }
}

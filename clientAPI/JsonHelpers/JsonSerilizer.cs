using clientAPI.Requests_and_Responses;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;

namespace clientAPI.JsonHelpers
{
    internal class JsonFormatSerilizer
    {
        public static byte[] loginSerilizer(LoginRequest loginRequest)
        {

            string resultStringJson = JsonSerializer.Serialize(loginRequest);

            return Encoding.ASCII.GetBytes(resultStringJson);

        }


    }

}

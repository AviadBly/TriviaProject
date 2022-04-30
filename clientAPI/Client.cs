using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text.Json;
using clientAPI.Requests_and_Responses;

namespace clientAPI
{
    public class Client
    {
        private NetworkStream m_socket;

        
            public Client(String server, Int32 port)
        {
            try
            {
                
                TcpClient client = new TcpClient(server, port);
              
                this.m_socket = client.GetStream();

              
                //// Close everything.
                //stream.Close();
                //client.Close();
            }
            catch (Exception ex) //error with creating socket
            {
                Console.WriteLine(ex.ToString());
            }

            
        }
        private byte[] intToBytes(int numInteger)
        {
            byte[] intBytes = BitConverter.GetBytes(numInteger);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(intBytes);

            return intBytes;
        }
        public void sender(string msg, byte code)
        {
            if (m_socket == null)
            {
                return;
            }

            int len = msg.Length;
            //code - 1 byte, len - 4 bytes, msg - depends on length
            byte[] finalMsg = new byte[1 + 4 + msg.Length];
            byte[] intBytes = intToBytes(len);
            finalMsg[0] = code;
            //len - 4 bytes
            for (int i = 1; i <= 4; i++)
            {
                finalMsg[i] = intBytes[i - 1];
            }
            
            for(int i = 5; i < len + 5; i++)
            {
                finalMsg[i] = (byte)(msg[i - 5]);
            }
            
            //write the msg with the format: code + length of data + data
            this.m_socket.Write(finalMsg);
        }

        public byte[] receiver()
        {

            // Buffer to store the response bytes.
            byte[] data = new Byte[256];

            // String to store the response ASCII representation.
            String responseData = String.Empty;

            // Read the first batch of the TcpServer response bytes.
            Int32 bytes = this.m_socket.Read(data, 0, data.Length);
            responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
            Console.WriteLine("Received: {0}", responseData);

            return data;
        }

    }
}

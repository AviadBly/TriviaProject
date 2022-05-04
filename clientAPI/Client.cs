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


        //returns a byte array
        public byte[] receiver()
        {

            // Buffer to store the response bytes.
            byte[] serverBytes = new Byte[1024];

            // String to store the response ASCII representation.
            String responseData = String.Empty;
            try
            {
                // Read the first batch of the TcpServer response bytes.
                Int32 bytes = this.m_socket.Read(serverBytes, 0, serverBytes.Length);
            }
            catch (System.IO.IOException e)
            {
                if (e.Source != null)
                    Console.WriteLine("IOException source: {0}", e.Source);
                return new byte[0];
            }
            

            byte[] lenBytes = serverBytes.Skip(1).Take(4).ToArray();

            // If the system architecture is little-endian (that is, little end first),
            // reverse the byte array.
            if (BitConverter.IsLittleEndian)
                Array.Reverse(lenBytes);

            int msgLength = BitConverter.ToInt32(lenBytes, 0);
                                    //code + len + data
            byte[] trimedMsg = serverBytes.Take(1 + 4 + msgLength).ToArray();
            responseData = System.Text.Encoding.UTF8.GetString(trimedMsg);
            Console.WriteLine("Received: {0}", responseData);

            return trimedMsg;
        }

    }
}

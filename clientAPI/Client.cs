using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text.Json;
using clientAPI.Requests;

namespace clientAPI
{
    internal class Client
    {
        private NetworkStream? m_socket;
        public Client(String server)
        {
            try
            {
                // Create a TcpClient.
                // Note, for this client to work you need to have a TcpServer
                // connected to the same address as specified by the server, port
                // combination.
                Int32 port = 8200;
                TcpClient client = new TcpClient(server, port);

                // Translate the passed message into ASCII and store it as a Byte array.
                //Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);

                // Get a client stream for reading and writing.
                //  Stream stream = client.GetStream();

                this.m_socket = client.GetStream();

              // Send the message to the connected TcpServer.
                //stream.Write(data, 0, data.Length);

                //Console.WriteLine("Sent: {0}", message);

                //// Receive the TcpServer.response.

                //// Buffer to store the response bytes.
                //data = new Byte[256];

                //// String to store the response ASCII representation.
                //String responseData = String.Empty;

                //// Read the first batch of the TcpServer response bytes.
                //Int32 bytes = stream.Read(data, 0, data.Length);
                //responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                //Console.WriteLine("Received: {0}", responseData);

                //// Close everything.
                //stream.Close();
                //client.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }

            
        }

        public void sender(string msg, byte code)
        {
            string len = Convert.ToString(msg.Length, 2).PadLeft(32, '0');

            string finalMsg = code + len + msg;
            
            if(m_socket == null)
            {
                return;
            }
            //write the msg with the format: code + length of data + data
            this.m_socket.Write(Encoding.ASCII.GetBytes(finalMsg));
        }

        public byte[] receiver()
        {
            byte[] msgBytes = new byte[1096];

            return msgBytes;
        }

    }
}

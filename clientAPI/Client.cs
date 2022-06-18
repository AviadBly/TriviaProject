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
using System.Security.Cryptography;
using System.Numerics;

namespace clientAPI
{
    public class ReceivedMessage
    {
        public ReceivedMessage(byte[] message, bool isErrorMsg, uint length, byte code)
        {
            Message = message;
            IsErrorMsg = isErrorMsg;
            Length = length;
            Code = code;
        }
        public ReceivedMessage()
        {
            Message = new byte[0];
            IsErrorMsg = true;
            Length = 0;
            Code = 0;
        }
        public byte[] Message { get; set; }
        public bool IsErrorMsg { get; set; }
        public uint Length { get; set; }    
        public byte Code { get; set; }

    }
    public class Client
    {
        private NetworkStream m_socket;
        AesEncryptor m_encryptor;

        private byte[] sharedKey;
            public Client(String server, Int32 port) {
            try
            {
                
                TcpClient client = new TcpClient(server, port);
              
                this.m_socket = client.GetStream();
                m_socket.ReadTimeout = 60000;   //we should lower this later, but for now we are just testing

                KeyExchangeManager keyManager = new KeyExchangeManager(this);

                byte[] secretKey = keyManager.getSecretKey();


                m_encryptor = new AesEncryptor(secretKey);

                //// Close everything.
                //stream.Close();
                //client.Close();
            }
            catch (Exception ex) //error with creating socket
            {
                Console.WriteLine(ex.ToString());
            }

            
        }
       
        private void printByteArray(byte[] arr, string msg)
        {
            Console.WriteLine(msg + ", length =" + arr.Length);
            for (int i = 0; i < arr.Length; i++)
            {
                Console.Write(arr[i] + ", ");
            }
            Console.WriteLine("\n");
        }

        private byte[] intToBytes(int numInteger)
        {
            byte[] intBytes = BitConverter.GetBytes(numInteger);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(intBytes);

            return intBytes;
        }

        private void addCodeAndLength(byte[] finalMsg, int msgLen, byte code)
        {
            
            //code - 1 byte, len - 4 bytes, msg - depends on length
            
            byte[] intBytes = intToBytes(msgLen);
            finalMsg[0] = code;
            //len - 4 bytes
            for (int i = 1; i <= 4; i++)
            {
                finalMsg[i] = intBytes[i - 1];
            }
        }
        public void sender(string msg, byte code)
        {
            
            byte[] data = new byte[msg.Length];
            for (int i = 0; i < msg.Length; i++)
            {
                data[i] = (byte)(msg[i]);
            }
            data = m_encryptor.encrypt(data);

            byte[] finalMsg = new byte[1 + 4 + data.Length];
            

            addCodeAndLength(finalMsg, data.Length, code);
                       
            
            printByteArray(data, "DATA encryptd:");

            for (int i = 5; i < data.Length + 5; i++)
            {
                finalMsg[i] = data[i - 5];
            }

            printByteArray(finalMsg, "final msg:");

            safeSend(finalMsg);

        }

        public void sender(byte[] msg, byte code)
        {
            if (m_socket == null)
            {
                return;
            }

            byte[] finalMsg = new byte[1 + 4 + msg.Length];
            addCodeAndLength(finalMsg, msg.Length, code);

            for (int i = 5; i < msg.Length + 5; i++)
            {
                finalMsg[i] = msg[i - 5];
            }

            //printByteArray(finalMsg, "final msg:");
            safeSend(finalMsg);
        }

        private void safeSend(byte[] message)
        {
            try
            {

                //write the msg with the format: code + length of data + data
                this.m_socket.Write(message);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error with server: " + ex.Message);
            }
        }

        //returns a byte array and a boolean indicating if its an error msg
        public ReceivedMessage receiver(bool isEncrypted = true)
        {
            
            ReceivedMessage serverMsg = new ReceivedMessage();
            byte[] metaDataBytes = new byte[5];

            
            try
            {
                
                // First, read the msg length
                Int32 bytes = this.m_socket.Read(metaDataBytes, 0, 5);        // 1 - code + 4 - len = 5
                Console.WriteLine("read length:" + bytes);
            }
            catch (System.IO.IOException e)
            {
                if (e.Source != null)
                    Console.WriteLine("IOException source: {0}", e.Source);
                return new ReceivedMessage();
            }

            serverMsg.Code = metaDataBytes[0];
            metaDataBytes = metaDataBytes.Skip(1).ToArray();

            // If the system architecture is little-endian (that is, little end first),
            // reverse the byte array.
            if (BitConverter.IsLittleEndian)
                Array.Reverse(metaDataBytes);
           
            serverMsg.Length = (uint)BitConverter.ToInt32(metaDataBytes, 0);
            uint len = serverMsg.Length;

            const uint BUFFER_SIZE = 1024;

            byte[] messageDataBytes = new Byte[serverMsg.Length];   //stores the entire message
            //byte[] buffer = new byte[BUFFER_SIZE];  //read from the socket in parts

            
            try
            {
                m_socket.ReadTimeout = 600000;   //we should lower this later, but for now we are just testing
                Int32 bytes = 0;
                int offset = 0;
                do
                {
                    // First, read the msg length
                    bytes = this.m_socket.Read(messageDataBytes, offset, messageDataBytes.Length - offset);        // 1 - code + 4 - len = 5
                    offset += bytes;
                    Console.WriteLine("read:" + bytes);
                } while (offset < len);
                
            }
            catch (System.IO.IOException e)
            {
                if (e.Source != null)
                    Console.WriteLine("IOException source: {0}", e.Source);
                return new ReceivedMessage();
            }

            serverMsg.Message = messageDataBytes;
            if (isEncrypted)
            {
                serverMsg.Message = m_encryptor.decrypt(serverMsg.Message);
                Console.WriteLine("Msg:" + Encoding.UTF8.GetString(serverMsg.Message));
            }
            
            //code + len + data
            //byte[] trimedMsg = serverBytes.Take(1 + 4 + msgLength).ToArray();
            
            if (serverMsg.Code == ErrorResponse.SERVER_DICONECT_CODE)
            {
                throw new Exception(System.Text.Encoding.UTF8.GetString(serverMsg.Message));
            }

            //if its an error msg
            serverMsg.IsErrorMsg = serverMsg.Code == ErrorResponse.errorMsgCode;
            //Console.WriteLine("Message:" + Encoding.Default.GetString(serverMsg.Message) + ", len:" + serverMsg.Length);
            return serverMsg;  //if no error
        }
      
    }


}

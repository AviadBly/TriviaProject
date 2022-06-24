using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using System.Security.Cryptography;

namespace clientAPI
{
    internal class KeyExchangeManager
    {
        private Client m_client { get; set; }
        private BigInteger m_publicKey;
        private BigInteger m_privateKey;
        private BigInteger m_serverPublicKey;
        private byte[] m_secretKey;
        
        private BigInteger m_generator;
        private BigInteger m_modulus;
        

        private const int keyNumberOfBytes = 16;

        private void printByteArray(byte[] arr, string msg)
        {
            Console.WriteLine(msg + ", length =" + arr.Length);
            for (int i = 0; i < arr.Length; i++)
            {
                Console.Write(arr[i] + ", ");
            }
            Console.WriteLine("\n");
        }
        
        public KeyExchangeManager(Client client)
        {
            m_client = client;
        }

        public byte[] getSecretKey()
        {
            getParametersFromServer();

            sendPublicKey();

            createSecretKey();

            return m_secretKey;
        }

        private BigInteger getNumberFromArray(byte[] arr, string msg)
        {           
            return new BigInteger(arr, true, true); //number is unsigned, big endian
        }

        private void getParametersFromServer()
        {
            

            byte[] generatorBytes = m_client.receiver(false).Message;   //get generator
            m_generator = getNumberFromArray(generatorBytes, "Generator:");          

            byte[] modulusBytes = m_client.receiver(false).Message; //get modulus
            m_modulus = getNumberFromArray(modulusBytes, "modulus:");
                        
            byte[] serverPublicKeyBytes = m_client.receiver(false).Message; //getServerPublicKey
            m_serverPublicKey = getNumberFromArray(serverPublicKeyBytes, "serverPublicKey: ");
            
        }

        private void sendPublicKey()
        {


            BigInteger privateKey;
            using (RandomNumberGenerator rng = new RNGCryptoServiceProvider())
            {
                
                byte[] tokenData = new byte[keyNumberOfBytes];
                rng.GetBytes(tokenData);

                m_privateKey = getNumberFromArray(tokenData, "privateKey:");                
            }

            m_publicKey = BigInteger.ModPow(m_generator, m_privateKey, m_modulus);
                        
            m_client.sender(m_publicKey.ToByteArray(true, true), 160);

        }

        private void createSecretKey()
        {
            BigInteger secretKey = BigInteger.ModPow(m_serverPublicKey, m_privateKey, m_modulus);

            m_secretKey = secretKey.ToByteArray(true, true);
                      
        }

    }
}

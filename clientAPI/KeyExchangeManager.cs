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
        private BigInteger m_secretKey;
        
        private BigInteger m_generator;
        private BigInteger m_modulus;
        private BigInteger m_maxExponent;

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

            return m_secretKey.ToByteArray();
        }

        private BigInteger getNumberFromArray(byte[] arr, string msg)
        {
            BigInteger result = new BigInteger(arr, true, true);  //number is unsigned
            //printByteArray(arr, msg);

            Console.WriteLine(msg + "Number: ");
            Console.WriteLine(result);

            return result;
        }

        private void getParametersFromServer()
        {
            ReceivedMessage msg = m_client.receiver();

            byte[] generatorBytes = msg.Message;           
            BigInteger generator = getNumberFromArray(generatorBytes, "Generator:");          

            m_generator = generator;

            msg = m_client.receiver();
            byte[] modulusBytes = msg.Message;     
            
            BigInteger modulus = getNumberFromArray(modulusBytes, "modulus:");
            m_modulus = modulus;
            
            msg = m_client.receiver();
            byte[] maxExponentBytes = msg.Message;
            
            BigInteger maxExponent = getNumberFromArray(maxExponentBytes, "subOrder:");
            m_maxExponent = maxExponent;


            msg = m_client.receiver();
            byte[] serverPublicKeyBytes = msg.Message;

            BigInteger serverPublicKey = getNumberFromArray(serverPublicKeyBytes, "serverPublicKey: ");
            m_serverPublicKey = serverPublicKey;

            Console.WriteLine("\n\n\n\n");
        }

        private void sendPublicKey()
        {


            BigInteger privateKey;
            using (RandomNumberGenerator rng = new RNGCryptoServiceProvider())
            {
                //byte[] tokenData = new byte[m_maxExponent.GetByteCount() - 1];
                byte[] tokenData = new byte[16];
                rng.GetBytes(tokenData);
                
                privateKey = getNumberFromArray(tokenData, "privateKey:");
                m_privateKey = privateKey;
            }



            BigInteger publicKey = BigInteger.ModPow(m_generator, privateKey, m_modulus);
            m_publicKey = publicKey;
            Console.WriteLine("publicKey:");
            Console.WriteLine(publicKey);
            printByteArray(publicKey.ToByteArray(true, true), "publicKey:");

            m_client.sender(publicKey.ToByteArray(true, true), 160);

        }

        private void createSecretKey()
        {
            BigInteger secretKey = BigInteger.ModPow(m_serverPublicKey, m_privateKey, m_modulus);
            

            byte[] secretKeyBytes = secretKey.ToByteArray(true, true);
            printByteArray(secretKeyBytes, "secretkey");

            Console.WriteLine("SECY:" + secretKey);
        }

    }
}

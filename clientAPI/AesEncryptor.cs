using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;
using System.IO;

namespace clientAPI
{
    

    internal class AesEncryptor
    {
        private byte[] m_privateKey;
        private byte[] IV;

        private void printByteArray(byte[] arr, string msg)
        {
            Console.WriteLine(msg + ", length =" + arr.Length);
            for (int i = 0; i < arr.Length; i++)
            {
                Console.Write(arr[i] + ", ");
            }
            Console.WriteLine("\n");
        }
        private static byte[] ComputeSha256Hash(byte[] rawData)
        {
            // Create a SHA256   
            using (SHA256 sha256Hash = SHA256.Create())
            {
                // ComputeHash - returns byte array  
                byte[] bytes = sha256Hash.ComputeHash(rawData);

                return bytes;
            }
        }

        public AesEncryptor(byte[] key)
        {
            Console.WriteLine("\n\n\n\n\n");
            printByteArray(key, "sharedKey:");
            byte[] secretKeyHashed = ComputeSha256Hash(key);
            m_privateKey = secretKeyHashed;
            Console.WriteLine("\n\n\n\n\nhashed key: " + m_privateKey);
            printByteArray(m_privateKey, "HASHED:");
        }

        public byte[] encrypt(byte[] originalMessage)
        {
            byte[] encryptedMessage = new byte[originalMessage.Length];

            using (Aes aes = new AesCryptoServiceProvider())
            {
                aes.Key = m_privateKey;
                aes.IV = new byte[16];

                // Encrypt the message
                using (MemoryStream ciphertext = new MemoryStream())
                using (CryptoStream cs = new CryptoStream(ciphertext, aes.CreateEncryptor(), CryptoStreamMode.Write))
                {
                    byte[] plaintextMessage = originalMessage;
                    cs.Write(plaintextMessage, 0, plaintextMessage.Length);
                    cs.Close();
                    encryptedMessage = ciphertext.ToArray();
                }
            }

            return encryptedMessage;           
        }

        public byte[] decrypt(byte[] encryptedMessage)
        {

            using (Aes aes = new AesCryptoServiceProvider())
            {
                aes.Key = m_privateKey;
                aes.IV = new byte[16];

                // Decrypt the message
                using (MemoryStream plaintext = new MemoryStream())
                {
                    
                    using (CryptoStream cs = new CryptoStream(plaintext, aes.CreateDecryptor(), CryptoStreamMode.Write))
                    {
                        cs.Write(encryptedMessage, 0, encryptedMessage.Length);
                        cs.Close();
                        string message = Encoding.UTF8.GetString(plaintext.ToArray());
                        Console.WriteLine(message);
                        return plaintext.ToArray();
                    }
                }
            }

            throw new Exception("no decrypt");
        }



    }
}

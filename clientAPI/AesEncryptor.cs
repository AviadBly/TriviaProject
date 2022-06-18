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
        int m_aesKeySize;
        const int m_aesBlockSize = 16;

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
            

            byte[] secretKeyHashed = ComputeSha256Hash(key);
            m_privateKey = secretKeyHashed;

            this.IV = new byte[m_aesBlockSize];
            m_aesKeySize = m_privateKey.Length;

            updateInitializationVector(m_privateKey);

            
        }

        private void updateInitializationVector(byte[] rawArr)
        {
            byte[] hashBytes = ComputeSha256Hash(rawArr);
          
            for(int i = 0; i < m_aesBlockSize; i++)
            {
                IV[i] = hashBytes[i];               
            }
        }

        public byte[] encrypt(byte[] originalMessage)
        {
            byte[] encryptedMessage = new byte[originalMessage.Length];
            updateInitializationVector(IV);

            using (Aes aes = new AesCryptoServiceProvider())
            {
                aes.Key = m_privateKey;
                aes.IV = this.IV;

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
            updateInitializationVector(IV);

            using (Aes aes = new AesCryptoServiceProvider())
            {
                aes.Key = m_privateKey;
                aes.IV = IV;

                // Decrypt the message
                using (MemoryStream plaintext = new MemoryStream())
                {                   
                    using (CryptoStream cs = new CryptoStream(plaintext, aes.CreateDecryptor(), CryptoStreamMode.Write))
                    {
                        cs.Write(encryptedMessage, 0, encryptedMessage.Length);
                        cs.Close();
                        return plaintext.ToArray();
                    }
                }
            }

            throw new Exception("Decryption error");
        }

    }
}

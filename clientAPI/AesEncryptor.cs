using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;


namespace clientAPI
{
    

    internal class AesEncryptor
    {
        private byte[] m_privateKey;
        private byte[] IV;

        public AesEncryptor(byte[] key)
        {
            m_privateKey = key;
        }

        public byte[] encrypt(byte[] originalMessage)
        {
            byte[] encryptedMessage = new byte[originalMessage.Length];

            using (Aes aes = new AesCryptoServiceProvider())
            {
                aes.Key = key;
                iv = aes.IV;

                // Encrypt the message
                using (MemoryStream ciphertext = new MemoryStream())
                using (CryptoStream cs = new CryptoStream(ciphertext, aes.CreateEncryptor(), CryptoStreamMode.Write))
                {
                    byte[] plaintextMessage = Encoding.UTF8.GetBytes(secretMessage);
                    cs.Write(plaintextMessage, 0, plaintextMessage.Length);
                    cs.Close();
                    encryptedMessage = ciphertext.ToArray();
                }
            }

        }
    }
}

#include "AesEncryptor.h"




AesEncryptor::AesEncryptor(const SecByteBlock& sharedSecretKey)
{
	
	m_privateKey = sharedSecretKey;

	// Calculate a SHA-256 hash over the Diffie-Hellman session key
	SecByteBlock key(SHA256::DIGESTSIZE);
	SHA256().CalculateDigest(key, m_privateKey, m_privateKey.size());

}

string AesEncryptor::encrypt(const string& message) const
{
	CryptoPP::AutoSeededRandomPool rng;

	// Generate a random IV
	byte iv[AES::BLOCKSIZE];
	//rng.GenerateBlock(iv, AES::BLOCKSIZE);

	CryptoPP::CFB_Mode<AES>::Encryption cfbEncryption(m_privateKey, aesKeyLength, iv);	//encrypt

	string encryptedMessage = message;

	cfbEncryption.ProcessData((byte*)encryptedMessage.c_str(), (byte*)message.c_str(), encryptedMessage.size());

	return encryptedMessage;
}

string AesEncryptor::decrypt(const string& encryptedMessage) const
{

	byte iv[AES::BLOCKSIZE];

	string decryptedMessage = encryptedMessage;

	CFB_Mode<AES>::Decryption cfbDecryption(m_privateKey, aesKeyLength, iv);
	cfbDecryption.ProcessData((byte*)decryptedMessage.c_str(), (byte*)encryptedMessage.c_str(), decryptedMessage.size());

	return decryptedMessage;
}

#include "AesEncryptor.h"

void AesEncryptor::updateInitializationVector(const SecByteBlock arr) {

	SecByteBlock temp(SHA256::DIGESTSIZE);
	SHA256().CalculateDigest(temp, arr, arr.size());

	for (int i = 0; i < m_iv.size(); i++) {
		m_iv[i] = temp[i];
	}
	
}

AesEncryptor::AesEncryptor(const SecByteBlock& sharedSecretKey)
{
	
	m_privateKey = sharedSecretKey;
	

	// Calculate a SHA-256 hash over the Diffie-Hellman session key
	SecByteBlock key(SHA256::DIGESTSIZE);
	

	SHA256().CalculateDigest(key, sharedSecretKey, sharedSecretKey.size());
	m_privateKey = key;

	m_iv = SecByteBlock(AES::BLOCKSIZE);

	updateInitializationVector(m_privateKey);
	
}

string AesEncryptor::encrypt(string message)
{
	updateInitializationVector(m_iv);

	
	CBC_Mode<AES>::Encryption cbcEncryption(m_privateKey, aesKeyLength, m_iv);	//encrypt
	
	string encryptedMessage;
	string originalMsg = message;


	// The StreamTransformationFilter adds padding
	//  as required. ECB and CBC Mode must be padded
	//  to the block size of the cipher.
	CryptoPP::StringSource ss(originalMsg, true,
		new CryptoPP::StreamTransformationFilter(cbcEncryption,
			new CryptoPP::StringSink(encryptedMessage)
		) // StreamTransformationFilter      
	); // StringSource

	
	return encryptedMessage;
}

string AesEncryptor::decrypt(string encryptedMessage)
{
	updateInitializationVector(m_iv);
		

	string decryptedMessage;
	string encryptedMsg = encryptedMessage;
	
	
	CBC_Mode<AES>::Decryption cbcDecryption(m_privateKey, aesKeyLength, m_iv);
	
	// The StreamTransformationFilter removes
	//  padding as required.
	CryptoPP::StringSource ss(encryptedMsg, true,
		new CryptoPP::StreamTransformationFilter(cbcDecryption,
			new CryptoPP::StringSink(decryptedMessage)
		) // StreamTransformationFilter
	); // StringSource

	
	return decryptedMessage;
}

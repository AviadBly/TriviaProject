#include "AesEncryptor.h"


void printByteArr(SecByteBlock arr, int len, string msg) {
	cout << msg << " length:" << len << "\n";
	for (int i = 0; i < len; i++) {
		cout << (int)arr[i] << ", ";
	}
	cout << "\n\n";
}

void printStringBytes(string str) {
	for (int i = 0; i < str.length(); i++) {
		cout << (int)str[i] << ", ";
	}
	cout << "\n\n";
}

void AesEncryptor::updateInitializationVector(const SecByteBlock arr) {

	SecByteBlock temp(m_iv.size());
	SHA256().CalculateDigest(temp, arr, arr.size());

	cout << "\n\nIV: ";
	for (int i = 0; i < m_iv.size(); i++) {
		m_iv[i] = temp[i];
		cout << (int)m_iv[i] << ", ";
	}
	cout << "\n\n";
}

AesEncryptor::AesEncryptor(const SecByteBlock& sharedSecretKey)
{
	
	m_privateKey = sharedSecretKey;
	cout << "\n\n\n\n\n";

	// Calculate a SHA-256 hash over the Diffie-Hellman session key
	SecByteBlock key(SHA256::DIGESTSIZE);
	printByteArr(sharedSecretKey, sharedSecretKey.size(), "SharedKey: ");

	SHA256().CalculateDigest(key, sharedSecretKey, sharedSecretKey.size());
	m_privateKey = key;

	m_iv = SecByteBlock(AES::BLOCKSIZE);

	printByteArr(m_privateKey, m_privateKey.size(), "Hash key:");
	cout << "Private hashed : " << m_privateKey << "\n\n\n\n\n";

	updateInitializationVector(m_privateKey);

	//string msg = "{jgjgjkg}";
	//// Generate a random IV
	CryptoPP::byte initi[AES::BLOCKSIZE];

	
}

string AesEncryptor::encrypt(string message)
{
	updateInitializationVector(m_iv);

	cout << "IV: " << m_iv << "\n";
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

	//cbcEncryption.ProcessData((CryptoPP::byte*)encryptedMessage.c_str(), (CryptoPP::byte*)message.c_str(), encryptedMessage.size());

	return encryptedMessage;
}

string AesEncryptor::decrypt(string encryptedMessage)
{
	updateInitializationVector(m_iv);
	//CryptoPP::byte iv[AES::BLOCKSIZE];	

	string decryptedMessage;
	string encryptedMsg = encryptedMessage;
	//printStringBytes(decryptedMessage);

	CBC_Mode<AES>::Decryption cbcDecryption(m_privateKey, aesKeyLength, m_iv);
	//cfbDecryption.ProcessData((CryptoPP::byte*)decryptedMessage.c_str(), (CryptoPP::byte*)encryptedMessage.c_str(), decryptedMessage.size());

	// The StreamTransformationFilter removes
	//  padding as required.
	CryptoPP::StringSource ss(encryptedMsg, true,
		new CryptoPP::StreamTransformationFilter(cbcDecryption,
			new CryptoPP::StringSink(decryptedMessage)
		) // StreamTransformationFilter
	); // StringSource

	//printStringBytes(decryptedMessage);
	return decryptedMessage;
}

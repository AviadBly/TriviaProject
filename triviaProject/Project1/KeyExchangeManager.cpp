#include "KeyExchangeManager.h"

void KeyExchange::UnsignedIntegerToByteBlock(const Integer& x, SecByteBlock& bytes)
{
	size_t encodedSize = x.MinEncodedSize(Integer::UNSIGNED);
	bytes.resize(encodedSize);
	x.Encode(bytes.BytePtr(), encodedSize, Integer::UNSIGNED);
}

//for debug
void KeyExchange::printByteArr(BYTE arr[], int len, string msg) {
	cout << msg << " length:" << len << "\n";
	for (int i = 0; i < len; i++) {
		cout << short(arr[i]) << ", ";
	}
	cout << "\n\n";
}


SecByteBlock KeyExchange::getPublicKey() const
{
	return this->m_publicKey;
}

SecByteBlock KeyExchange::getPrivateKey() const
{
	return this->m_privateKey;
}

SecByteBlock KeyExchange::getClientPublicKey() const
{
	return this->m_clientPublicKey;
}


string KeyExchange::returnMsgFromBytes(SecByteBlock bytes, BYTE code) {

	vector<BYTE> message;

	for (unsigned int i = 0; i < bytes.size(); i++) {
		message.push_back(bytes[i]);
	}

	return JsonResponsePacketSerializer::getMessageInFormat(message, code);
}

void KeyExchange::initializeParameters()
{
	AutoSeededRandomPool prng;
	Integer M, Q, G;
	CryptoPP::PrimeAndGenerator pg;


	const int ModulusnumberOfBits = 512;
	const int QnumberOfBits = ModulusnumberOfBits - 1;

	pg.Generate(1, prng, ModulusnumberOfBits, QnumberOfBits);		//publicKey = G ^ privateKey % M
	M = pg.Prime();	//modulus
	Q = pg.SubPrime();
	G = pg.Generator();

	m_DHC = CryptoPP::DH(M, Q, G);

	SecByteBlock privateKey(m_DHC.PrivateKeyLength()), publicKey(m_DHC.PublicKeyLength());
	m_DHC.GenerateKeyPair(prng, privateKey, publicKey);

	this->m_privateKey = privateKey;
	this->m_publicKey = publicKey;

}



void KeyExchange::sendParameters(SOCKET socket)
{

	SecByteBlock generator;
	UnsignedIntegerToByteBlock(m_DHC.GetGenerator(), generator);

	SecByteBlock modulus;
	UnsignedIntegerToByteBlock(m_DHC.GetGroupParameters().GetModulus(), modulus);

	Communicator::sendMsg(socket, returnMsgFromBytes(generator, 99));

	
	Communicator::sendMsg(socket, returnMsgFromBytes(modulus, 98));

	Communicator::sendMsg(socket, returnMsgFromBytes(getPublicKey(), 96));

}

void KeyExchange::sendGetClientPublicKey(SOCKET socket)
{
	
	string clientMsg = Communicator::recvMsg(socket).substr(5);
	SecByteBlock clientPublicKeyBytes(clientMsg.length());

	for (unsigned int i = 0; i < clientMsg.length(); i++) {
		clientPublicKeyBytes[i] = clientMsg[i];
	}
	m_clientPublicKey = clientPublicKeyBytes;


}


SecByteBlock KeyExchange::getSharedSecretKeySecretKey(SOCKET socket)
{

	initializeParameters();
	sendParameters(socket);
	sendGetClientPublicKey(socket);

	Integer M = m_DHC.GetGroupParameters().GetModulus();
	Integer G_B(getClientPublicKey(), getClientPublicKey().size());

	Integer privateK(m_privateKey, m_privateKey.size());
	
	
	CryptoPP::ModularArithmetic MM(M);
	Integer secret = MM.Exponentiate(G_B, privateK);

	SecByteBlock secretKey(m_DHC.AgreedValueLength());
	
	UnsignedIntegerToByteBlock(secret, secretKey);
		
	if (!m_DHC.Agree(secretKey, getPrivateKey(), getClientPublicKey()))
		throw ("NO SECURE CONNECTION");

	return secretKey;
}

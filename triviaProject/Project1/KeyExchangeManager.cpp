#include "KeyExchangeManager.h"


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

	//M = 131;	//modulus
	//Q = 7;
	//G = 19;

	m_DHC =  CryptoPP::DH(M, Q, G);

	SecByteBlock privateKey(m_DHC.PrivateKeyLength()), publicKey(m_DHC.PublicKeyLength());
	m_DHC.GenerateKeyPair(prng, privateKey, publicKey);

	this->m_privateKey = privateKey;
	this->m_publicKey = publicKey;

	Integer k1(privateKey, privateKey.size()), k2(publicKey, publicKey.size());

	cout << "Private key:\n";
	cout << k1 << endl;
	cout << "Public key:\n";
	cout << k2 << endl;

	cout << "M:\n";
	cout << M << endl;
	cout << "Q:\n";
	cout << Q << endl;
	cout << "G:\n";
	cout << G << endl;
}

void KeyExchange::UnsignedIntegerToByteBlock(const Integer& x, SecByteBlock& bytes)
{
	size_t encodedSize = x.MinEncodedSize(Integer::UNSIGNED);
	bytes.resize(encodedSize);
	x.Encode(bytes.BytePtr(), encodedSize, Integer::UNSIGNED);
}

void KeyExchange::printByteArr(BYTE arr[], int len, string msg) {
	cout << msg << " length:" << len << "\n";
	for (int i = 0; i < len; i++) {
		cout << short(arr[i]) << ", ";
	}
	cout << "\n\n";
}

string KeyExchange::returnMsgFromBytes(SecByteBlock bytes, BYTE code) {

	vector<BYTE> message;

	for (int i = 0; i < bytes.size(); i++) {
		message.push_back(bytes[i]);
	}

	return JsonResponsePacketSerializer::getMessageInFormat(message, code);
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



void KeyExchange::getClientPublicKey(SOCKET socket)
{
	cout << "\n\n\n\n\n";
	string clientMsg = Communicator::recvMsg(socket).substr(5);
	SecByteBlock clientPublicKeyBytes(clientMsg.length());
	for (int i = 0; i < clientMsg.length(); i++) {
		clientPublicKeyBytes[i] = clientMsg[i];
	}
	m_clientPublicKey = clientPublicKeyBytes;

	printByteArr(m_clientPublicKey, m_clientPublicKey.size(), "clientPublicKey:");


}


void KeyExchange::sendParameters(SOCKET socket)
{

	SecByteBlock generator;
	UnsignedIntegerToByteBlock(m_DHC.GetGenerator(), generator);

	SecByteBlock modulus;
	UnsignedIntegerToByteBlock(m_DHC.GetGroupParameters().GetModulus(), modulus);

	SecByteBlock subOrder;
	UnsignedIntegerToByteBlock(m_DHC.GetGroupParameters().GetSubgroupOrder(), subOrder);


	printByteArr(generator, generator.size(), "Generator:");
	Communicator::sendMsg(socket, returnMsgFromBytes(generator, 99));

	printByteArr(modulus, modulus.size(), "Modulus:");
	Communicator::sendMsg(socket, returnMsgFromBytes(modulus, 98));

	printByteArr(subOrder, subOrder.size(), "SubOrder:");
	Communicator::sendMsg(socket, returnMsgFromBytes(subOrder, 97));

	printByteArr(getPublicKey(), getPublicKey().size(), "PublicKey:");
	Communicator::sendMsg(socket, returnMsgFromBytes(getPublicKey(), 96));

}

SecByteBlock KeyExchange::getKey(SOCKET socket)
{

	
	SecByteBlock secretKey(m_DHC.AgreedValueLength());

	printByteArr(secretKey, secretKey.size(), "secretKey:");

	if (!m_DHC.Agree(secretKey, getPrivateKey(), getClientPublicKey()))
		throw ("NO SECURE CONNECTION");

	return secretKey;
}


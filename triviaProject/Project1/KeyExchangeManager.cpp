#include "KeyExchangeManager.h"

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

	//M = 131;	//modulus
	//Q = 7;
	//G = 19;

	m_DHC = CryptoPP::DH(M, Q, G);

	SecByteBlock privateKey(m_DHC.PrivateKeyLength()), publicKey(m_DHC.PublicKeyLength());
	m_DHC.GenerateKeyPair(prng, privateKey, publicKey);

	this->m_privateKey = privateKey;
	this->m_publicKey = publicKey;

	Integer k1(privateKey, privateKey.size()), k2(publicKey, publicKey.size());

	CryptoPP::ModularArithmetic MM(M);
	Integer pub = MM.Exponentiate(G, k1);


	/*cout << "Private key:\n";
	cout << k1 << endl;*/
	if ((k2 - pub) == 0) {
		cout << "Public key!!!!!!!!!!:\n";
		
	}
	

	printByteArr(privateKey, privateKey.size(), "Private key:");

	cout << "M:\n";
	cout << M << endl;
	

	/*cout << "Q:\n";
	cout << Q << endl;*/
	cout << "G:\n";
	cout << G << endl;
}



void KeyExchange::sendParameters(SOCKET socket)
{

	SecByteBlock generator;
	UnsignedIntegerToByteBlock(m_DHC.GetGenerator(), generator);

	SecByteBlock modulus;
	UnsignedIntegerToByteBlock(m_DHC.GetGroupParameters().GetModulus(), modulus);

	Integer m(modulus, modulus.size());
	cout << "REAL M:" << m << "\n";

	SecByteBlock MaxExponenet;
	UnsignedIntegerToByteBlock(m_DHC.GetGroupParameters().GetMaxExponent(), MaxExponenet);


	printByteArr(generator, generator.size(), "Generator:");
	Communicator::sendMsg(socket, returnMsgFromBytes(generator, 99));

	printByteArr(modulus, modulus.size(), "Modulus:");
	Communicator::sendMsg(socket, returnMsgFromBytes(modulus, 98));

	printByteArr(MaxExponenet, MaxExponenet.size(), "MaxExponenet:");
	Communicator::sendMsg(socket, returnMsgFromBytes(MaxExponenet, 97));

	printByteArr(getPublicKey(), getPublicKey().size(), "PublicKey:");
	Communicator::sendMsg(socket, returnMsgFromBytes(getPublicKey(), 96));

}

void KeyExchange::sendGetClientPublicKey(SOCKET socket)
{
	cout << "\n\n\n\n\n";
	string clientMsg = Communicator::recvMsg(socket).substr(5);
	SecByteBlock clientPublicKeyBytes(clientMsg.length());

	for (unsigned int i = 0; i < clientMsg.length(); i++) {
		clientPublicKeyBytes[i] = clientMsg[i];
	}
	m_clientPublicKey = clientPublicKeyBytes;

	printByteArr(m_clientPublicKey, m_clientPublicKey.size(), "clientPublicKey:");

	Integer pub(m_clientPublicKey, m_clientPublicKey.size() , CryptoPP::Integer::UNSIGNED, CryptoPP::ByteOrder::LITTLE_ENDIAN_ORDER);
	
	cout << "PUB: " << pub << "\n";
}


SecByteBlock KeyExchange::getSecretKey(SOCKET socket)
{

	initializeParameters();
	sendParameters(socket);
	sendGetClientPublicKey(socket);

	Integer M = m_DHC.GetGroupParameters().GetModulus();
	Integer G_B(getClientPublicKey(), getClientPublicKey().size());
	cout << "m:" << M << "\n";
	cout << "G_B:" << G_B << "\n";

	Integer privateK(m_privateKey, m_privateKey.size());
	cout << "PRIV:" << privateK << "\n";
	
	CryptoPP::ModularArithmetic MM(M);
	Integer secret = MM.Exponentiate(G_B, privateK);

	cout << secret << "\n";

	SecByteBlock secretKey(m_DHC.AgreedValueLength());
	cout << " len:" + secret.ByteCount() << "\n";

	UnsignedIntegerToByteBlock(secret, secretKey);
	printByteArr(secretKey, secretKey.size(), "secret: ");
	
	if (!m_DHC.Agree(secretKey, getPrivateKey(), getClientPublicKey()))
		throw ("NO SECURE CONNECTION");

	Integer sec(secretKey, secretKey.size());
	
	printByteArr(secretKey, secretKey.size(), "secretKey:");

	cout << "SECRET FLAG:" << sec << "\n";

	return secretKey;
}

KeyExchange::~KeyExchange()
{
	
	m_DHC.~DH_Domain();
	m_publicKey.~SecBlock();
	m_privateKey.~SecBlock();
	m_clientPublicKey.~SecBlock();
}


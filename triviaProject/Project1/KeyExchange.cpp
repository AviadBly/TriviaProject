#include "KeyExchange.h"

std::string KeyExchange::getKey(SOCKET socket)
{


    OID CURVE = secp256r1();
    AutoSeededX917RNG<AES> rng;

    ECDH < ECP >::Domain dhA(CURVE), dhB(CURVE);

    // Don't worry about point compression. Its amazing that Certicom got
    // a patent for solving an algebraic equation....
    // dhA.AccessGroupParameters().SetPointCompression(true);
    // dhB.AccessGroupParameters().SetPointCompression(true);

    SecByteBlock privA(dhA.PrivateKeyLength()), pubA(dhA.PublicKeyLength());

    return string();
}


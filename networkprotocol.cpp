#include "networkprotocol.h"
/*
NetworkProtocol::NetworkProtocol(QObject *parent) :
    QObject(parent)
{
}
*/

void NetworkProtocol::encode()
{

}

void NetworkProtocol::decode(QByteArray& msg)
{
    // An actual decoding is proceeding in an descendant class
    //--------------------------------------------------------


//    foreach(Var v, decodedVar)  //???
//    {
//        emit dataReady(v);
//    };
}

void Transaction::clearResponseData()
{

}

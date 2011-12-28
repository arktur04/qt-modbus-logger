#include <QString>
#include "abstractnetworkclient.h"
#include <QDebug>

AbstractNetworkClient::AbstractNetworkClient()
{
    qDebug() << "AbstractNetworkClient ctor" << endl;
}

void AbstractNetworkClient::connectToServer()
{
    qDebug() << "AbstractNetworkClient.connect" << endl;
    connected();                                        //debug
}

void AbstractNetworkClient::disconnectFromServer()
{
    qDebug() << "AbstractNetworkClient.disconnect" << endl;
    disconnected();                                        //debug
}

void AbstractNetworkClient::send(const QByteArray& msg)
{
    qDebug() << "AbstractNetworkClient.send(" << msg.toHex() <<")";
   // receive(QByteArray::fromHex("987654"));
}
void AbstractNetworkClient::receive(const QByteArray& msg)
{
    emit onReceive(msg);
    qDebug() << "AbstractNetworkClient.receive(" << msg.toHex() << ")";
}

void AbstractNetworkClient::error(const QAbstractSocket::SocketError socketError)
{
    emit onError(socketError);
}

void AbstractNetworkClient::connected()
{
    emit onConnected();
}

void AbstractNetworkClient::disconnected()
{
    emit onDisconnected();
}

#include "abstractnetworkclient.h"
#include "tcpclient.h"
#include <QString>
#include <QtDebug>

TcpClient::TcpClient()
{
    qDebug() << "TcpClient ctor" << endl;
    connect(this, SIGNAL(debugSend(QByteArray)), this, SLOT(debugReceive(QByteArray)), Qt::QueuedConnection);
}

void TcpClient::connectToServer()
{
    AbstractNetworkClient::connectToServer();
    qDebug() << "TcpClient.connectToServer" << endl;
}

void TcpClient::disconnectFromServer()
{
    AbstractNetworkClient::disconnectFromServer();
    qDebug() << "TcpClient.disconnectFromServer" << endl;
}

void TcpClient::send(const QByteArray& msg)
{
    AbstractNetworkClient::send(msg);
    qDebug() << "TcpClient.send(" << msg.toHex() << ")";
    emit debugSend(msg);
}

void TcpClient::receive(QByteArray& msg)
{
    AbstractNetworkClient::receive(msg);
    qDebug() << "TcpClient.receive(" << msg.toHex() << ")";
}

void TcpClient::debugReceive(QByteArray msg)
{
    receive(msg);
}

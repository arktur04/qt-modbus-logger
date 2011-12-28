#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "abstractnetworkclient.h"
#include <QtDebug>

class TcpClient : public AbstractNetworkClient
{
public:
    TcpClient();
    virtual void connectToServer();
    virtual void disconnectFromServer();
    virtual void send(const QByteArray& msg);
    virtual void receive(QByteArray& msg);
signals:
  //  void debugSend();
public slots:
    virtual void debugReceive(QByteArray msg);
};

#endif // TCPCLIENT_H

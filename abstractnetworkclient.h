#ifndef ABSTRACTNETWORKCLIENT_H
#define ABSTRACTNETWORKCLIENT_H

#include <QByteArray>
#include <QMetaType>
#include <QString>
#include <QAbstractSocket>

Q_DECLARE_METATYPE(QAbstractSocket::SocketError)

class AbstractNetworkClient : public QObject
{
    Q_OBJECT
public:
 //   explicit AbstractNetworkClient(QObject *parent = 0);
    AbstractNetworkClient();
    virtual void connectToServer();
    virtual void disconnectFromServer();
    virtual void send(const QByteArray& msg);
protected:
    virtual void receive(const QByteArray& msg);
//    {
//        emit onReceive(msg);
//        qDebug() << "AbstractNetworkClient.receive(" << msg.toHex() << ")";
//    }

    virtual void error(const QAbstractSocket::SocketError socketError);
//    {
//        emit onError(socketError);
//    }

    virtual void connected();
//    {
//        emit onConnected();
//    }

    virtual void disconnected();
//    {
//        emit onDisconnected();
//    }

signals:
    void onReceive(const QByteArray& msg);
    void onError(const QAbstractSocket::SocketError socketError);
    void onConnected();
    void onDisconnected();

    void debugSend(QByteArray msg);
public slots:
  virtual void debugReceive(QByteArray msg) {}
};

#endif // ABSTRACTNETWORKCLIENT_H

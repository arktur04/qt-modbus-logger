#include "querysender.h"
#include "abstractnetworkclient.h"
#include <QAbstractSocket>
#include <QtDebug>
#include <QObject>
#include <QString>
#include <QList>
#include <QByteArray>
#include <Qt>

//QuerySender::QuerySender(QObject *parent) :
//    QObject(parent)
//{
//}

void QuerySender::sendFirst()
{
    qDebug() << "QuerySender::sendFirst()" << endl;
    if(m_queryList && !m_queryList->isEmpty())
    {
        isSequenceCompleted = false;
        m_nextMsg = m_queryList->constBegin();
        sendMsg(*m_nextMsg++);
    }
    else
    {
        isSequenceCompleted = true;
    };
}

void QuerySender::sendNext()
{
    qDebug() << "QuerySender::sendNext()" << endl;
    if(m_nextMsg != m_queryList->constEnd())
    {
        sendMsg(*m_nextMsg++);
    }
    else
    {
        isSequenceCompleted = true;
    }
}

void QuerySender::run()
{
    if(!m_isRunning && m_networkClient)
    {
        m_isRunning = true;
        connect(m_networkClient, SIGNAL(onConnected()), this, SLOT(connected()));
        connect(m_networkClient, SIGNAL(onDisconnected()), this, SLOT(disconnected()));
        connect(m_networkClient, SIGNAL(onReceive(const QByteArray&)),
                this, SLOT(dataRecieved(const QByteArray&)));
        connect(m_networkClient, SIGNAL(onError(const QAbstractSocket::SocketError)),
                this, SLOT(networkError(const QAbstractSocket::SocketError)));

        m_networkClient->connectToServer();
    }
}

void QuerySender::stop()
{
    if(m_isRunning)
    {
        m_isRunning = true;
        killTimer(m_timerId);
    }
}

void QuerySender::connected()
{
   if(m_isRunning)
   {
       m_timerId = startTimer(m_period);
   }
}

void QuerySender::disconnected()
{

}

void QuerySender::dataRecieved(const QByteArray& msg)
{
    qDebug() << "QuerySender::dataRecieved(" << msg.toHex() << ")" << endl;
    emit onDataRecieved(msg);
    sendNext();
}

void QuerySender::networkError(const QAbstractSocket::SocketError error)
{

}

void QuerySender::timerEvent(QTimerEvent *event)
{
    sendFirst();
}

void QuerySender::sendMsg(const QByteArray& msg)
{
    qDebug() << "QuerySender.sendMsg(" << msg.toHex() << ")";
    m_networkClient->send(msg);
    if(isSequenceCompleted)
    {
        qDebug() << endl;
    }
}

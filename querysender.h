#ifndef QUERYSENDER_H
#define QUERYSENDER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QByteArray>
#include <QAbstractSocket>
#include "abstractnetworkclient.h"
#include "networkprotocol.h"

class QuerySender : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QByteArray>* queryList READ queryList WRITE setQueryList)
    Q_PROPERTY(int period READ period WRITE setPeriod)
    Q_PROPERTY(AbstractNetworkClient* networkClient READ networkClient WRITE setNetworkClient)
public:
    //explicit QuerySender(QObject *parent = 0);
    QuerySender(QList<QByteArray>* queryList):
        m_queryList(queryList), m_isRunning(false), m_period(1000), isSequenceCompleted(true) {}
    QList<QByteArray>* queryList() const
    {return m_queryList;}
    void setQueryList(QList<QByteArray>* queryList)
    {m_queryList = queryList;}
    int period() const
    {return m_period;}
    void setPeriod(int period)
    {m_period = period;}
    AbstractNetworkClient* networkClient() const
    {return m_networkClient;}
    void setNetworkClient(AbstractNetworkClient* networkClient)
    {
        m_networkClient = networkClient;
    }
    void sendFirst();
    void sendNext();
    void run();
    void stop();
signals:
    void onDataRecieved(const QByteArray& msg);
public slots:
    void connected();
    void disconnected();
    void dataRecieved(const QByteArray& msg);
    void networkError(const QAbstractSocket::SocketError error);

protected:
    virtual void sendMsg(const QByteArray& msg);
    void timerEvent(QTimerEvent *event);

private:
    QList<QByteArray>* m_queryList;
    AbstractNetworkClient* m_networkClient;
    QList<QByteArray>::const_iterator m_nextMsg;

    QList<Transaction> transactionList;
    bool m_isRunning;
    int m_timerId;
    int m_period;
    bool isSequenceCompleted;
};

#endif // QUERYSENDER_H

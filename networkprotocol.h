#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H

#include <QObject>
//#include <QString>
#include <QByteArray>
#include <QVector>
#include "vars.h"

class NetworkProtocol : public QObject
{
    Q_OBJECT
public:
  //  explicit NetworkProtocol(QObject *parent = 0);
    void encode();
signals:
    void dataReady(const Var& var);
public slots:
    virtual void decode(QByteArray& msg);
protected:
    QVector< Var > decodedVar;
};

class Transaction
{
    friend class NetworkProtocol;
public:
    void clearResponseData();

    VarList& varList() {return m_varList;}
    QByteArray& query() {return m_query;}
    QByteArray& response() {return m_response;}
    int startAddr() {return m_startAddr;}
    int number() {return m_number;}
    int transactionId() {return m_transactionId;}
    int functionCode() {return m_functionCode;}
private:
    VarList m_varList;
    QByteArray m_query;
    QByteArray m_response;
    int m_startAddr;
    int m_number;
    int m_transactionId;
    int m_functionCode;
};

#endif // NETWORKPROTOCOL_H

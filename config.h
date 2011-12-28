#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QList>
#include <QHostAddress>
//#include "varlist.h"

//using namespace var;

class Config: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QHostAddress hostAddress READ hostAddress)
    Q_PROPERTY(qint16 ipPort READ ipPort)
    Q_PROPERTY(int timerPeriod READ timerPeriod)
    Q_PROPERTY(QList<QByteArray>* pQueryList READ pQueryList)

public:
    Config(QString configName = "config.xml");
    virtual ~Config() {}
    char load();

    QHostAddress hostAddress() const
    {return m_hostAddress;}
    qint16 ipPort() const
    {return m_ipPort;}
    int timerPeriod() const
    {return m_timerPeriod;}
    QList<QByteArray>* pQueryList()
    {return &m_queryList;}
private:
    QString m_configName;
    QHostAddress m_hostAddress;
    qint16 m_ipPort;
    int m_timerPeriod;
    QList<QByteArray> m_queryList;
  //  VarList m_varList;
};

#endif // CONFIG_H

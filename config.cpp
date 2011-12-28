#include "config.h"

#include <iostream>
#include <QtXml>
#include <QtDebug>
#include <QHostAddress>
//#include "varlist.h"
#include "vars.h"
//#include "vartypeinfo.h"

using namespace std;
//using namespace var;

Config::Config(QString configName): QObject(), m_configName(configName)
{
    //m_hostAddress();
    //m_queryList();
    load();
}

char Config::load()
{
    QFile configFile(m_configName);
    if(!configFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "The config file opening error." << endl;
        return -1;
    };

    QDomDocument configDom;
    if(!configDom.setContent(&configFile))
    {
        cout << "The config file XML parsing error";
        configFile.close();
        return -2;
    };

    configFile.close();


    QDomElement element;
    QDomElement root = configDom.documentElement();
    QDomElement generalElement = root.firstChildElement("General");
    element = generalElement.firstChildElement("Connection");
    if(!element.isNull())
    {
        m_hostAddress.setAddress(element.attribute("ip", "127.0.0.1"));
        m_ipPort = element.attribute("port", "0").toInt();

//                cout << "ip: "
//                     << m_hostAddress.toString()
//                     << endl
//                     << "port: "
//                     << m_ipPort
//                     << endl;
    };
    element = generalElement.firstChildElement("Timer");
    if(!element.isNull())
    {
        m_timerPeriod = element.attribute("period", "1000").toInt();
//                cout << "period: "
//                     << m_timerPeriod
//                     << endl;
    };
    QDomElement queriesElement = root.firstChildElement("Queries");
    for(element = queriesElement.firstChildElement("Query");
        !element.isNull();
        element = element.nextSiblingElement("Query"))
    {
        QByteArray query = QByteArray::fromHex(element.attribute("query", "0").toAscii());
        m_queryList.append(query);
//                cout << "query: "
//                     << query
//                     << endl;
    };


    QString tempName, tempTypeName;
    QDomElement varsElement = root.firstChildElement("Vars");
    for(element = varsElement.firstChildElement("Var");
        !element.isNull();
        element = element.nextSiblingElement("Var"))
    {
        tempName = element.attribute("name", "___ERROR___UNKNOWN_VARIABLE___");
        tempTypeName = element.attribute("type", "___ERROR___UNKNOWN_TYPE___");
        Var* pVar;
        pVar = globalTypedVarMap().var(tempTypeName);
        if(pVar)
        {
            pVar->setId(element.attribute("id", "-1").toInt());
            pVar->setName(tempName);
            globalVarList().appendVar(*pVar);
        }
        else
        {
            qDebug() << "Unknown type";
        }
    };






/*
    QDomNode node = documentElement.firstChild();
    while(!node.isNull())
    {
        if(node.isElement())
        {
            QDomElement element = node.toElement();
            if(element.tagName()=="Connection")
            {
                m_hostAddress.setAddress(element.attribute("ip", "127.0.0.1"));
                m_ipPort = element.attribute("port", "0").toInt();

//                cout << "ip: "
//                     << m_hostAddress.toString()
//                     << endl
//                     << "port: "
//                     << m_ipPort
//                     << endl;
            };
            if(element.tagName()=="Timer")
            {
                m_timerPeriod = element.attribute("period", "1000").toInt();
//                cout << "period: "
//                     << m_timerPeriod
//                     << endl;
            };
            if(element.tagName()=="Query")
            {
                QByteArray query = QByteArray::fromHex(element.attribute("query", "0").toAscii());
                m_queryList.append(query);
//                cout << "query: "
//                     << query
//                     << endl;
            };
            if(element.tagName()=="Vars")
            {
            }
        }

        node = node.nextSibling();
    }
*/

    return 0;
}

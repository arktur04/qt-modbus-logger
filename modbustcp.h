#ifndef MODBUSTCP_H
#define MODBUSTCP_H

#include "networkprotocol.h"

class ModbusTcp: public NetworkProtocol
{
public:
    ModbusTcp();
public slots:
    virtual void decode(QByteArray& msg);
protected:
    int startingAddr() {return m_startingAddr;}
    void setStartingAddr(int value) {m_startingAddr = value;}
    int numberOfPoints() {return m_numberOfPoints;}
    void NumberOfPoints(int value) {m_numberOfPoints = value;}
private:
    int m_startingAddr;
    int m_numberOfPoints;
};

#endif // MODBUSTCP_H

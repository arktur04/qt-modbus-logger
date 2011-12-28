#include "vartypes.h"

TypeMap* TypeMap::m_singleInstance = 0;  //

void TypeBase::validateByteOrder()
{
    Q_ASSERT(m_byteOrder.size() == m_dataSize);
    for(int i = 0; i < m_dataSize; ++i)
    {
        Q_ASSERT(((int)m_byteOrder[i] >= 0) && ((int)m_byteOrder[i] < m_dataSize));
    }
}

void TypeBase::convertRawData(char* src, char* dest)
{
    for(int i = 0; i < m_dataSize; ++i)
    {
        *(dest++) = src[m_byteOrder[i]];
    }
}

void TypeMap::createTypeMap()
{
    if(!m_singleInstance)
    {
        m_singleInstance = new TypeMap();
        m_singleInstance->addType(new TypeBool);
        m_singleInstance->addType(new TypeInt16);
        m_singleInstance->addType(new TypeUInt16);
        m_singleInstance->addType(new TypeInt32);
        m_singleInstance->addType(new TypeUInt32);
        m_singleInstance->addType(new TypeFloat);
    };
}

TypeMap* TypeMap::getTypeMap()
{
    return m_singleInstance;
}

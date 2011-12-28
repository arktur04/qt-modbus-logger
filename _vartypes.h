#ifndef VARTYPES_H
#define VARTYPES_H

#include <QString>
#include <QByteArray>
#include <QMap>
#include <QDebug>

class TypeBase
{
public:
    TypeBase() {}

    virtual QString typeName() {return "Base type";}
    virtual int dataSize() {return -1;}
    virtual QByteArray* byteOrder() {return &m_byteOrder;}
    virtual void convertRawData(char* src, char* dest);

private:
    void validateByteOrder();
    QString m_typeName;
    int m_dataSize;
    QByteArray m_byteOrder;
};

class TypeBool: public TypeBase
{
public:
    TypeBool()
    {
        byteOrder()->append(char(0));
    }
    virtual QString typeName() {return "Bool";}
    virtual int dataSize() {return 1;}
};

class TypeInt16: public TypeBase
{
public:
    TypeInt16()
    {
        byteOrder()->append(char(0));
        byteOrder()->append(char(1));
    }
    virtual QString typeName() {return "Int16";}
    virtual int dataSize() {return 2;}
};

class TypeUInt16: public TypeBase
{
public:
    TypeUInt16()
    {
        byteOrder()->append(char(0));
        byteOrder()->append(char(1));
    }
    virtual QString typeName() {return "UInt16";}
    virtual int dataSize() {return 2;}
};

class TypeInt32: public TypeBase
{
public:
    TypeInt32()
    {
        byteOrder()->append(char(0));
        byteOrder()->append(char(1));
        byteOrder()->append(char(2));
        byteOrder()->append(char(3));
    }
    virtual QString typeName() {return "Int32";}
    virtual int dataSize() {return 4;}
};

class TypeUInt32: public TypeBase
{
public:
    TypeUInt32()
    {
        byteOrder()->append(char(0));
        byteOrder()->append(char(1));
        byteOrder()->append(char(2));
        byteOrder()->append(char(3));
    }
    virtual QString typeName() {return "UInt32";}
    virtual int dataSize() {return 4;}
};

class TypeFloat: public TypeBase
{
public:
    TypeFloat()
    {
        byteOrder()->append(char(0));
        byteOrder()->append(char(1));
        byteOrder()->append(char(2));
        byteOrder()->append(char(3));
    }
    virtual QString typeName() {return "Float";}
    virtual int dataSize() {return 4;}
};

//class TypeMap;
class TypeMap: public QMap< QString, TypeBase* >
{
public:
    TypeMap() {}
    void addType(TypeBase* pType)
    {
        insert(pType->typeName(), pType);
    }
    virtual ~TypeMap()
    {
        for(iterator i = begin(); i != end(); ++i)
        {
            delete i.value();
        };
        /*
        QMapIterator< QString, TypeBase* > i(*(TypeMap::getTypeMap()));
        while(i.hasNext())
        {
            i.next();
            delete i.value();
        }
        */
        delete m_singleInstance;
    }

    static void createTypeMap();

    static TypeMap* getTypeMap();
private:
    static TypeMap* m_singleInstance;
};

//--------------------------
class TypeEnum                 //for test purpouse
{
public:
    TypeEnum() {}
    static void enumerate()
    {
        QMap< QString, TypeBase* > * map = (TypeMap::getTypeMap());
        QMap< QString, TypeBase* >::iterator i;

        for(i = map->begin(); i != map->end(); ++i)
        {
            qDebug() << "Key: " << i.key()                 //->key()
                     << " Name: " << i.value()->typeName()
                     << " Size: " << i.value()->dataSize();
        }
    }
};

#endif // VARTYPES_H

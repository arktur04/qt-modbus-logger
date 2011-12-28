#ifndef VARS_H
#define VARS_H

#include <QString>
#include <QList>
#include <QMap>
//#include "vartypes.h"

enum VarState {Good, Bad, TimeOut, Undefined};

enum TypeId {TypeUndefined, TypeBool, TypeInt16, TypeUInt16, TypeInt32, TypeUInt32, TypeFloat};

const int VARDATASIZE = 8;

struct VarType
{
    TypeId id;
    bool useByteOrder;
    char byteOrder[VARDATASIZE];
    int size;
    QString name;
};

union VarValue
{
    bool Bool;
    long long Int;
    double Double;
    char data[VARDATASIZE];
};

class TypeDescriptors
{
public:
    TypeDescriptors();
   /* TypeId typeId(QString typeName);
    QString typeName(TypeId typeId);
    int size(TypeId typeId); */
    VarType* varType(QString typeName) {return m_stringTypeMap[typeName];}
    VarType* varType(TypeId typeId) {return m_idTypeMap[typeId];}
//    VarType* operator[] (QString typeName) {return varType(typeName);}
//    VarType* operator[] (TypeId typeId) {return varType(typeId);}
private:
    QMap< QString, VarType* > m_stringTypeMap;
    QMap< TypeId, VarType* > m_idTypeMap;
    void dataConverter(TypeId typeId, char* data, VarValue& value);
};

class Var
{
public:
    Var() {}
    Var(int _id, VarType* _varType, QString _name);
   // Var(int _id, VarType* _varType, QString _name);
    Var(int _id, VarValue _value);
    Var(int _id, VarState state);
    int id() {return m_id;}
    VarState state() {return m_state;}
    QString name() {return m_name;}
    VarType* varType() {return m_varType;}
    char* pValue() {return (char*)&m_value;}
    virtual VarValue value() {return m_value;}
protected:
private:
    int m_id;
    VarType * m_varType;
    QString m_name;
    VarState m_state;
    VarValue m_value;
};

class VarList: public QList< Var *>
{
public:
    VarList() {}
    virtual ~VarList() {}
    void appendVar(int id, char * pData);
    void appendVar(int id, VarType* varType, QString name);
    inline Var& operator[] (int id) const
    {
        if(*m_idVarMap.contains(id))
        {
            return *m_idVarMap[id];
        }
        else
        {
            return 0;
        };
    }
private:
    QMap< int, Var * > m_idVarMap;
};

VarList* globalVarList();

void createGlobalVarList();

void appendVarToGlobalList(int id, TypeId typeId, QString name);

void deleteGlobalVarList();

//-------------------------------------------
TypeDescriptors* globalTypeDescriptor();

void createTypeDescriptor();

void deleteTypeDescriptor();

#endif // VARS_H

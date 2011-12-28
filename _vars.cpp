#include "vars.h"

VarList* _globalVarList = 0;

VarList* globalVarList()
{
    return _globalVarList;
}

void createGlobalVarList()
{
    _globalVarList = new VarList;
}

void deleteGlobalVarList()
{
    delete _globalVarList;
}
//---------------------------------------------------------------
TypeDescriptors* _globalTypeDescriptor = 0;

TypeDescriptors* globalTypeDescriptor()
{
    return _globalTypeDescriptor;
}

void createTypeDescriptor()
{
    _globalTypeDescriptor = new TypeDescriptors;
}

void deleteTypeDescriptor()
{
    delete _globalTypeDescriptor;
}
//---------------------------------------------------------------
TypeDescriptors::TypeDescriptors()
{
    static VarType typeTable[] =
    {
        {TypeUndefined, false, {-1, -1, -1, -1, -1, -1, -1, -1}, 0, "undefined"},
        {TypeBool, true, {0, -1, -1, -1, -1, -1, -1, -1}, 1, "bool"},
        {TypeInt16, true, {0, 1, -1, -1, -1, -1, -1, -1}, 2, "int16"},
        {TypeUInt16, true, {0, 1, -1, -1, -1, -1, -1, -1}, 2, "uint16"},
        {TypeInt32, true, {0, 1, 2, 3, -1, -1, -1, -1}, 4, "int32"},
        {TypeUInt32, true, {0, 1, 2, 3, -1, -1, -1, -1}, 4, "uint32"},
        {TypeFloat, true, {0, 1, 2, 3, -1, -1, -1, -1}, 4, "float"}
    };
    m_stringTypeMap[""] = &typeTable[TypeUndefined]; // the default value for the map
    //for the m_idTypeMap the default value will be set to zero automatically ();
    for(int i = 0; i < (int)TypeFloat; ++i )
    {
        m_stringTypeMap[typeTable[i].name] = &typeTable[i];
        m_idTypeMap[typeTable[i].id] = &typeTable[i];
    };
}
/*
TypeId TypeDescriptors::typeId(QString typeName)
{
    return m_stringTypeMap[typeName].id;
}

QString TypeDescriptors::typeName(TypeId typeId)
{
    return (m_idTypeMap[typeId].name);
}

int TypeDescriptors::size(TypeId typeId)
{
    return (m_idTypeMap[typeId].size);
}
*/
/*
VarType varType(QString typeName)
{
    return m_stringTypeMap[typeName];
}

VarType varType(TypeId typeId)
{
    return m_idTypeMap[typeId];
}
*/
void TypeDescriptors::dataConverter(TypeId typeId, char* data, VarValue& value)
{
    switch(typeId)
    {
    case TypeUndefined:
        value.Int = 0;
        break;
    case TypeBool:
    case TypeInt16:
    case TypeUInt16:
    case TypeInt32:
    case TypeUInt32:
    case TypeFloat:
        VarType* t = m_idTypeMap[typeId];
        for(int i = 0; i < t->size; i++)
        {
            value.data[i] = data[t->byteOrder[i]];
        };
        break;
    };
}

//------------------------------------------------------------
Var::Var(int _id, VarType* _varType, QString _name): m_id(_id), m_varType(_varType), m_name(_name)
{

}

Var::Var(int _id, VarValue _value): m_id(_id), m_value(_value)
{

}

Var::Var(int _id, VarState state): m_id(_id), m_state(state)
{

}

//-----------------------------------------------------------
void VarList::appendVar(int id, char * pData)
{
    VarValue value;

    //find a variable with this id in th e global list
    Var* tempVar = m_idVarMap[id];
    if(tempVar)
    {
  //  globalTypeDescriptor()->dataConverter(tempVar->varType(), pData, tempVar->pValue());
//        for(int i = 0; i < tempVar->varType()->size; ++i);//  globalTypeDescriptor()->size(tempVar->varType()); ++i)
//        {
//            (char)(tempVar->pValue() + i)* = (char)(pData + i)*;
//        };
        append(new Var(id, value));
    };
}

//----------------------------------------------------------
void VarList::appendVar(int id, VarType* varType, QString name)
{
    Var* tempVar = new Var(id, varType, name);
    append(tempVar);
    m_idVarMap[id] = tempVar;
}

#include "vars.h"

VarList& globalVarList()
{
    static VarList gvl;
    return gvl;
}

TypedVarMap::TypedVarMap()
{
    if(!m_map.size())
    {
        m_map[TypeBool::name()] = new BoolVar();
        m_map[TypeInt16::name()] = new Int16Var();
        m_map[TypeUInt16::name()] = new UInt16Var();
        m_map[TypeInt32::name()] = new Int32Var();
        m_map[TypeUInt32::name()] = new UInt32Var();
        m_map[TypeFloat::name()] = new FloatVar();
    };
}

TypedVarMap::~TypedVarMap()
{
//    QMap< QString, Var * >::iterator iter;

    foreach(Var* pVar, m_map)
    {
        delete pVar;
    };
}

Var* TypedVarMap::var(QString typeName)
{
    if(m_map.contains(typeName))
    {
        return m_map.value(typeName);
    }
    else
    {
        return 0;
    }
}

TypedVarMap& globalTypedVarMap()
{
    static TypedVarMap tvm;
    return tvm;
}

/*
class TypeMap: QMap< QString, TypeBase* >
{
    TypeMap()
    {
        static TypeBool boolType;
        static TypeInt16 int16Type;
        static TypeUInt16 uInt16Type;
        static TypeInt32 int32Type;
        static TypeUInt32 uInt32Type;
        static TypeFloat floatType;

        insert(boolType.name(), &boolType);
        insert(int16Type.name(), &int16Type);
        insert(uInt16Type.name(), &uInt16Type);
        insert(int32Type.name(), &int32Type);
        insert(uInt32Type.name(), &uInt32Type);
        insert(floatType.name(), &floatType);
    }
};

TypeBase* getTypeByName(const QString name)
{
    static TypeMap typeMap;
    if(typeMap.contains(name))
    {
        return typeMap[name];
    }
    else
    {
        return 0;
    }
}
*/

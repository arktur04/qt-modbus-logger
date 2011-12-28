#ifndef VARS_H
#define VARS_H

#include <QString>
#include <QByteArray>
#include <QList>
#include <QMap>

class TypeBase
{
public:
    static inline QString name() {return "type_base";}
    static inline int size() {return 0;}
    static inline QByteArray& byteOrder()
    {
        static QByteArray ba;
        return ba;
    }
};

class TypeBool: public TypeBase
{
public:
    static inline QString name() {return "bool";}
    static inline int size() {return -1;}  //special size handling
    static inline QByteArray& byteOrder()
    {
        static QByteArray ba;
        ba[0] = 0;
        return ba;
    }
};

class TypeInt16: public TypeBase
{
public:
    static inline QString name() {return "int16";}
    static inline int size() {return 2;}
    static inline QByteArray& byteOrder()
    {
        static QByteArray ba;
        ba[0] = 0;
        ba[1] = 1;
        return ba;
    }
};

class TypeUInt16: public TypeBase
{
public:
    static inline QString name() {return "uint16";}
    static inline int size() {return 2;}
    static inline QByteArray& byteOrder()
    {
        static QByteArray ba;
        ba[0] = 0;
        ba[1] = 1;
        return ba;
    }
};

class TypeInt32: public TypeBase
{
public:
    static inline QString name() {return "int32";}
    static inline int size() {return 4;}
    static inline QByteArray& byteOrder()
    {
        static QByteArray ba;
        ba[0] = 0;
        ba[1] = 1;
        ba[2] = 2;
        ba[3] = 3;
        return ba;
    }
};

class TypeUInt32: public TypeBase
{
public:
    static inline QString name() {return "uint32";}
    static inline int size() {return 4;}
    static inline QByteArray& byteOrder()
    {
        static QByteArray ba;
        ba[0] = 0;
        ba[1] = 1;
        ba[2] = 2;
        ba[3] = 3;
        return ba;
    }
};

class TypeFloat: public TypeBase
{
public:
    static inline QString name() {return "float";}
    static inline int size() {return 4;}
    static inline QByteArray& byteOrder()
    {
        static QByteArray ba;
        ba[0] = 0;
        ba[1] = 1;
        ba[2] = 2;
        ba[3] = 3;
        return ba;
    }
};

class VarValue
{
public:
    VarValue() {}
    VarValue(bool boolVar): m_boolVal(boolVar) {}
    VarValue(int intVal): m_intVal(intVal) {}
    VarValue(unsigned int uIntVal): m_uIntVal(uIntVal) {}
    VarValue(float floatVal): m_floatVal(floatVal) {}

    inline bool boolVal() {return m_boolVal;}
    inline void setBoolVal(bool boolVal) {m_boolVal = boolVal;}
    inline int intVal() {return m_intVal;}
    inline void setIntVal(int intVal) {m_intVal = intVal;}
    inline unsigned int uIntVal() {return m_uIntVal;}
    inline void setUIntVal(unsigned int uIntVal) {m_uIntVal = uIntVal;}
    inline float floatVal() {return m_floatVal;}
    inline void setFloatVal(float floatVal) {m_floatVal = floatVal;}
    operator bool() {return m_boolVal;}
    operator int() {return m_intVal;}
    operator unsigned int() {return m_uIntVal;}
    operator float() {return m_floatVal;}
private:
    bool m_boolVal;
    int m_intVal;
    unsigned int m_uIntVal;
    float m_floatVal;
};

TypeBase* getTypeByName(const QString name);

enum VarState {Good, Bad, TimeOut, Undefined};

class Var
{
public:
    Var() {}
  //  Var(int id, QString name): m_id(id), m_name(name) {}
  //  Var(int id, TypeBase* varType, QString _name);
  //  Var(int id, VarValue value);
  //  Var(int id, VarState state);
  //  Var(const Var& other);

    int id() {return m_id;}
    void setId(int id) {m_id = id;}
    void setName(QString name) {m_name = name;}
    VarState state() {return m_state;}
    QString name() {return m_name;}
    virtual TypeBase& varType()
    {
        static TypeBase t;
        return t;
    }
    VarValue& value() {return m_value;}
protected:
private:
    int m_id;
    TypeBase* m_varType;
    QString m_name;
    VarState m_state;
    VarValue m_value;
};

class BoolVar: public Var
{
public:
    BoolVar(): m_boolValue(false) {}
    bool& BoolValue() {return m_boolValue;}
    virtual TypeBase& varType()
    {
        static TypeBool t;
        return t;
    }
private:
    bool m_boolValue;
};

class Int16Var: public Var
{
public:
    Int16Var(): m_intValue(0) {}
    int& IntValue() {return m_intValue;}
    virtual TypeBase& varType()
    {
        static TypeInt16 t;
        return t;
    }
private:
    int m_intValue;
};

class UInt16Var: public Var
{
public:
    UInt16Var(): m_intValue(0) {}
    int& intValue() {return m_intValue;}
    //------------------------------------------
    // type info
    QString typeName() {return "uint16";}
    int size() {return 2;}
    virtual TypeBase& varType()
    {
        static TypeUInt16 t;
        return t;
    }
private:
    int m_intValue;
};

class Int32Var: public Var
{
public:
    Int32Var(): m_intValue(0) {}
    int& intValue() {return m_intValue;}
    virtual TypeBase& varType()
    {
        static TypeInt32 t;
        return t;
    }
private:
    int m_intValue;
};

class UInt32Var: public Var
{
public:
    UInt32Var(): m_intValue(0) {}
    int& intValue() {return m_intValue;}
    virtual TypeBase& varType()
    {
        static TypeInt32 t;
        return t;
    }
private:
    int m_intValue;
};

class FloatVar: public Var
{
public:
    FloatVar(): m_floatValue(0) {}
    int& floatValue() {return m_floatValue;}
    virtual TypeBase& varType()
    {
        static TypeFloat t;
        return t;
    }
private:
    int m_floatValue;
};
//-----------------------------------------------

class VarList: public QList< Var *>
{
public:
    VarList() {}
    void appendVar(Var& var)
    {
        append(&var);
        m_idVarMap[var.id()] = &var;
    }

    inline Var* operator[] (int id) const
    {
        if(m_idVarMap.contains(id))
        {
            return m_idVarMap[id];
        }
        else
        {
            return 0;
        };
    }
private:
    QMap< int, Var * > m_idVarMap;
};

VarList& globalVarList();

class TypedVarMap
{
public:
    TypedVarMap();
    ~TypedVarMap();
    Var* var(QString typeName);
private:
    QMap< QString, Var * > m_map;
};

TypedVarMap& globalTypedVarMap();

#endif // VARS_H

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "whimsynote.h"
#include "whimsybase.h"

#define WHIMSYVARIANT_ENABLE_TYPE_CASTING      1

typedef uint64_t    FlagType;

namespace whimsycore
{

class Variant : public Base
{
public:
    enum Type
    {
        Null,
        Bool,
        Nibble,
        Byte,
        Word,
        Integer,
        Long,
        Float,
        Double,
        Note,
        String,
        VariantArray,
        GenericPointer
    };

    enum OutputStringFormat
    {
        Format_Normal,
        Format_Hex
    };

    template<class T>
    struct VDPointer
    {
        mutable int                 _refcount;
        T*                          _data;

        VDPointer() : _refcount(1){}
        VDPointer(const T& ref) : _refcount(1){_data = new T(ref);}

        virtual ~VDPointer(){
            delete(_data);
        }

        void reference() const
        {
            _refcount++;
        }

        void dereference() const
        {
            //assert(_refcount > 0);
            if(--_refcount == 0)
            {
                //delete(_data);
                delete(this);
            }
        }
    };

    union VariantData
    {
        bool                                    _Bool;
        unsigned char                           _Byte;
        unsigned short int                      _Word;
        int                                     _Integer;
        float                                   _Float;
        double                                  _Double;
        long long                               _Long;
        NoteProto                               _Note;
        VDPointer<std::string>*                 _String;
        VDPointer<std::vector<Variant> >*       _VariantArray;
        VDPointer<char>*                        _Pointer;
    };

    WHIMSY_OBJECT_NAME("WhimsyVariant")

    static const Variant     null;

    Variant();
    Variant(const Variant& wref);
    Variant(bool _bool);
    Variant(int _int);
    Variant(long long _long);
    Variant(float _float);
    Variant(double _double);
    Variant(whimsycore::Note _note);
    Variant(const char* _cstr);
    Variant(std::string _cstr);
    Variant(std::vector<Variant> _array);

    Variant&                        operator=(const Variant& wref);

    const char*                     type() const;
    Variant::Type                   typeID() const;

    static const char*              typeToString(Variant::Type t);

    bool                            isNull() const;

    Variant&                        convert(Variant::Type t);

    bool                            boolValue() const;
    unsigned char                   nibbleValue() const;
    unsigned char                   byteValue() const;
    unsigned short int              wordValue() const;
    int                             intValue() const;
    long long int                   longValue() const;
    float                           floatValue() const;
    double                          doubleValue() const;
    whimsycore::Note                noteValue() const;
    std::string                     stringValue() const;
    std::vector<Variant>            arrayValue() const;

#if WHIMSYVARIANT_ENABLE_TYPE_CASTING == 1
    template<typename T>            operator T(){return value<T>();}
    template<typename T> T          value() const;
#endif

    std::string                     toString() const;
    std::string                     toString(OutputStringFormat ot) const;

    static bool                     typeUsesExtraMemory(Type t);
    static bool                     typeIsNumeric(Type t);
    static bool                     typeIsInteger(Type t);
    static bool                     typeIsFloatingPoint(Type t);

    ~Variant();

private:
    Type                _data_type;
    VariantData         _data;

    bool                            isUsingExtraMemory() const;
    void                            noteFix();
};
}


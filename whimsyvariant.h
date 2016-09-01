#ifndef WHIMSYVARIANT_H
#define WHIMSYVARIANT_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "whimsynote.h"
#include "whimsybase.h"

typedef uint64_t    FlagType;

class WhimsyVariant : public WhimsyBase
{
public:
    enum VariantType
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
        bool                                    Bool;
        unsigned char                           Byte;
        unsigned short int                      Word;
        int                                     Integer;
        float                                   Float;
        double                                  Double;
        long long                               Long;
        WhimsyNoteProto                         Note;
        VDPointer<std::string>*                 String;
        VDPointer<std::vector<WhimsyVariant>>*  VariantArray;
        VDPointer<char>*                        GenericPointer;
    };

    WHIMSY_OBJECT_NAME("WhimsyVariant")

    WhimsyVariant();
    WhimsyVariant(const WhimsyVariant& wref);
    WhimsyVariant(bool _bool);
    WhimsyVariant(int _int);
    WhimsyVariant(long long _long);
    WhimsyVariant(float _float);
    WhimsyVariant(double _double);
    WhimsyVariant(WhimsyNote _note);
    WhimsyVariant(const char* _cstr);
    WhimsyVariant(std::string _cstr);
    WhimsyVariant(std::vector<WhimsyVariant> _array);

    WhimsyVariant&                  operator=(const WhimsyVariant& wref);

    const char*                     type() const;
    WhimsyVariant::VariantType      typeID() const;

    static const char*              typeToString(WhimsyVariant::VariantType t);

    bool                            isNull() const;

    WhimsyVariant&                  convertTo(WhimsyVariant::VariantType t);

    bool                            boolValue() const;
    unsigned char                   nibbleValue() const;
    unsigned char                   byteValue() const;
    unsigned short int              wordValue() const;
    int                             intValue() const;
    long long                       longValue() const;
    float                           floatValue() const;
    double                          doubleValue() const;
    WhimsyNote                      noteValue() const;
    std::string                     stringValue() const;
    std::vector<WhimsyVariant>      arrayValue() const;

    std::string                     toString() const;

    ~WhimsyVariant();

private:
    VariantType         _data_type;
    VariantData         _data;

    bool isUsingExtraMemory() const;
};

#endif // WHIMSYVARIANT_H

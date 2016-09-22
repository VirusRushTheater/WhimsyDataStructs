#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "whimsyvariant.h"
#include "whimsyvector.h"

namespace whimsycore
{

class TypedTable;

/**
 */
struct SoftTypedVector : public WhimsyVector<Variant>
{
    friend class TypedTable;

    Variant::Type   type;

    SoftTypedVector(Variant::Type _type) :
        type(_type){}

    SoftTypedVector(Variant::Type _type, const SoftTypedVector& stv);
    SoftTypedVector(Variant::Type _type, const std::vector<Variant>& stv);

    void update();
};

class TypedTable : public Base
{
private:
    unsigned int                    _width, _height;
    unsigned int                    _addrow_cursor;
    std::vector<Variant::Type>      _types;
    std::vector<SoftTypedVector>    _cols;

public:
    WHIMSY_OBJECT_NAME("Core/TypedTable")

    TypedTable() : _width(0), _height(0), _addrow_cursor(0) {}

    template<typename ... Args>
    void addFields(Args ... others)
    {
        addFieldsVector(WhimsyVector<Variant::Type>(others...));
    }

    template<typename ... Args>
    void addRow(Args ... others)
    {
        addRowVector(WhimsyVector<Variant>(others...));
    }


    TypedTable& addFieldsVector(WhimsyVector<Variant::Type> types);
    TypedTable& addRowVector(WhimsyVector<Variant> datas);

    TypedTable& removeRow(size_t position);

    std::string toString() const;
};

}

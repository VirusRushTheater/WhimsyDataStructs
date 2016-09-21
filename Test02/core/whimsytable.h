#pragma once

#include <vector>
#include <string>
#include <sstream>
#include "whimsyvariant.h"
#include "whimsyvector.h"

namespace whimsycore
{

class TypedTable;

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
protected:
    unsigned int                    _width, _height;
    unsigned int                    _addrow_cursor;
    std::vector<Variant::Type>      _types;
    std::vector<SoftTypedVector>    _cols;

public:
    WHIMSY_OBJECT_NAME("Core/TypedTable")

    TypedTable() : _width(0), _height(0), _addrow_cursor(0) {}

    template<typename ... Args>
    void addFields(Variant::Type type, Args ... others)
    {
        SoftTypedVector*    newcol;
        SoftTypedVector     stv(type);

        _cols.push_back(stv);

        if(_height > 0)
        {
            newcol = &(_cols[_cols.size() - 1]);
            newcol->insert(newcol->end(), _height, Variant::null);
        }

        _width++;
        addFields(others...);
    }

    void addFields()
    {
    }


    template<typename ... Args>
    void addRow(Variant cell, Args ... others)
    {
        _cols[_addrow_cursor++].push_back(cell);

        if(_addrow_cursor == _width)
            addRow();
        else
            addRow(others...);
    }

    void addRow()
    {
        if(_addrow_cursor < _width)
        {
            while(_addrow_cursor < _width)
                _cols[_addrow_cursor++].push_back(Variant::null);
        }

        _height++;
        _addrow_cursor = 0;
    }


    std::string toString() const;
};

}

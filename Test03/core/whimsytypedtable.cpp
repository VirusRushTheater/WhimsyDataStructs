#include "whimsytypedtable.h"

using namespace whimsycore;

SoftTypedVector::SoftTypedVector(Variant::Type _type, const SoftTypedVector &stv) :
    type(_type)
{
    Variant tempval;
    std::vector<Variant>::const_iterator it;
    this->reserve(stv.size());

    if(type == Variant::Null)
    {
        this->insert(this->end(), stv.begin(), stv.end());
    }
    else
    {
        for(it = stv.begin(); it != stv.end(); it++)
        {
            tempval = *it;
            this->push_back(tempval.convert(type));
        }
    }
}

SoftTypedVector::SoftTypedVector(Variant::Type _type, const std::vector<Variant> &stv) :
    type(_type)
{
    Variant tempval;
    std::vector<Variant>::const_iterator it;
    this->reserve(stv.size());

    if(type == Variant::Null)
    {
        this->insert(this->end(), stv.begin(), stv.end());
    }
    else
    {
        for(it = stv.begin(); it != stv.end(); it++)
        {
            tempval = *it;
            this->push_back(tempval.convert(type));
        }
    }
}

void SoftTypedVector::update()
{
    SoftTypedVector::iterator it;
    for(it = this->begin(); it != this->end(); it++)
        it->convert(this->type);
}

// --------------------------------

TypedTable& TypedTable::addFieldsVector(WhimsyVector<Variant::Type> types)
{
    size_t                                  vtypos;

    for(vtypos = 0; vtypos < types.size(); vtypos++)
    {
        _cols.push_back(SoftTypedVector(types[vtypos]));
        if(_height > 0)
            _cols[vtypos].insert(_cols[vtypos].end(), _height, Variant::null);

        _width++;
    }

    return *this;
}

TypedTable& TypedTable::addRowVector(WhimsyVector<Variant> datas)
{
    size_t                                  vitpos;
    for(vitpos = 0; vitpos < datas.size() && vitpos < _width; vitpos++)
    {
        _cols[vitpos].push_back(datas[vitpos].convert(_cols[vitpos].type));
        if(vitpos == _width)
            break;
    }

    if(vitpos < _width)
    {
        for(; vitpos < _width; vitpos++)
            _cols[vitpos].push_back(Variant::null);
    }

    _height++;
    return *this;
}

std::string TypedTable::toString() const
{
    std::ostringstream retval;

    if(_width == 0 || _height == 0)
        return std::string("[]");

    retval << "[";
    for(unsigned int j = 0; j < _height; j++)
    {
        retval << "[";
        for(unsigned int i = 0; i < _width; i++)
        {
            retval << _cols[i][j].toString(Variant::Format_Hex);
            if(i != _width - 1)
                retval << "\t";
        }
        retval << "]";

        if(j != _height - 1)
            retval << std::endl;
    }
    retval << "]";

    return retval.str();
}

TypedTable& TypedTable::removeRow(size_t position)
{
    if(position >= _height)
        return *this;

    for(unsigned int i = 0; i < _cols.size(); i++)
        _cols[i].erase(_cols[i].begin() + position);

    _height--;

    return *this;
}

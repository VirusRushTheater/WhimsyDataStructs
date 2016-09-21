
#include "whimsytable.h"

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
                retval << "\t, ";
        }
        retval << "]";

        if(j != _height - 1)
            retval << std::endl;
    }
    retval << "]";

    return retval.str();
}

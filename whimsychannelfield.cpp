#include <sstream>

#include "whimsychannelfield.h"
#include "whimsyexception.h"

using namespace whimsycore;

Variant& ChannelField::at(unsigned int pos)
{
    if(pos >= _data.size())
        throw(Exception(this, Exception::ArrayOutOfBounds, "Method at()"));

    return _data.at(pos);
}

Variant& ChannelField::operator [](unsigned int pos)
{
    return at(pos);
}

ChannelField& ChannelField::append(const Variant& data)
{
    _data.push_back(data);
    return *this;
}

ChannelField& ChannelField::operator <<(const Variant& data)
{
    return append(data);
}

ChannelField& ChannelField::remove(int index)
{
    int datasize = _data.size();
    if(index >= datasize || index < -datasize)
        throw(Exception(this, Exception::ArrayOutOfBounds, "Method remove()"));

    if(index >= 0)
        _data.erase(_data.begin() + index);
    else
        _data.erase(_data.end() - index + 1);
    return *this;
}

ChannelField& ChannelField::removeLast()
{
    _data.erase(_data.end() - 1);
    return *this;
}

ChannelField& ChannelField::insert(const Variant& data, unsigned int pos)
{
    if(pos > _data.size())
        throw(Exception(this, Exception::ArrayOutOfBounds, "Method insert()"));

    _data.insert(_data.begin() + pos, data);
    return *this;
}


Variant::Type ChannelField::type() const
{
    return _type;
}

const char* ChannelField::typeName() const
{
    return Variant::typeToString(_type);
}

std::string ChannelField::name() const
{
    return std::string(_name);
}

void ChannelField::setName(std::string nm)
{
    _name = nm;
}

std::string ChannelField::toString() const
{
    std::ostringstream retval;
    std::vector<Variant>::const_iterator it =           _data.begin();
    std::vector<Variant>::const_iterator almost_end =   _data.end() - 1;

    retval << "WhimsyChannelField \"" << _name << "\" [" << Variant::typeToString(_type) << "] -> [";

    for(; it != _data.end(); it++)
    {
        retval << it->toString();
        if(it != almost_end)
            retval << ", ";
    }

    retval << "]";

    return retval.str();
}

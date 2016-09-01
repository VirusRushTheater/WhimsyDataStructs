#include <sstream>

#include "whimsychannelfield.h"
#include "whimsyexception.h"

WhimsyVariant& WhimsyChannelField::at(unsigned int pos)
{
    if(pos >= _data.size())
        throw(WhimsyException(this, WhimsyException::ArrayOutOfBounds, "Method at()"));

    return _data.at(pos);
}

WhimsyVariant& WhimsyChannelField::operator [](unsigned int pos)
{
    return at(pos);
}

WhimsyChannelField& WhimsyChannelField::append(const WhimsyVariant& data)
{
    _data.push_back(data);
    return *this;
}

WhimsyChannelField& WhimsyChannelField::operator <<(const WhimsyVariant& data)
{
    return append(data);
}

WhimsyChannelField& WhimsyChannelField::remove(int index)
{
    int datasize = _data.size();
    if(index >= datasize || index < -datasize)
        throw(WhimsyException(this, WhimsyException::ArrayOutOfBounds, "Method remove()"));

    if(index >= 0)
        _data.erase(_data.begin() + index);
    else
        _data.erase(_data.end() - index + 1);
    return *this;
}

WhimsyChannelField& WhimsyChannelField::removeLast()
{
    _data.erase(_data.end() - 1);
    return *this;
}

WhimsyChannelField& WhimsyChannelField::insert(const WhimsyVariant& data, unsigned int pos)
{
    if(pos > _data.size())
        throw(WhimsyException(this, WhimsyException::ArrayOutOfBounds, "Method insert()"));

    _data.insert(_data.begin() + pos, data);
    return *this;
}

std::string WhimsyChannelField::toString() const
{
    std::ostringstream retval;
    std::vector<WhimsyVariant>::const_iterator it =           _data.begin();
    std::vector<WhimsyVariant>::const_iterator almost_end =   _data.end() - 1;

    retval << "WhimsyChannelField \"" << _name << "\" [" << WhimsyVariant::typeToString(_type) << "] -> [";

    for(; it != _data.end(); it++)
    {
        retval << it->toString();
        if(it != almost_end)
            retval << ", ";
    }

    retval << "]";

    return retval.str();
}

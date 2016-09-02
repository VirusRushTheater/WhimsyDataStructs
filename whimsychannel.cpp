#include <iomanip>
#include <string>

#include "whimsychannel.h"

using namespace whimsycore;

Channel& Channel::addField(Variant::Type type, std::string name)
{
    int current_field_amount = _fields.size();

    // Case insensitive. To uppercase.
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    // Element exists, therefore no field added.
    if(_name_map.find(name) != _name_map.end())
    {
        throw Exception(this, Exception::NameConflict, name.c_str());
        return *this;
    }
    else
    {
        _fields.push_back(ChannelField(type, name));
        _name_map.insert(std::pair<std::string, int>(name, current_field_amount));
    }

    return *this;
}

Channel& Channel::removeField(std::string name)
{
    int pos_to_be_removed;

    // Case insensitive. To uppercase.
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    // Element does not exist.
    if(_name_map.find(name) == _name_map.end())
    {
        throw Exception(this, Exception::NotFound, name.c_str());
        return *this;
    }
    else
    {
        pos_to_be_removed =     _name_map[name];
        _name_map.erase(_name_map.find(name));
        _fields.erase(_fields.begin() + pos_to_be_removed);
    }

    return *this;
}

std::string Channel::toString() const
{
    std::ostringstream                                  retval, headerstr;
    std::vector<std::vector<Variant>::const_iterator>   fielddata, fieldend;
    std::deque<ChannelField>::const_iterator            fieldit;
    unsigned int                                        rown, coln, rowtotal;

    rowtotal = 0x8FFFFFF; // Maximum unsigned int possible.

    // General info
    retval << "[WhimsyChannel] Field amount: " << _fields.size() << std::endl;
    for(fieldit = _fields.begin(); fieldit != _fields.end(); fieldit++)
    {
        retval << "Field \"" << fieldit->name() << "\" [" << fieldit->typeName() << "]" << std::endl;
        fielddata.push_back(fieldit->_data.begin());
        fieldend.push_back(fieldit->_data.end());
        if(fieldit->_data.size() < rowtotal)
            rowtotal = fieldit->_data.size();

        // Prepares header.
        headerstr << Utility::forceWidth(fieldit->name(), 8, ' ') << " ";
    }

    retval << "Row count: " << rowtotal << std::endl;

    // Channel headers
    retval << "#   " << headerstr.str();
    retval << std::endl;

    // Channel data
    for(rown = 0; rown < rowtotal; rown++)
    {
        // Row number
        retval << std::setfill('0') << std::setw(3) << rown << " ";

        // Column info
        for(coln = 0; coln < fielddata.size(); coln++)
        {
            retval << Utility::forceWidth(fielddata.at(coln)->toString(Variant::Format_Hex), 8) << " ";
            fielddata.at(coln)++;
        }

        // End line
        retval << std::endl;
    }

    return retval.str();
}

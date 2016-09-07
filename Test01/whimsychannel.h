#pragma once

#include <deque>
#include <string>
#include <map>
#include <algorithm>

#include "whimsybase.h"
#include "whimsychannelfield.h"
#include "whimsyexception.h"

namespace whimsycore
{

class ChannelRow;

class Channel : public Base
{
    friend class ChannelRow;

public:
    std::deque<ChannelField>      _fields;
    std::map<std::string, int>    _name_map;

public:
    WHIMSY_OBJECT_NAME("WhimsyChannel")

    Channel&    addField(Variant::Type type, std::string name);
    Channel&    removeField(std::string name);

    std::string toString() const;
};
}

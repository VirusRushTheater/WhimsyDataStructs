#pragma once

#include <vector>
#include <string>

#include "whimsybase.h"
#include "whimsyvariant.h"

namespace whimsycore
{
class Channel;

class ChannelField : public Base
{
    friend class Channel;

private:
    std::vector<Variant>  _data;
    Variant::Type  _type;
    std::string                 _name;

public:
    WHIMSY_OBJECT_NAME("WhimsyChannelField")

    ChannelField() : _type(Variant::Byte), _name(std::string("Nameless"))
    {}
    ChannelField(Variant::Type type, std::string name) :
        _type(type), _name(name)
    {}

    Variant&          at(unsigned int pos);
    Variant&          operator[](unsigned int pos);

    ChannelField&     append(const Variant& data);
    ChannelField&     operator <<(const Variant& data);

    ChannelField&     remove(int index);
    ChannelField&     removeLast();

    ChannelField&     insert(const Variant& data, unsigned int pos);

    Variant::Type  type() const;
    const char*             typeName() const;

    std::string             name() const;
    void                    setName(std::string nm);

    std::string             toString() const;
};
}

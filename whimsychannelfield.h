#ifndef WHIMSYCHANNELFIELD_H
#define WHIMSYCHANNELFIELD_H

#include <vector>
#include <string>

#include "whimsybase.h"
#include "whimsyvariant.h"

class WhimsyChannelField : public WhimsyBase
{
public:
    std::vector<WhimsyVariant>  _data;
    WhimsyVariant::VariantType  _type;
    std::string                 _name;

public:
    WHIMSY_OBJECT_NAME("WhimsyChannelField")

    WhimsyChannelField() : _type(WhimsyVariant::Byte), _name(std::string("Nameless"))
    {}
    WhimsyChannelField(WhimsyVariant::VariantType type, std::string name) :
        _type(type), _name(name)
    {}

    WhimsyVariant&          at(unsigned int pos);
    WhimsyVariant&          operator[](unsigned int pos);

    WhimsyChannelField&     append(const WhimsyVariant& data);
    WhimsyChannelField&     operator <<(const WhimsyVariant& data);

    std::string             toString() const;

    WhimsyChannelField&     remove(int index);
    WhimsyChannelField&     removeLast();

    WhimsyChannelField&     insert(const WhimsyVariant& data, unsigned int pos);
};

#endif // WHIMSYCHANNELFIELD_H

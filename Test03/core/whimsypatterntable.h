#pragma once

#include "whimsybase.h"
#include "whimsyvariant.h"
#include "whimsyvector.h"

#include <string>
#include <map>

namespace whimsycore {

/**
 * @brief The PatternTableHeader struct
 */
struct PatternTableHeader
{
    std::string     name;
    std::string     codename;
    Variant::Type   type;
    Variant         minvalue;
    Variant         maxvalue;
    bool            convertible;
};

/**
 * @brief The PatterTableField struct
 */
struct PatternTableField
{
    PatternTableHeader      header;
    WhimsyVector<Variant>   data;
};

/**
 * @brief The PatternTable class
 */
class PatternTable : public Base
{
private:

public:

};

}

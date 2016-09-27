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

    PatternTableHeader(){}
    PatternTableHeader(std::string name_, std::string codename_, Variant::Type type_,
                       Variant minvalue_ = Variant::null, Variant maxvalue_ = Variant::null, bool convertible_ = true);
};

/**
 * @brief The PatterTableField struct
 */
struct PatternTableField : public Base
{
    PatternTableHeader      header;
    WhimsyVector<Variant>   data;

public:
    WHIMSY_OBJECT_NAME("Core/PatternTableField")

    /**
     * @brief Makes sure all the data in the Variant vector is of the
     * type indicated in the header.
     */
    void sweep();

    /**
     * @brief Clears this field and imports data from another, adapting and normalizing
     * using header parameters from both tables.
     * @param originfield   Field data to import from.
     * @return  True if the data was converted. False if data is unconvertible.
     */
    bool convertFrom(const PatternTableField& originfield);
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

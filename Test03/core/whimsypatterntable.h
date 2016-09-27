#pragma once

#include "whimsybase.h"
#include "whimsyvariant.h"
#include "whimsyvector.h"

#include <string>
#include <map>

namespace whimsycore {

typedef WhimsyVector<Variant*>              PatternRow;
typedef std::map<std::string, Variant*>     MappedRow;

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

    PatternTableField() {}
    PatternTableField(PatternTableHeader ph) : header(ph) {}

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
    unsigned int                                _width, _height;
    unsigned int                                _addrow_cursor;
    WhimsyVector<PatternTableField>             fields;
    std::map<std::string, PatternTableField*>   codename_map;

    // _null_ref is a patch solution to return not-found references in the getCell methods.
    // Is there a cleaner way to do this?
    Variant                                     _null_ref;

public:
    /**
     * @brief Manually adds a typed field into this table.
     * @param name              Name of the field, for aesthetical reasons.
     * @param codename          Codename of the field, for functional reasons (like allowing the engine and IO modules to identify this field)
     * @param type              Variable type of this field.
     * @param minvalue          Minimum value this variable can take. By default, it's constrained only by this variable's type. Leave it blank or use Variant::null if that makes no sense (like in a string or an array)
     * @param maxvalue          Maximum value this variable can take. By default, it's constrained only by this variable's type. Leave it blank or use Variant::null if that makes no sense (like in a string or an array)
     * @param convertible       Is this variable convertible to others?
     * @return  Reference to this object.
     */
    PatternTable&   addField(std::string name, std::string codename, Variant::Type type,
                             Variant minvalue = Variant::null, Variant maxvalue = Variant::null, bool convertible = true);

    /**
     * @brief Overloaded method.
     * @param ph                Struct with initial values ready.
     * @return  Reference to this object.
     */
    PatternTable&   addField(PatternTableHeader ph);

    /**
     * @brief Appends a row with the elements in the vector, in order. If it lacks elements, it fills with Variant::null. If there are too many elements, it just discards them.
     * @param cells             Vector with the row's new elements.
     * @return  Reference to this object.
     */
    PatternTable&   addRowVector(const WhimsyVector<Variant>& cells);

    /**
     * @brief Variadic function version of addRowVector.
     * @param others            An undetermined number of new row elements. If it lacks elements, it fills with Variant::null. If there are too many elements, it just discards them.
     * @return  Reference to this object.
     */
    template<typename ... Args>
    PatternTable& addRow(Args ... others)
    {
        return addRowVector(WhimsyVector<Variant>(others...));
    }

    /**
     * @brief Removes a row specified by position.
     * @param position          Index of the row you want to delete, starting from zero.
     * @return  Reference to this object.
     */
    PatternTable&   removeRow(size_t position);

    /**
     * @brief Removes this table's last row.
     * @return  Reference to this object.
     */
    PatternTable&   removeLastRow();

    /**
     * @brief Gets references to a given row's elements.
     * @param position  Row position, starting from zero.
     * @return  Vector with a row's elements references.
     */
    PatternRow getRow(size_t position);

    /**
     * @brief Similar to getRow. Gets references to a given row's elements, mapped to each field's codename.
     * @param position  Row position, starting from zero.
     * @return  Map with a row's elements references.
     */
    MappedRow getMappedRow(size_t position);

    /**
     * @brief Gets a cell reference, given the codename of its field and its row position.
     * @param fieldcodename     Field's codename.
     * @param position          Row position, starting from zero.
     * @return  Indicated cell reference.
     */
    Variant* getCell(std::string fieldcodename, size_t position);

    /**
     * @brief Gets a cell reference, given the index of its field.
     * @param fieldindex        Field's index, starting from zero.
     * @param position          Row position, starting from zero.
     * @return  Indicated cell reference.
     */
    Variant* getCell(size_t fieldindex, size_t position);

    /**
     * @brief Returns a string representation of this table.
     * @return
     */
    std::string toString() const;
};

}

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
 * @brief The PatternFieldHeader struct
 */
struct PatternFieldHeader : public Base
{
    std::string     name;
    std::string     id;
    Variant::Type   type;
    Variant         minvalue;
    Variant         maxvalue;
    bool            convertible;

    PatternFieldHeader(){}
    PatternFieldHeader(std::string name_, std::string codename_, Variant::Type type_,
                       Variant minvalue_ = Variant::null, Variant maxvalue_ = Variant::null, bool convertible_ = true);

    std::string toString() const {return "";}
};

/**
 * @brief The PatterTableField struct
 */
struct PatternTableField : public Base
{
    PatternFieldHeader      header;
    WhimsyVector<Variant>   data;

public:
    WHIMSY_OBJECT_NAME("Core/PatternTableField")

    PatternTableField() {}
    PatternTableField(PatternFieldHeader ph) : header(ph) {}

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

    /**
     * @brief Fills or remove rows to fit with the desired amount. Newly added fields will be filled with NULLs.
     * WARNING! This method may lead to loss of data, use with caution.
     * @param amount    Amount of rows this field will have.
     */
    void setHeight(size_t amount);

    /**
     * @brief Adds a determined number of rows at the end of this field.
     * @param amount
     */
    void addRows(size_t amount);

    /**
     * @brief Deletes a determined number of rows at the end of this field. This leads to data loss, use with moderation.
     * @param amount
     */
    void deleteRows(size_t amount);

    /**
     * @brief Gets how many data rows has this field.
     * @return How many data rows has this field.
     */
    size_t height() const;

    /**
     * @brief Erases all row data from this field.
     */
    void cleanse();
};

/**
 * @brief The PatternTable class is used to store both a channel's info and sequences of notes.
 * It's intended to be vectorized when working in a song, in order to form polymorphic sounds. That way, each channel would
 * specify a single sound, note or effect happening in the song a given time.
 */
class PatternTable : public Base
{
    friend class AbstractSong;
    friend class MappedSong;
    friend class SequencedSong;

private:
    unsigned int                                _width, _height;
    unsigned int                                _addrow_cursor;
    WhimsyVector<PatternTableField>             fields;
    std::map<std::string, PatternTableField*>   codename_map;
    std::map<std::string, int>                  codename_pos;

    std::string                                 _name, _codename;

public:
    WHIMSY_OBJECT_NAME("Core/PatternTable")

    /**
     * @brief Empty constructor. Use only for debugging purposes. For everything else, use the PatternTable(std::string, std::string) constructor instead, please.
     */
    PatternTable() : _name("Debug"), _codename("DEBUG"), _width(0), _height(0), _addrow_cursor(0) {}

    /**
     * @brief Name constructor. Gives this pattern a channel name (aesthetical reasons) and a codename (functionality reasons)
     * @param name          Complete name of this channel.
     * @param codename      Code name of this channel, for use in IO and Engine.
     */
    PatternTable(const std::string& name, const std::string& codename);

    /**
     * @brief Complete constructor. To be used in conjunction with SystemProfile's XML loading functions.
     * @param name          Complete name of this channel.
     * @param codename      Code name of this channel, for use in IO and Engine.
     * @param fields        Vector containing all the fields this channel will have.
     */
    PatternTable(const std::string& name, const std::string& codename, const WhimsyVector<PatternFieldHeader>& fields);

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
    PatternTable&   addField(const std::string& name, const std::string& codename, Variant::Type type,
                             Variant minvalue = Variant::null, Variant maxvalue = Variant::null, bool convertible = true);

    /**
     * @brief Overloaded method.
     * @param ph                Struct with initial values ready.
     * @return  Reference to this object.
     */
    PatternTable&   addField(PatternFieldHeader ph);

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
     * @brief Fills or remove rows to each field, to fit with the desired amount. Newly added fields will be filled with NULLs.
     * WARNING! This method may lead to loss of data, use with caution.
     * @param amount    Amount of rows this table will have.
     */
    void setHeight(size_t amount);

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
    Variant* getCell(const std::string& fieldcodename, size_t position);

    /**
     * @brief Gets a cell reference, given the index of its field.
     * @param fieldindex        Field's index, starting from zero.
     * @param position          Row position, starting from zero.
     * @return  Indicated cell reference.
     */
    Variant* getCell(size_t fieldindex, size_t position);

    /**
     * @brief Gets this channel's name.
     * @return
     */
    std::string getName() const;

    /**
     * @brief Gets this channel's codename.
     * @return
     */
    std::string getCodename() const;

    /**
     * @brief Appends a number of empty rows (Variant::null) to the end of each field of this table.
     * @param amount    Number of new, fresh, empty rows.
     */
    void addEmptyRows(size_t amount);

    /**
     * @brief Deletes a number of empty rows from the end of each field of this table.
     * @param amount    Number of rows to be deleted.
     */
    void deleteRows(size_t amount);

    /**
     * @brief Gets the number of rows this table has.
     * @return  The number of rows this table has.
     */
    size_t height() const;

    /**
     * @brief Returns a string representation of this table.
     * @return
     */
    std::string toString() const;
};

}

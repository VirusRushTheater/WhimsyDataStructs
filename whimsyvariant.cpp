#include "whimsyvariant.h"
#include <sstream>

/**
 * @brief Empty constructor. Initializes this variant as a null pointer.
 */
WhimsyVariant::WhimsyVariant()
{
    _data_type =            VariantType::Null;
    _data.Integer =         0;
}

/**
 * @brief Copy constructor. Doesn't deep copy memory items if in memory, but passes a reference to it.
 * @param wref      Initializing value.
 */
WhimsyVariant::WhimsyVariant(const WhimsyVariant& wref) :
    _data_type(wref._data_type),
    _data(wref._data)
{
    if(wref.isUsingExtraMemory())
        _data.GenericPointer->reference();
}

/**
 * @brief Boolean constructor. Makes this variant take the value of a boolean.
 * @param _bool_t   Initializing value.
 */
WhimsyVariant::WhimsyVariant(bool _bool)
{
    _data_type =            VariantType::Bool;
    _data.Bool =            _bool;
}

/**
 * @brief Int constructor. Makes this variant take the value of an integer.
 * @param _bool_t   Initializing value.
 */
WhimsyVariant::WhimsyVariant(int _int)
{
    _data_type =            VariantType::Integer;
    _data.Integer =         _int;
}

WhimsyVariant::WhimsyVariant(long long _long)
{
    _data_type =            VariantType::Long;
    _data.Long =            _long;
}

/**
 * @brief Float constructor. Makes this variant take the value of a float.
 * @param _float    Initializing value.
 */
WhimsyVariant::WhimsyVariant(float _float)
{
    _data_type =            VariantType::Float;
    _data.Float =           _float;
}

/**
 * @brief Double constructor. Makes this variant take the value of a double.
 * @param _double    Initializing value.
 */
WhimsyVariant::WhimsyVariant(double _double)
{
    _data_type =            VariantType::Double;
    _data.Double =          _double;
}

/**
 * @brief Note constructor. Makes this variant take the value of a note.
 * @param _note     Initializing value.
 */
WhimsyVariant::WhimsyVariant(WhimsyNote _note)
{
    _data_type =            VariantType::Note;
    _data.Note =            _note;
}

/**
 * @brief String constructor. Makes this variant take the value of a string.
 * @param _cstr     Initializing value.
 */
WhimsyVariant::WhimsyVariant(const char *_cstr)
{
    _data_type =            VariantType::String;
    _data.String =          new VDPointer<std::string>(std::string(_cstr));
    //_data.String =          new std::string(_cstr);
}

/**
 * @brief String constructor. Makes this variant take the value of a string.
 * @param _cstr     Initializing value.
 */
WhimsyVariant::WhimsyVariant(std::string _cstr)
{
    _data_type =            VariantType::String;
    _data.String =          new VDPointer<std::string>(std::string(_cstr));
    //_data.String =          new std::string(_cstr);
}

/**
 * @brief Array constructor. Makes this variant take the value of a dynamic array.
 * @param _array    Initializing value.
 */
WhimsyVariant::WhimsyVariant(std::vector<WhimsyVariant> _array)
{
    _data_type =            VariantType::VariantArray;
    _data.VariantArray =    new VDPointer<std::vector<WhimsyVariant>>(_array);
    //_data.VariantArray =    new std::vector<WhimsyVariant>(_array);
}

/**
 * @brief Assignment operator. Doesn't deep copy memory items if in memory, but passes a reference to it.
 * @param wref
 * @return
 */
WhimsyVariant& WhimsyVariant::operator=(const WhimsyVariant& wref)
{
    if(isUsingExtraMemory())
        _data.GenericPointer->dereference();

    _data_type = wref._data_type;
    _data = wref._data;

    if(wref.isUsingExtraMemory())
        _data.GenericPointer->reference();

    //std::cout << "Assigning: " << wref.representate() << std::endl;
    return *this;
}

/**
 * @brief Returns the type of this Variant, in a convenient string format.
 * @return
 */
const char* WhimsyVariant::type() const
{
    return typeToString(_data_type);
}

/**
 * @brief Returns the Type ID of this Variant.
 * @return
 */
WhimsyVariant::VariantType WhimsyVariant::typeID() const
{
    return _data_type;
}

const char* WhimsyVariant::typeToString(WhimsyVariant::VariantType t)
{
    switch(t)
    {
        case VariantType::Null:
            return "null";
        case VariantType::Bool:
            return "bool";
        case VariantType::Nibble:
            return "nibble";
        case VariantType::Byte:
            return "byte";
        case VariantType::Word:
            return "word";
        case VariantType::Integer:
            return "int";
        case VariantType::Float:
            return "float";
        case VariantType::Double:
            return "double";
        case VariantType::Long:
            return "long";
        case VariantType::Note:
            return "note";
        case VariantType::String:
            return "string";
        case VariantType::VariantArray:
            return "array";
        case VariantType::GenericPointer:
            return "pointer";
        default:
            return "unknown";
    }

    return "Unknown";
}

/**
 * @brief Tells whether this variant holds a null value or not.
 * @return
 */
bool WhimsyVariant::isNull() const
{
    return (_data_type == VariantType::Null);
}

WhimsyVariant& WhimsyVariant::convertTo(WhimsyVariant::VariantType t)
{
    long long int   inumber;
    double          dnumber;

    // Dismiss if no conversion.
    if(t == _data_type)
        return *this;

    // Any type -> Null type = Nullify (and remove extra memory if necessary)
    if(t == Null)
    {
        _data_type = Null;
        if(isUsingExtraMemory())
            _data.GenericPointer->dereference();
    }

    return *this;
}

bool WhimsyVariant::boolValue() const
{
    return _data.Bool;
}

unsigned char WhimsyVariant::nibbleValue() const
{
    return _data.Byte & 15;
}

unsigned char WhimsyVariant::byteValue() const
{
    return _data.Byte;
}

unsigned short int WhimsyVariant::wordValue() const
{
    return _data.Word;
}

int WhimsyVariant::intValue() const
{
    return _data.Integer;
}

long long WhimsyVariant::longValue() const
{
    return _data.Long;
}

float WhimsyVariant::floatValue() const
{
    return _data.Float;
}

double WhimsyVariant::doubleValue() const
{
    return _data.Double;
}

WhimsyNote WhimsyVariant::noteValue() const
{
    return WhimsyNote(static_cast<WhimsyNote>(_data.Note));
}

std::string WhimsyVariant::stringValue() const
{
    //_data.String->reference();
    return std::string(*(_data.String->_data));
}

std::vector<WhimsyVariant> WhimsyVariant::arrayValue() const
{
    //_data.VariantArray->reference();
    return std::vector<WhimsyVariant>(*(_data.VariantArray->_data));
}

bool WhimsyVariant::isUsingExtraMemory() const
{
    if(_data_type == VariantType::String ||
            _data_type == VariantType::VariantArray ||
            _data_type == VariantType::GenericPointer)
        return true;
    else
        return false;
}

std::string WhimsyVariant::toString() const
{
    std::ostringstream retval;
    std::vector<WhimsyVariant>::iterator it;
    std::vector<WhimsyVariant>::iterator almost_end;

    switch(_data_type)
    {
        case VariantType::Null:
            retval <<   "-";
        break;
        case VariantType::Bool:
            retval <<   (_data.Bool ? "true" : "false");
        break;
        case VariantType::Integer:
            retval <<   _data.Integer;
        break;
        case VariantType::Long:
            retval <<   _data.Long;
        break;
        case VariantType::Float:
            retval <<   _data.Float;
        break;
        case VariantType::Double:
            retval <<   _data.Double;
        break;
        case VariantType::Note:
            retval <<   _data.Note.toString();
        break;
        case VariantType::String:
            retval <<   *(_data.String->_data);
        break;
        case VariantType::VariantArray:
            almost_end = _data.VariantArray->_data->end() - 1;

            retval << "[";
            for(it = _data.VariantArray->_data->begin(); it != _data.VariantArray->_data->end(); it++)
                retval <<   it->toString() << ((it != almost_end) ? ", " : "");

            retval << "]";
        break;
        default:
            retval << "unknown";
    }
    return retval.str();
}

/**
 * @brief Destructor. Frees memory if this is a pointer.
 */
WhimsyVariant::~WhimsyVariant()
{
    if(isUsingExtraMemory())
        _data.GenericPointer->dereference();
}

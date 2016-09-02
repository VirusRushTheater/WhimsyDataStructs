#include "whimsyvariant.h"

#include <sstream>
#include <iomanip>

using namespace whimsycore;

const Variant Variant::null = Variant();

/**
 * @brief Empty constructor. Initializes this variant as a null pointer.
 */
Variant::Variant()
{
    _data_type =            Type::Null;
    _data.Integer =         0;
}

/**
 * @brief Copy constructor. Doesn't deep copy memory items if in memory, but passes a reference to it.
 * @param wref      Initializing value.
 */
Variant::Variant(const Variant& wref) :
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
Variant::Variant(bool _bool)
{
    _data_type =            Type::Bool;
    _data.Bool =            _bool;
}

/**
 * @brief Int constructor. Makes this variant take the value of an integer.
 * @param _bool_t   Initializing value.
 */
Variant::Variant(int _int)
{
    _data_type =            Type::Integer;
    _data.Integer =         _int;
}

Variant::Variant(long long _long)
{
    _data_type =            Type::Long;
    _data.Long =            _long;
}

/**
 * @brief Float constructor. Makes this variant take the value of a float.
 * @param _float    Initializing value.
 */
Variant::Variant(float _float)
{
    _data_type =            Type::Float;
    _data.Float =           _float;
}

/**
 * @brief Double constructor. Makes this variant take the value of a double.
 * @param _double    Initializing value.
 */
Variant::Variant(double _double)
{
    _data_type =            Type::Double;
    _data.Double =          _double;
}

/**
 * @brief Note constructor. Makes this variant take the value of a note.
 * @param _note     Initializing value.
 */
Variant::Variant(whimsycore::Note _note)
{
    _data_type =            Type::Note;
    _data.Note =            _note;
}

/**
 * @brief String constructor. Makes this variant take the value of a string.
 * @param _cstr     Initializing value.
 */
Variant::Variant(const char *_cstr)
{
    _data_type =            Type::String;
    _data.String =          new VDPointer<std::string>(std::string(_cstr));
    //_data.String =          new std::string(_cstr);
}

/**
 * @brief String constructor. Makes this variant take the value of a string.
 * @param _cstr     Initializing value.
 */
Variant::Variant(std::string _cstr)
{
    _data_type =            Type::String;
    _data.String =          new VDPointer<std::string>(std::string(_cstr));
    //_data.String =          new std::string(_cstr);
}

/**
 * @brief Array constructor. Makes this variant take the value of a dynamic array.
 * @param _array    Initializing value.
 */
Variant::Variant(std::vector<Variant> _array)
{
    _data_type =            Type::VariantArray;
    _data.VariantArray =    new VDPointer<std::vector<Variant>>(_array);
    //_data.VariantArray =    new std::vector<WhimsyVariant>(_array);
}

/**
 * @brief Assignment operator. Doesn't deep copy memory items if in memory, but passes a reference to it.
 * @param wref
 * @return
 */
Variant& Variant::operator=(const Variant& wref)
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
const char* Variant::type() const
{
    return typeToString(_data_type);
}

/**
 * @brief Returns the Type ID of this Variant.
 * @return
 */
Variant::Type Variant::typeID() const
{
    return _data_type;
}

const char* Variant::typeToString(Variant::Type t)
{
    switch(t)
    {
        case Type::Null:
            return "null";
        case Type::Bool:
            return "bool";
        case Type::Nibble:
            return "nibble";
        case Type::Byte:
            return "byte";
        case Type::Word:
            return "word";
        case Type::Integer:
            return "int";
        case Type::Float:
            return "float";
        case Type::Double:
            return "double";
        case Type::Long:
            return "long";
        case Type::Note:
            return "note";
        case Type::String:
            return "string";
        case Type::VariantArray:
            return "array";
        case Type::GenericPointer:
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
bool Variant::isNull() const
{
    return (_data_type == Type::Null);
}

Variant& Variant::convert(Variant::Type t)
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

bool Variant::boolValue() const
{
    return _data.Bool;
}

unsigned char Variant::nibbleValue() const
{
    return _data.Byte & 15;
}

unsigned char Variant::byteValue() const
{
    return _data.Byte;
}

unsigned short int Variant::wordValue() const
{
    return _data.Word;
}

int Variant::intValue() const
{
    return _data.Integer;
}

long long Variant::longValue() const
{
    return _data.Long;
}

float Variant::floatValue() const
{
    return _data.Float;
}

double Variant::doubleValue() const
{
    return _data.Double;
}

whimsycore::Note Variant::noteValue() const
{
    return whimsycore::Note(static_cast<whimsycore::Note>(_data.Note));
}

std::string Variant::stringValue() const
{
    //_data.String->reference();
    return std::string(*(_data.String->_data));
}

std::vector<Variant> Variant::arrayValue() const
{
    //_data.VariantArray->reference();
    return std::vector<Variant>(*(_data.VariantArray->_data));
}

bool Variant::isUsingExtraMemory() const
{
    return typeUsesExtraMemory(_data_type);
}

std::string Variant::toString() const
{
    std::ostringstream retval;
    std::vector<Variant>::iterator it;
    std::vector<Variant>::iterator almost_end;

    switch(_data_type)
    {
        case Type::Null:
            retval <<   "-";
        break;
        case Type::Bool:
            retval <<   (_data.Bool ? "true" : "false");
        break;
        case Type::Nibble:
        case Type::Byte:
        case Type::Word:
        case Type::Integer:
            retval <<   _data.Integer;
        break;
        case Type::Long:
            retval <<   _data.Long;
        break;
        case Type::Float:
            retval <<   _data.Float;
        break;
        case Type::Double:
            retval <<   _data.Double;
        break;
        case Type::Note:
            retval <<   _data.Note.toString();
        break;
        case Type::String:
            retval <<   *(_data.String->_data);
        break;
        case Type::VariantArray:
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

std::string Variant::toString(OutputStringFormat ot) const
{
    std::ostringstream retval;
    std::vector<Variant>::iterator it;
    std::vector<Variant>::iterator almost_end;

    if(ot == Format_Normal)
        return toString();
    else if(ot == Format_Hex)
    {
        switch(_data_type)
        {
            // Null, Note and String -> No changes.
            case Type::Null:
            case Type::Note:
            case Type::String:
                return toString();

            // Floating types have now 4 precision points.
            case Type::Float:
                retval.precision(4);
                retval << _data.Float;
            break;
            case Type::Double:
                retval.precision(4);
                retval << _data.Double;
            break;

            // Integer types are converted to hex and padded as necessary.
            case Type::Bool:
                retval <<   (_data.Bool ? "1" : "0");
            break;
            case Type::Nibble:
                retval << std::hex << (_data.Byte & 15);
            break;
            case Type::Byte:
                retval << std::setfill('0') << std::setw(2) << std::hex << _data.Byte;
            break;
            case Type::Word:
                retval << std::setfill('0') << std::setw(4) << std::hex << _data.Word;
            break;
            case Type::Integer:
                retval << std::setfill('0') << std::setw(8) << std::hex << _data.Integer;
            break;
            case Type::Long:
                retval << std::setfill('0') << std::setw(16) << std::hex << _data.Long;
            break;

            // Array recurses this function into each element.
            case Type::VariantArray:
                almost_end = _data.VariantArray->_data->end() - 1;

                retval << "[";
                for(it = _data.VariantArray->_data->begin(); it != _data.VariantArray->_data->end(); it++)
                    retval <<   it->toString(ot) << ((it != almost_end) ? ", " : "");

                retval << "]";
            break;
            default:
                retval << "unknown";
        }
    }
    return retval.str();
}

static bool Variant::typeUsesExtraMemory(Type t)
{
    if(t == Type::String ||
            t == Type::VariantArray ||
            t == Type::GenericPointer)
        return true;
    else
        return false;
}

static bool Variant::typeIsNumeric(Type t)
{
    return (typeIsInteger(t) || typeIsFloatingPoint(t));
}

static bool Variant::typeIsInteger(Type t)
{
    if(t == Type::Bool ||
            t == Type::Nibble ||
            t == Type::Byte ||
            t == Type::Word ||
            t == Type::Integer ||
            t == Type::Long)
        return true;
    else
        return false;
}

static bool Variant::typeIsFloatingPoint(Type t)
{
    if(t == Type::Float ||
            t == Type::Double)
        return true;
    else
        return false;
}

/**
 * @brief Destructor. Frees memory if this is a pointer.
 */
Variant::~Variant()
{
    if(isUsingExtraMemory())
        _data.GenericPointer->dereference();
}

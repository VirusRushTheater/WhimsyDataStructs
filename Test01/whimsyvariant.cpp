#include "whimsyvariant.h"
#include "whimsyexception.h"

#include <sstream>
#include <iomanip>

#define WHIMSYVARIANT_CLEAR       _data_type = Null; _data._Long = 0ll;

using namespace whimsycore;

const Variant Variant::null = Variant();

/**
 * @brief Empty constructor. Initializes this variant as a null pointer.
 */
Variant::Variant()
{
    _data_type =            Type::Null;
    _data._Integer =         0;
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
        _data._Pointer->reference();
}

/**
 * @brief Boolean constructor. Makes this variant take the value of a boolean.
 * @param _bool_t   Initializing value.
 */
Variant::Variant(bool _bool)
{
    _data_type =            Type::Bool;
    _data._Bool =            _bool;
}

/**
 * @brief Int constructor. Makes this variant take the value of an integer.
 * @param _bool_t   Initializing value.
 */
Variant::Variant(int _int)
{
    _data_type =            Type::Integer;
    _data._Integer =         _int;
}

Variant::Variant(long long _long)
{
    _data_type =            Type::Long;
    _data._Long =            _long;
}

/**
 * @brief Float constructor. Makes this variant take the value of a float.
 * @param _float    Initializing value.
 */
Variant::Variant(float _float)
{
    _data_type =            Type::Float;
    _data._Float =           _float;
}

/**
 * @brief Double constructor. Makes this variant take the value of a double.
 * @param _double    Initializing value.
 */
Variant::Variant(double _double)
{
    _data_type =            Type::Double;
    _data._Double =          _double;
}

/**
 * @brief Note constructor. Makes this variant take the value of a note.
 * @param _note     Initializing value.
 */
Variant::Variant(whimsycore::Note _note)
{
    _data_type =            Type::Note;
    _data._Note =            _note;
    noteFix();
}

/**
 * @brief String constructor. Makes this variant take the value of a string.
 * @param _cstr     Initializing value.
 */
Variant::Variant(const char *_cstr)
{
    _data_type =            Type::String;
    _data._String =          new VDPointer<std::string>(std::string(_cstr));
    //_data.String =          new std::string(_cstr);
}

/**
 * @brief String constructor. Makes this variant take the value of a string.
 * @param _cstr     Initializing value.
 */
Variant::Variant(std::string _cstr)
{
    _data_type =            Type::String;
    _data._String =          new VDPointer<std::string>(std::string(_cstr));
    //_data.String =          new std::string(_cstr);
}

/**
 * @brief Array constructor. Makes this variant take the value of a dynamic array.
 * @param _array    Initializing value.
 */
Variant::Variant(std::vector<Variant> _array)
{
    _data_type =            Type::VariantArray;
    _data._VariantArray =    new VDPointer<std::vector<Variant> >(_array);
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
        _data._Pointer->dereference();

    _data_type = wref._data_type;
    _data = wref._data;

    if(wref.isUsingExtraMemory())
        _data._Pointer->reference();

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

#if WHIMSYVARIANT_ENABLE_TYPE_CASTING == 1
template<typename T> T Variant::value() const
{
    throw Exception(this, Exception::InvalidConversion, "Cannot cast to this type.");
    return T();
}

namespace whimsycore
{
template<> bool Variant::value<bool>() const
{
    return boolValue();
}

template<> unsigned char Variant::value<unsigned char>() const
{
    return byteValue();
}

template<> unsigned short int Variant::value<unsigned short int>() const
{
    return wordValue();
}

template<> int Variant::value<int>() const
{
    return intValue();
}

template<> long long int Variant::value<long long int>() const
{
    return longValue();
}

template<> float Variant::value<float>() const
{
    return floatValue();
}

template<> double Variant::value<double>() const
{
    return doubleValue();
}

template<> whimsycore::Note Variant::value<whimsycore::Note>() const
{
    return noteValue();
}

template<> std::string Variant::value<std::string>() const
{
    return stringValue();
}

template<> std::vector<Variant> Variant::value<std::vector<Variant> >() const
{
    return arrayValue();
}
}
#endif

bool Variant::boolValue() const
{
    if(_data_type == Bool)
        return _data._Bool;

    switch(_data_type)
    {
        case Null:
            return false;
        case Bool:
        case Nibble:
        case Byte:
            return (_data._Byte != 0);
        case Word:
            return (_data._Word != 0);
        case Integer:
            return (_data._Integer != 0);
        case Long:
            return (_data._Long != 0);
        case Float:
            return (_data._Float != 0);
        case Double:
            return (_data._Double != 0);
        case Note:
            return (_data._Note.toInt() < 128);
        case String:
            return (strcasecmp(_data._String->_data->c_str(), "true") == 0 ||
                    strcmp(_data._String->_data->c_str(), "1") == 0);
        case VariantArray:
            if(_data._VariantArray->_data->size() < 1)
            {
                throw Exception(this, Exception::InvalidConversion, "Variant currently an empty array. Can't convert to Bool.");
                return false;
            }
            return _data._VariantArray->_data->at(0).boolValue();
        default:
            throw Exception(this, Exception::InvalidConversion, "Unknown conversion to Bool.");
            return false;
    }
}

unsigned char Variant::nibbleValue() const
{
    if(_data_type == Nibble)
        return _data._Byte;

    switch(_data_type)
    {
        case Null:
            return 0;
        case Bool:
            return (_data._Bool) ? 1 : 0;
        case Nibble:
        case Byte:
            return (_data._Byte & 15);
        case Word:
            return static_cast<unsigned char>((_data._Word < 16) ? _data._Word : 15);
        case Integer:
            return static_cast<unsigned char>((_data._Integer < 16) ? ((_data._Integer >= 0) ? _data._Integer : 0) : 15);
        case Long:
            return static_cast<unsigned char>((_data._Long < 16) ? ((_data._Long >= 0) ? _data._Long : 0) : 15);
        case Float:
            return static_cast<unsigned char>((_data._Float < 16) ? ((_data._Float >= 0) ? _data._Float : 0) : 15);
        case Double:
            return static_cast<unsigned char>((_data._Double < 16) ? ((_data._Double >= 0) ? _data._Double : 0) : 15);
        case Note:
            return static_cast<unsigned char>((_data._Note.toInt() - 128) % 12);
        case String:
            return Variant((int) strtol(_data._String->_data->c_str(), NULL, 10)).nibbleValue();
        case VariantArray:
            if(_data._VariantArray->_data->size() < 1)
            {
                throw Exception(this, Exception::InvalidConversion, "Variant currently an empty array. Can't convert to Nibble.");
                return 0;
            }
            return _data._VariantArray->_data->at(0).nibbleValue();
        default:
            throw Exception(this, Exception::InvalidConversion, "Unknown conversion to Nibble.");
            return 0;
    }
}

unsigned char Variant::byteValue() const
{
    if(_data_type == Byte || _data_type == Nibble)
        return _data._Byte;

    switch(_data_type)
    {
        case Null:
            return 0;
        case Bool:
            return (_data._Bool) ? 1 : 0;
        case Nibble:
        case Byte:
        case Word:
            return static_cast<unsigned char>(_data._Word);
        case Integer:
            return static_cast<unsigned char>(_data._Integer);
        case Long:
            return static_cast<unsigned char>(_data._Long);
        case Float:
            return static_cast<unsigned char>(_data._Float);
        case Double:
            return static_cast<unsigned char>(_data._Double);
        case Note:
            return _data._Note.value();
        case String:
            return static_cast<unsigned char>(strtol(_data._String->_data->c_str(), NULL, 10));
        case VariantArray:
            if(_data._VariantArray->_data->size() < 1)
            {
                throw Exception(this, Exception::InvalidConversion, "Variant currently an empty array. Can't convert to Byte.");
                return 0;
            }
            return _data._VariantArray->_data->at(0).byteValue();
        default:
            throw Exception(this, Exception::InvalidConversion, "Unknown conversion to Byte.");
            return 0;
    }
}

unsigned short int Variant::wordValue() const
{
    if(_data_type == Word)
        return _data._Word;

    switch(_data_type)
    {
        case Null:
            return 0;
        case Bool:
            return (_data._Bool) ? 1 : 0;
        case Nibble:
        case Byte:
            return static_cast<unsigned short int>(_data._Byte);
        case Word:
        case Integer:
            return static_cast<unsigned short int>(_data._Integer);
        case Long:
            return static_cast<unsigned short int>(_data._Long);
        case Float:
            return static_cast<unsigned short int>(_data._Float);
        case Double:
            return static_cast<unsigned short int>(_data._Double);
        case Note:
            return _data._Note.value();
        case String:
            return static_cast<unsigned short int>(strtol(_data._String->_data->c_str(), NULL, 10));
        case VariantArray:
            if(_data._VariantArray->_data->size() < 1)
                throw Exception(this, Exception::InvalidConversion, "Variant currently an empty array. Can't convert to Word.");
            return _data._VariantArray->_data->at(0).wordValue();
        default:
            throw Exception(this, Exception::InvalidConversion, "Unknown conversion to Word.");
            return 0;
    }
}

int Variant::intValue() const
{
    if(_data_type == Integer)
        return _data._Integer;

    switch(_data_type)
    {
        case Null:
            return 0;
        case Bool:
            return (_data._Bool) ? 1 : 0;
        case Nibble:
        case Byte:
            return static_cast<int>(_data._Byte);
        case Word:
            return static_cast<int>(_data._Word);
        case Integer:
        case Long:
            return static_cast<int>(_data._Long);
        case Float:
            return static_cast<int>(_data._Float);
        case Double:
            return static_cast<int>(_data._Double);
        case Note:
            return _data._Note.value();
        case String:
            return static_cast<int>(strtol(_data._String->_data->c_str(), NULL, 10));
        case VariantArray:
            if(_data._VariantArray->_data->size() < 1)
                throw Exception(this, Exception::InvalidConversion, "Variant currently an empty array. Can't convert to Integer.");
            return _data._VariantArray->_data->at(0).intValue();
        default:
            throw Exception(this, Exception::InvalidConversion, "Unknown conversion to Integer.");
            return 0;
    }
}

long long int Variant::longValue() const
{
    if(_data_type == Long)
        return _data._Long;

    switch(_data_type)
    {
        case Null:
            return 0;
        case Bool:
            return (_data._Bool) ? 1 : 0;
        case Nibble:
        case Byte:
            return static_cast<long long int>(_data._Byte);
        case Word:
            return static_cast<long long int>(_data._Word);
        case Integer:
            return static_cast<long long int>(_data._Integer);
        case Long:
        case Float:
            return static_cast<long long int>(_data._Float);
        case Double:
            return static_cast<long long int>(_data._Double);
        case Note:
            return _data._Note.value();
        case String:
            return strtoll(_data._String->_data->c_str(), NULL, 10);
        case VariantArray:
            if(_data._VariantArray->_data->size() < 1)
                throw Exception(this, Exception::InvalidConversion, "Variant currently an empty array. Can't convert to Long.");
            return _data._VariantArray->_data->at(0).longValue();
        default:
            throw Exception(this, Exception::InvalidConversion, "Unknown conversion to Long.");
            return 0;
    }
}

float Variant::floatValue() const
{
    if(_data_type == Float)
        return _data._Float;

    switch(_data_type)
    {
        case Null:
            return 0;
        case Bool:
            return (_data._Bool) ? 1 : 0;
        case Nibble:
        case Byte:
            return static_cast<float>(_data._Byte);
        case Word:
            return static_cast<float>(_data._Word);
        case Integer:
            return static_cast<float>(_data._Integer);
        case Long:
            return static_cast<float>(_data._Long);
        case Float:
        case Double:
            return static_cast<float>(_data._Double);
        case Note:
            return _data._Note.value();
        case String:
            return strtof(_data._String->_data->c_str(), NULL);
        case VariantArray:
            if(_data._VariantArray->_data->size() < 1)
                throw Exception(this, Exception::InvalidConversion, "Variant currently an empty array. Can't convert to Float.");
            return _data._VariantArray->_data->at(0).floatValue();
        default:
            throw Exception(this, Exception::InvalidConversion, "Unknown conversion to Float.");
            return 0;
    }
}

double Variant::doubleValue() const
{
    if(_data_type == Double)
        return _data._Double;

    switch(_data_type)
    {
        case Null:
            return 0;
        case Bool:
            return (_data._Bool) ? 1 : 0;
        case Nibble:
        case Byte:
            return static_cast<double>(_data._Byte);
        case Word:
            return static_cast<double>(_data._Word);
        case Integer:
            return static_cast<double>(_data._Integer);
        case Long:
            return static_cast<double>(_data._Long);
        case Float:
            return static_cast<double>(_data._Float);
        case Double:
        case Note:
            return _data._Note.value();
        case String:
            return strtod(_data._String->_data->c_str(), NULL);
        case VariantArray:
            if(_data._VariantArray->_data->size() < 1)
                throw Exception(this, Exception::InvalidConversion, "Variant currently an empty array. Can't convert to Double.");
            return _data._VariantArray->_data->at(0).doubleValue();
        default:
            throw Exception(this, Exception::InvalidConversion, "Unknown conversion to Double.");
            return 0;
    }
}

whimsycore::Note Variant::noteValue() const
{
    if(_data_type == Note)
        return whimsycore::Note(_data._Note);
    else if(_data_type == String)
        return whimsycore::Note(*(_data._String->_data));
    else
        return whimsycore::Note(byteValue());
}

std::string Variant::stringValue() const
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
            retval <<   (_data._Bool ? "true" : "false");
        break;
        case Type::Nibble:
        case Type::Byte:
        case Type::Word:
        case Type::Integer:
            retval <<   _data._Integer;
        break;
        case Type::Long:
            retval <<   _data._Long;
        break;
        case Type::Float:
            retval <<   _data._Float;
        break;
        case Type::Double:
            retval <<   _data._Double;
        break;
        case Type::Note:
            retval <<   _data._Note.toString();
        break;
        case Type::String:
            retval <<   *(_data._String->_data);
        break;
        case Type::VariantArray:
            almost_end = _data._VariantArray->_data->end() - 1;

            retval << "[";
            for(it = _data._VariantArray->_data->begin(); it != _data._VariantArray->_data->end(); it++)
                retval <<   it->toString() << ((it != almost_end) ? ", " : "");

            retval << "]";
        break;
        default:
            retval << "unknown";
    }

    return retval.str();
}

std::vector<Variant> Variant::arrayValue() const
{
    std::vector<Variant> retval;
    if(_data_type == VariantArray)
        retval = std::vector<Variant>(*(_data._VariantArray->_data));
    else
        retval.push_back(*this);

    return retval;
}

/**
 * @brief Failsafe class if it doesn't know how to convert to this type.
 */
/*
template<> T Variant::value() const
{
    throw Exception(this, Exception::InvalidConversion, "whimsycore::Variant doesn't know how to convert to this class.");
    return T();
}
*/
bool Variant::isUsingExtraMemory() const
{
    return typeUsesExtraMemory(_data_type);
}

std::string Variant::toString() const
{
    return stringValue();
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
                retval << _data._Float;
            break;
            case Type::Double:
                retval.precision(4);
                retval << _data._Double;
            break;

            // Integer types are converted to hex and padded as necessary.
            case Type::Bool:
                retval <<   (_data._Bool ? "1" : "0");
            break;
            case Type::Nibble:
                retval << std::hex << (int)(_data._Byte & 15);
            break;
            case Type::Byte:
                retval << std::setfill('0') << std::setw(2) << std::hex << (int)_data._Byte;
            break;
            case Type::Word:
                retval << std::setfill('0') << std::setw(4) << std::hex << _data._Word;
            break;
            case Type::Integer:
                retval << std::setfill('0') << std::setw(8) << std::hex << _data._Integer;
            break;
            case Type::Long:
                retval << std::setfill('0') << std::setw(16) << std::hex << _data._Long;
            break;

            // Array recurses this function into each element.
            case Type::VariantArray:
                almost_end = _data._VariantArray->_data->end() - 1;

                retval << "[";
                for(it = _data._VariantArray->_data->begin(); it != _data._VariantArray->_data->end(); it++)
                    retval <<   it->toString(ot) << ((it != almost_end) ? ", " : "");

                retval << "]";
            break;
            default:
                retval << "unknown";
        }
    }
    return retval.str();
}

bool Variant::typeUsesExtraMemory(Variant::Type t)
{
    if(t == Type::String ||
            t == Type::VariantArray ||
            t == Type::GenericPointer)
        return true;
    else
        return false;
}

bool Variant::typeIsNumeric(Variant::Type t)
{
    return (typeIsInteger(t) || typeIsFloatingPoint(t));
}

bool Variant::typeIsInteger(Variant::Type t)
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

bool Variant::typeIsFloatingPoint(Variant::Type t)
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
        _data._Pointer->dereference();
}


Variant& Variant::convert(Variant::Type t)
{
    Variant             rval;

    // Dismiss if no conversion.
    if(t == _data_type || _data_type == Null)
        return *this;

    // Any type -> Null type = Nullify (and remove extra memory if necessary)
    if(t == Null)
    {
        _data_type = Null;
    }

    // Any type -> Generic Pointer = What.
    if(t == GenericPointer)
    {
        throw Exception(this, Exception::InvalidConversion, "GenericPointer isn't meant to be a valid type.");
    }

    switch(t)
    {
        case Null:      break;
        case Bool:      rval = boolValue();     break;
        case Nibble:    rval = nibbleValue();   break;
        case Byte:      rval = byteValue();     break;
        case Word:      rval = wordValue();     break;
        case Integer:   rval = intValue();      break;
        case Long:      rval = longValue();     break;
        case Float:     rval = floatValue();    break;
        case Double:    rval = doubleValue();   break;
        case Note:      rval = noteValue();     break;
        case String:    rval = stringValue();   break;
        case VariantArray:  rval = arrayValue();    break;
    default: break;
    }

    /*
    if(isUsingExtraMemory())
        _data._Pointer->dereference();
        */
    *this =         rval;
    if(rval._data_type != Null)
        _data_type =    t;

    return *this;
}

void Variant::noteFix()
{
    if(_data_type == Note)
    {
        if(_data._Note.isNull())
        {
            WHIMSYVARIANT_CLEAR
        }
    }
}

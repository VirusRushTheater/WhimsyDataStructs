#include "whimsyexception.h"

using namespace whimsycore;

Exception::Exception(const char* info) :
    _identifiable(false),
    _cause(NULL),
    _xctype(Unknown),
    _additional_info(info)
{
    if(strlen(_additional_info) > 0)
        _uses_additional_info = true;
    else
        _uses_additional_info = false;
}

Exception::Exception(const Base* objref, ExceptionType reasons, const char* info) :
    _identifiable(true),
    _cause(objref),
    _xctype(reasons),
    _additional_info(info)
{
    if(objref == NULL)
        _identifiable = false;

    if(strlen(_additional_info) > 0)
        _uses_additional_info = true;
    else
        _uses_additional_info = false;
}

std::string Exception::toString() const
{
    std::ostringstream retval;
    if(_identifiable)
    {
        retval << "[A Whimsy Object @ 0x" << std::hex << reinterpret_cast<long long int>(_cause) << "] ";
        retval << exceptionTypeToString(_xctype);
    }
    else
    {
        retval << "[Exception] ";
        retval << exceptionTypeToString(_xctype);
        //retval << "Cause unknown";
    }

    if(_uses_additional_info)
        retval << " - " << _additional_info;

    return retval.str().c_str();
}

const char* Exception::what() const throw()
{
    return toString().c_str();
}

const char* Exception::exceptionTypeToString(ExceptionType t)
{
    switch(t)
    {
        case Unknown:
            return "Unknown";
        case TestPurposes:
            return "Testing exception";
        case ArrayOutOfBounds:
            return "Array out of bounds";
        case InvalidConversion:
            return "Invalid conversion";
        case NameConflict:
            return "Name conflict";
        case NotFound:
            return "Not found";
        default:
            return "Not specified";
    }
}

Exception::ExceptionType Exception::exceptionTypeID() const
{
    return _xctype;
}

const char* Exception::exceptionType() const
{
    return exceptionTypeToString(exceptionTypeID());
}

const char* Exception::additionalInfo() const
{
    return _additional_info;
}

#include "whimsyexception.h"

WhimsyException::WhimsyException(const char* info) :
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

WhimsyException::WhimsyException(WhimsyBase* objref, ExceptionType reasons, const char* info) :
    _identifiable(true),
    _cause(objref),
    _xctype(reasons),
    _additional_info(info)
{
    if(strlen(_additional_info) > 0)
        _uses_additional_info = true;
    else
        _uses_additional_info = false;
}

std::string WhimsyException::toString() const
{
    std::ostringstream retval;
    if(_identifiable)
    {
        retval << "[" << _cause->className() << " @ 0x" << std::hex << reinterpret_cast<long long int>(_cause) << "] ";
        retval << exceptionTypeToString(_xctype);
    }
    else
    {
        retval << "Cause unknown";
    }

    if(_uses_additional_info)
        retval << " - " << _additional_info;

    return retval.str().c_str();
}

const char* WhimsyException::what() const throw()
{
    return toString().c_str();
}

const char* WhimsyException::exceptionTypeToString(ExceptionType t)
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
        default:
            return "Not specified";
    }
}

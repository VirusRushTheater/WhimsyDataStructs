#pragma once

#include "whimsybase.h"

#include <sstream>
#include <string>
#include <exception>
#include <cstring>

namespace whimsycore
{
class Exception : public std::exception, public Base
{   
public:
    enum ExceptionType
    {
        Unknown,
        TestPurposes,
        ArrayOutOfBounds,
        InvalidConversion,
        NameConflict,
        NotFound
    };

private:
    bool            _identifiable;
    Base*     _cause;
    ExceptionType   _xctype;

    bool            _uses_additional_info;
    const char*     _additional_info;

public:
    WHIMSY_OBJECT_NAME("WhimsyException")
    Exception(const char* info = "");
    Exception(Base* objref, ExceptionType reasons = ExceptionType::Unknown, const char* info = "");

    std::string toString() const;

    Base* cause() const;
    ExceptionType reasons() const;

    virtual const char* what() const throw();

    static const char* exceptionTypeToString(ExceptionType t);
};
}

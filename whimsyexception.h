#ifndef WHIMSYEXCEPTION_H
#define WHIMSYEXCEPTION_H

#include "whimsybase.h"

#include <sstream>
#include <string>
#include <exception>
#include <cstring>

class WhimsyException : public std::exception, public WhimsyBase
{   
public:
    enum ExceptionType
    {
        Unknown,
        TestPurposes,
        ArrayOutOfBounds,
        InvalidConversion
    };

private:
    bool            _identifiable;
    WhimsyBase*     _cause;
    ExceptionType   _xctype;

    bool            _uses_additional_info;
    const char*     _additional_info;

public:
    WHIMSY_OBJECT_NAME("WhimsyException")
    WhimsyException(const char* info = "");
    WhimsyException(WhimsyBase* objref, ExceptionType reasons = ExceptionType::Unknown, const char* info = "");

    std::string toString() const;

    WhimsyBase* cause() const;
    ExceptionType reasons() const;

    virtual const char* what() const throw();

    static const char* exceptionTypeToString(ExceptionType t);
};

#endif // WHIMSYEXCEPTION_H

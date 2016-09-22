#pragma once

#include <string>
#include <iostream>

#define WHIMSY_OBJECT_NAME(A)     const char* className() const {return A;}

typedef unsigned char       byte;

namespace whimsycore
{

struct ByteStream
{
    unsigned char*  data;
    size_t          length;
};

/**
 * @brief Base class for all whimsycore classes. Defines some common debug and convenience methods, to be inherited
 * and reimplemented in children classes.
 */
class Base
{
public:
    /**
     * @brief Returns the derived class name.
     * Use the macro WHIMSY_OBJECT_NAME inside the public: section of every child class you make.
     * @return  Name of derived class.
     */
    virtual const char* className() const = 0;

    /**
     * @brief Returns a string representation of the derived class. For debug purposes mostly.
     * @return
     */
    virtual std::string toString() const {return std::string();}

    /**
     * @brief Converts a derived data structure to a byte stream, mainly for file storing purposes.
     * @return
     */
    virtual ByteStream toStream() const {return {NULL, 0}; }

    /**
     * @brief Populates a derived data structure with raw, unformatted data from a byte array. To be used
     * at loading files.
     *
     * @param       Byte stream with data and its length.
     */
    virtual void fromStream(const ByteStream&) {}
};

class Utility
{
public:
    enum PaddingOptions
    {
        PadLeft,
        PadRight
    };

    static std::string forceWidth(std::string original, size_t newsize, char fillchar = ' ', PaddingOptions po = PadLeft);
};
}

/**
 * @brief Operator overloaded with the purpose of harnessing the STL stream functions (like std::cout or std::ostringstream)
 * @param os    Output Stream
 * @param v     Reference to a WhimsyVariant class
 * @return      Identifier to that output stream
 */
extern std::ostream& operator <<(std::ostream& os, whimsycore::Base const& v);

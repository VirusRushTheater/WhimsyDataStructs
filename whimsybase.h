#ifndef WHIMSYBASE_H
#define WHIMSYBASE_H

#include <string>
#include <iostream>

#define WHIMSY_OBJECT_NAME(A)     const char* className() const{return A;}
//#define WHIMSY_OBJECT_NAME(A)

class WhimsyBase
{
public:
    virtual const char* className() const = 0;
    virtual std::string toString() const {return std::string();}
};

/**
 * @brief Operator overloaded with the purpose of harnessing the STL stream functions (like std::cout or std::ostringstream)
 * @param os    Output Stream
 * @param v     Reference to a WhimsyVariant class
 * @return      Identifier to that output stream
 */
extern std::ostream& operator <<(std::ostream& os, WhimsyBase const& v);

#endif // WHIMSYBASE_H

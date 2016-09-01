#include <iostream>
#include "whimsybase.h"

std::ostream& operator <<(std::ostream& os, WhimsyBase const& v)
{
    os << v.toString();
    return os;
}

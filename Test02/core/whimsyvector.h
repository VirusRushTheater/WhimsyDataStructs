#pragma once

#include "whimsybase.h"
#include <vector>
#include <string>
#include <sstream>

namespace whimsycore
{

/**
 * @brief Wrapper for std::vector to manage a variadic argument constructor, and nice item adder methods.
 */
template <typename T>
class WhimsyVector : public Base, public std::vector<T>
{
public:
    WHIMSY_OBJECT_NAME("Core/WhimsyVector")

    typedef std::vector<T> typeTvector;

    template<typename ... Args>
    WhimsyVector(Args ... variadicargs)
    {
        addItems(variadicargs...);
    }

    template<typename ... Args>
    WhimsyVector<T>& addItems(const T& elem, Args ... others)
    {
        this->push_back(elem);
        return addItems(others...);
    }

    WhimsyVector<T>& addItems()
    {
        return *this;
    }

    WhimsyVector<T>& operator << (const T&& elem)
    {
        this->push_back(elem);
        return *this;
    }

    std::string toString() const
    {
        std::ostringstream              retval;
        size_t                          cit;

        retval << "[";
        for(cit = 0; cit < this->size(); cit++)
        {
            retval << this->at(cit);
            if(cit != this->size() - 1)
                retval << ", ";
        }
        retval << "]";

        return retval.str();
    }
};

}

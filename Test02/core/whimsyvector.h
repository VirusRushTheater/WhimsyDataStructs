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

    /**
     * @brief Creates an empty Vector.
     */
    WhimsyVector()
    {
    }

    /**
     * @brief Creates a vector, and adds all the supplied arguments as new elements of this vector.
     * @param firstarg  Argument to ensure this constructor is called with, at least, one element.
     * @param others    Variadic parameter list. Make sure all elements of this list are the same type of this vector.
     */
    template<typename ... Args>
    WhimsyVector(T firstarg, Args ... variadicargs)
    {
        addItems(firstarg, variadicargs...);
    }

    /**
     * @brief Adds all the supplied arguments as new elements of this vector.
     * @param elem      Argument to ensure this method is called with, at least, one element.
     * @param others    Variadic parameter list. Make sure all elements of this list are the same type of this vector.
     * @return Reference to this vector.
     */
    template<typename ... Args>
    WhimsyVector<T>& addItems(const T& elem, Args ... others)
    {
        this->push_back(elem);
        return addItems(others...);
    }

    /**
     * @brief End for the addItems recursive algorithm. Does not do anything.
     * @return  Reference to this vector.
     */
    WhimsyVector<T>& addItems()
    {
        return *this;
    }

    /**
     * @brief Enables using the << operator to add elements to the vector. Equivalent to push_back().
     * @param elem  New element for this vector.
     * @return      Reference to this vector.
     */
    WhimsyVector<T>& operator << (const T&& elem)
    {
        this->push_back(elem);
        return *this;
    }

    /**
     * @brief Outputs a Python-like representation of this vector.
     * @return String representation of this vector.
     */
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

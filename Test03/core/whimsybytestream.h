#pragma once

#include <cstring>
#include "whimsyvector.h"
#include "whimsyexception.h"

namespace whimsycore
{

class ByteStream : public WhimsyVector<byte>
{
private:
    size_t cursor;

public:
    /**
     * @brief Creates a vector, and adds all the supplied arguments as new elements of this vector.
     * @param firstarg  Argument to ensure this constructor is called with, at least, one element.
     * @param others    Variadic parameter list. Make sure all elements of this list are the same type of this vector.
     */
    template<typename ... Args>
    ByteStream(Args ... variadicargs) : cursor(0)
    {
        this->addItems(variadicargs...);
    }

    /**
     * @brief Overloaded method to add items. Adds all the characters in the string (trailing zero not included)
     * @param cstring   C Styled string.
     * @param others    Variadic parameter list. Make sure all elements of this list are the same type of this vector.
     * @return Reference to this vector.
     */
    template<typename ... Args>
    ByteStream& addItems(const char* cstring, Args ... others)
    {
        this->insert(this->end(), cstring, cstring + std::strlen(cstring));
        return addItems(others...);
    }

    /**
     * @brief Overloaded method to add items.
     * @param elem      Byte element.
     * @param others    Variadic parameter list. Make sure all elements of this list are the same type of this vector.
     * @return Reference to this vector.
     */
    template<typename ... Args>
    ByteStream& addItems(byte elem, Args ... others)
    {
        this->push_back(elem);
        return addItems(others...);
    }

    /**
     * @brief End for the addItems recursive algorithm. Does not do anything.
     * @return  Reference to this vector.
     */
    ByteStream& addItems()
    {
        return *this;
    }

    /**
     * @brief Rewinds the cursor. See operator>>.
     */
    void rewind();

    /**
     * @brief Sets the reader cursor position. See operator>>.
     * @param pos       New position of the cursor.
     */
    void seekSet(size_t pos);

    /**
     * @brief Pushes the reader cursor position forwards. See operator>>.
     * @param pos       How many bytes will the cursor be pushed forward.
     */
    void seekCur(size_t pos);

    /**
     * @brief Tells which is the cursor's position.
     * @return
     */
    size_t tell() const;

    /**
     * @brief Copies a portion of the ByteStream's data into `dest`. The cursor is automatically adjusted for consecutive calls.
     * @param pos       A reference to a variable which will hold the data.
     */
    template<typename T>
    ByteStream& operator >> (T& dest)
    {
        if(cursor + sizeof(T) >= this->size())
            throw Exception(this, Exception::ArrayOutOfBounds, "Operator >> out of bounds.");

        std::memcpy(&dest, &(this->at(cursor)), sizeof(T));
        cursor += sizeof(T);

        return *this;
    }

    /**
     * @brief Copies a file data into this ByteStream.
     * @param filepath      Path of the file you want to read.
     * @return              Amount of bytes read.
     */
    size_t read(const char* filepath);

    /**
     * @brief Dumps this ByteStream data into a file.
     * @param filepath      Path of the file you want to write to.
     * @return              Amount of bytes written.
     */
    size_t write(const char* filepath);
};

}

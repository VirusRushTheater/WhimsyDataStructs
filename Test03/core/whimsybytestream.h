#pragma once

#include <cstring>
#include "whimsyvector.h"
#include "whimsyexception.h"

// In the case your processor is a big-endian one, change this "define" to 1.
#define PROCESSOR_IS_BIG_ENDIAN     0

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
     * @brief Adds a 32-bit int as 4 new elements in Little Endian fashion (LSB first, MSB last)
     * NOTE: IF YOUR PROCESSOR IS BIG ENDIAN, SET `PROCESSOR_IS_BIG_ENDIAN` MACRO TO 1!
     * @param number    32-bit integer.
     * @return          Reference to this vector.
     */
#if PROCESSOR_IS_BIG_ENDIAN == 0
    ByteStream& addInt(int32_t number)
    {
        this->insert(this->end(), (unsigned char*)&number, &(((unsigned char*)&number)[4]));
        return *this;
    }
#else
    ByteStream& addInt(int32_t number)
    {
        byte output[4];
        output[0] = number;         // MSB
        output[1] = number >> 8;
        output[2] = number >> 16;
        output[3] = number >> 24;   // LSB

        this->insert(this->end(), &(output[0]), &(output[3]));

        return *this;
    }
#endif

    /**
     * @brief Adds a (up to) 28-bit MIDI-fashioned Variable length number into this vector.
     * MIDI Variable length: Each byte stores 7 bits plus a flag. If this flag is 1, this number is bigger and continues at the next byte, recursively, until it finds a 0 flag byte.
     * The flag corresponds to the highest value bit in the byte (0x80).
     *
     * @param number    28-bit integer.
     * @return          Reference to this vector.
     */
    ByteStream& addMidiVarLen(uint32_t number)
    {
        if(number >> 21)
            this->push_back(0x80 | ((number >> 21) & 0x7F));

        if(number >> 14)
            this->push_back(0x80 | ((number >> 14) & 0x7F));

        if(number >> 7)
            this->push_back(0x80 | ((number >> 7) & 0x7F));

        this->push_back(number & 0x7F);

        return *this;
    }

    /**
     * @brief Gets a (up to) 28-bit MIDI-fashioned Variable length number from this vector.
     * MIDI Variable length: Each byte stores 7 bits plus a flag. If this flag is 1, this number is bigger and continues at the next byte, recursively, until it finds a 0 flag byte.
     * The flag corresponds to the highest value bit in the byte (0x80).
     *
     * @param number    Integer where the number will be stored.
     * @return          Reference to this vector.
     */
    ByteStream& getMidiVarLen(int& number)
    {
        number = 0;

        byte byteskip;
        bool continueflag;

        for(byteskip = 0; byteskip < 28; byteskip += 7)
        {
            number |=       (this->at(cursor) & 0x7F);
            continueflag =  (this->at(cursor) & 0x80);

            if(cursor++ >= this->size())
                throw Exception(this, Exception::ArrayOutOfBounds, "getMidiVarLen went out of bounds.");

            if(!continueflag)
                break;
            else
                number <<= 7;
        }

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

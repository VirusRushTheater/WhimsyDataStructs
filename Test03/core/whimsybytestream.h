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

    ByteStream& addIntReverseEndian(int32_t number);
    ByteStream& addWordReverseEndian(uint16_t number);
    ByteStream& getIntReverseEndian(int32_t& number);
    ByteStream& getWordReverseEndian(uint16_t& number);
    template<typename T> ByteStream& addVariableReverseEndian(T variable)
    {
        byte* revert_pointer = reinterpret_cast<byte*>(&variable);
        byte swap_reserve;

        for(size_t i = 0; i < (sizeof(T) / 2); i++)
        {
            swap_reserve = revert_pointer[sizeof(T) - 1 - i];
            revert_pointer[sizeof(T) - 1 - i] = revert_pointer[i];
            revert_pointer[i] = swap_reserve;
        }

        this->insert(this->end(), (unsigned char*)&variable, &(((unsigned char*)&variable)[sizeof(T)]));

        return *this;
    }

    template<typename T> ByteStream& getVariableReverseEndian(T& variable)
    {
        byte* revert_pointer = reinterpret_cast<byte*>(&variable);
        byte swap_reserve;

        if(cursor + sizeof(T) > this->size())
            throw Exception(this, Exception::ArrayOutOfBounds, "getVariableReverseEndian went out of bounds.");

        std::memcpy(&variable, &(this->at(cursor)), sizeof(T));
        cursor += sizeof(T);

        for(size_t i = 0; i < (sizeof(T) / 2); i++)
        {
            swap_reserve = revert_pointer[sizeof(T) - 1 - i];
            revert_pointer[sizeof(T) - 1 - i] = revert_pointer[i];
            revert_pointer[i] = swap_reserve;
        }

        return *this;
    }

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
    ByteStream& addInt(int32_t number);

    /**
     * @brief Adds a 16-bit (word) int as 2 new elements in Little Endian fashion (LSB first, MSB last)
     * NOTE: IF YOUR PROCESSOR IS BIG ENDIAN, SET `PROCESSOR_IS_BIG_ENDIAN` MACRO TO 1!
     * @param number    16-bit integer.
     * @return          Reference to this vector.
     */
    ByteStream& addWord(uint16_t number);

    /**
     * @brief Gets a 32-bit int element from the 4 bytes in front of the reader cursor.
     * @param number    32-bit integer where the element will be stored.
     * @return          Reference to this vector.
     */
    ByteStream& getInt(int32_t& number);

    /**
     * @brief Gets a 16-bit unsigned int element (word) from the 2 bytes in front of the reader cursor.
     * @param number    16-bit integer where the element will be stored.
     * @return          Reference to this vector.
     */
    ByteStream& getWord(uint16_t& number);

    /**
     * @brief Adds a C-type variable of any type into the stream. Doesn't work with C++ variables like strings or vectors.
     * @param number    C type variable, including array or structs. Not STL variables or other kind of dynamically allocated variables.
     * @return          Reference to this vector.
     */
    template<typename T> ByteStream& addVariable(T variable)
    {
        this->insert(this->end(), (unsigned char*)&variable, &(((unsigned char*)&variable)[sizeof(T)]));
        return *this;
    }

    /**
     * @brief Gets a C-type variable of any type from the stream. Doesn't work with C++ variables like strings or vectors.
     * @param number    C type variable reference, including array or structs. Not STL variables or other kind of dynamically allocated variables.
     * @return          Reference to this vector.
     */
    template<typename T> ByteStream& getVariable(T& variable)
    {
        if(cursor + sizeof(T) > this->size())
            throw Exception(this, Exception::ArrayOutOfBounds, "getVariable went out of bounds.");

        std::memcpy(&variable, &(this->at(cursor)), sizeof(T));
        cursor += sizeof(T);

        return *this;
    }

#if PROCESSOR_IS_BIG_ENDIAN == 0
    inline ByteStream& addIntBigEndian(int32_t number) {return addIntReverseEndian(number);}
    inline ByteStream& addWordBigEndian(uint16_t number) {return addWordReverseEndian(number);}
    template<typename T> inline ByteStream& addVariableBigEndian(T number) {return addVariableReverseEndian<T>(number);}
    inline ByteStream& addIntLittleEndian(int32_t number) {return addInt(number);}
    inline ByteStream& addWordLittleEndian(uint16_t number) {return addWord(number);}
    template<typename T> inline ByteStream& addVariableLittleEndian(T number) {return addVariable<T>(number);}

    inline ByteStream& getIntBigEndian(int32_t& number) {return getIntReverseEndian(number);}
    inline ByteStream& getWordBigEndian(uint16_t& number) {return getWordReverseEndian(number);}
    template<typename T> inline ByteStream& getVariableBigEndian(T& number) {return getVariableReverseEndian<T>(number);}
    inline ByteStream& getIntLittleEndian(int32_t& number) {return getInt(number);}
    inline ByteStream& getWordLittleEndian(uint16_t& number) {return getWord(number);}
    template<typename T> inline ByteStream& getVariableLittleEndian(T& number) {return getVariable<T>(number);}
#else
    inline ByteStream& addIntBigEndian(int32_t number) {return addInt(number);}
    inline ByteStream& addWordBigEndian(uint16_t number) {return addWord(number);}
    template<typename T> inline ByteStream& addVariableBigEndian(T number) {return addVariable<T>(number);}
    inline ByteStream& addIntLittleEndian(int32_t number) {return addIntReverseEndian(number);}
    inline ByteStream& addWordLittleEndian(uint16_t number) {return addWordReverseEndian(number);}
    template<typename T> inline ByteStream& addVariableLittleEndian(T number) {return addVariableReverseEndian<T>(number);}

    inline ByteStream& getIntBigEndian(int32_t& number) {return getInt(number);}
    inline ByteStream& getWordBigEndian(uint16_t& number) {return getWord(number);}
    template<typename T> inline ByteStream& getVariableBigEndian(T& number) {return getVariable<T>(number);}
    inline ByteStream& getIntLittleEndian(int32_t& number) {return getIntReverseEndian(number);}
    inline ByteStream& getWordLittleEndian(uint16_t& number) {return getWordReverseEndian(number);}
    template<typename T> inline ByteStream& getVariableLittleEndian(T& number) {return getVariableReverseEndian<T>(number);}
#endif

    /**
     * @brief Adds a (up to) 28-bit MIDI-fashioned Variable length number into this vector.
     * MIDI Variable length: Each byte stores 7 bits plus a flag. If this flag is 1, this number is bigger and continues at the next byte, recursively, until it finds a 0 flag byte.
     * The flag corresponds to the highest value bit in the byte (0x80).
     *
     * @param number    28-bit integer.
     * @return          Reference to this vector.
     */
    ByteStream& addMidiVarLen(uint32_t number);

    /**
     * @brief Gets a (up to) 28-bit MIDI-fashioned Variable length number from this vector.
     * MIDI Variable length: Each byte stores 7 bits plus a flag. If this flag is 1, this number is bigger and continues at the next byte, recursively, until it finds a 0 flag byte.
     * The flag corresponds to the highest value bit in the byte (0x80).
     *
     * @param number    Integer where the number will be stored.
     * @return          Reference to this vector.
     */
    ByteStream& getMidiVarLen(int& number);

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
        if(cursor + sizeof(T) > this->size())
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
    size_t readFile(const char* filepath);

    /**
     * @brief Dumps this ByteStream data into a file.
     * @param filepath      Path of the file you want to write to.
     * @return              Amount of bytes written.
     */
    size_t writeFile(const char* filepath);
};

}

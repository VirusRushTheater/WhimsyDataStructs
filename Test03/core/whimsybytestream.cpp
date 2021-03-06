#include "whimsyexception.h"
#include "whimsybytestream.h"

using namespace whimsycore;

ByteStream& ByteStream::addIntReverseEndian(int32_t number)
{
    byte output[4];
    output[0] = number >> 24;   // LSB
    output[1] = number >> 16;
    output[2] = number >> 8;
    output[3] = number;         // MSB

    this->insert(this->end(), &(output[0]), &(output[4]));

    return *this;
}

ByteStream& ByteStream::addWordReverseEndian(uint16_t number)
{
    byte output[2];
    output[0] = number >> 8;    // LSB
    output[1] = number;         // MSB

    this->insert(this->end(), &(output[0]), &(output[2]));

    return *this;
}

ByteStream& ByteStream::getIntReverseEndian(int32_t& number)
{
    if(cursor + 4 > this->size())
        throw Exception(this, Exception::ArrayOutOfBounds, "getIntReverseEndian went out of bounds.");

    byte* input = reinterpret_cast<byte*>(&number);
    input[3] = this->at(cursor++);
    input[2] = this->at(cursor++);
    input[1] = this->at(cursor++);
    input[0] = this->at(cursor++);

    return *this;
}

ByteStream& ByteStream::getWordReverseEndian(uint16_t &number)
{
    if(cursor + 2 > this->size())
        throw Exception(this, Exception::ArrayOutOfBounds, "getWordReverseEndian went out of bounds.");

    byte* input = reinterpret_cast<byte*>(&number);
    input[1] = this->at(cursor++);
    input[0] = this->at(cursor++);

    return *this;
}

ByteStream& ByteStream::addInt(int32_t number)
{
    this->insert(this->end(), (unsigned char*)&number, &(((unsigned char*)&number)[4]));
    return *this;
}

ByteStream& ByteStream::addWord(uint16_t number)
{
    this->insert(this->end(), (unsigned char*)&number, &(((unsigned char*)&number)[2]));
    return *this;
}

ByteStream& ByteStream::addMidiVarLen(uint32_t number)
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

ByteStream& ByteStream::getMidiVarLen(int& number)
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

ByteStream& ByteStream::getInt(int32_t &number)
{
    if(cursor + 4 > this->size())
        throw Exception(this, Exception::ArrayOutOfBounds, "getInt went out of bounds.");

    std::memcpy(&number, &(this->at(cursor)), 4);
    cursor += 4;
    return *this;
}

ByteStream& ByteStream::getWord(uint16_t &number)
{
    if(cursor + 2 > this->size())
        throw Exception(this, Exception::ArrayOutOfBounds, "getWord went out of bounds.");

    std::memcpy(&number, &(this->at(cursor)), 2);
    cursor += 2;
    return *this;
}
/*
template<typename T> ByteStream& ByteStream::addVariable(T variable)
{
    this->insert(this->end(), (unsigned char*)&variable, &(((unsigned char*)&variable)[sizeof(T)]));
    return *this;
}

template<typename T> ByteStream& ByteStream::getVariable(T& variable)
{
    if(cursor + sizeof(T) >= this->size())
        throw Exception(this, Exception::ArrayOutOfBounds, "getVariable went out of bounds.");

    std::memcpy(&variable, &(this->at(cursor)), sizeof(T));
    cursor += sizeof(T);

    return *this;
}

template<typename T> ByteStream& ByteStream::addVariableReverseEndian(T variable)
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

template<typename T> ByteStream& ByteStream::getVariableReverseEndian(T& variable)
{
    byte* revert_pointer = reinterpret_cast<byte*>(&variable);
    byte swap_reserve;

    if(cursor + sizeof(T) >= this->size())
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
*/

void ByteStream::seekCur(size_t pos)
{
    if((pos + cursor) >= this->size())
    {
        throw Exception(this, Exception::ArrayOutOfBounds, "Seek out of bounds.");
    }
    else
        cursor += pos;
}

void ByteStream::seekSet(size_t pos)
{
    if(pos >= this->size())
    {
        throw Exception(this, Exception::ArrayOutOfBounds, "Seek out of bounds.");
    }
    else
        cursor = pos;
}

size_t ByteStream::tell() const
{
    return cursor;
}

void ByteStream::rewind()
{
    cursor = 0;
}

size_t ByteStream::writeFile(const char *filepath)
{
    size_t retval;

    std::FILE* fhandler = std::fopen(filepath, "wb");
    if(!fhandler)
        throw Exception(this, Exception::CouldNotOpenFileForWriting, filepath);

    retval = std::fwrite(&(this->at(0)), this->size(), 1, fhandler);
    std::fclose(fhandler);

    return retval;
}

size_t ByteStream::readFile(const char *filepath)
{
    size_t retval;

    std::FILE* fhandler = std::fopen(filepath, "rb");
    if(!fhandler)
        throw Exception(this, Exception::CouldNotOpenFileForReading, filepath);

    std::fseek(fhandler, 0, SEEK_END);
    retval = std::ftell(fhandler);
    std::rewind(fhandler);

    this->clear();
    this->resize(retval);

    retval = std::fread(&(this->at(0)), this->size(), 1, fhandler);
    std::fclose(fhandler);

    return retval;
}

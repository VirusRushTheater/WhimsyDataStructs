#include "whimsyexception.h"
#include "whimsybytestream.h"

using namespace whimsycore;

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

size_t ByteStream::write(const char *filepath)
{
    size_t retval;

    std::FILE* fhandler = std::fopen(filepath, "wb");
    if(!fhandler)
        throw Exception(this, Exception::CouldNotOpenFileForWriting, filepath);

    retval = std::fwrite(&(this->at(0)), this->size(), 1, fhandler);
    std::fclose(fhandler);

    return retval;
}

size_t ByteStream::read(const char *filepath)
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

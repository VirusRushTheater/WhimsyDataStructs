#include "ChannelField.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace whimsy;

ChannelField::ChannelField() :
    _type(Byte_field),
    _name(std::string("Nameless"))
{
}

ChannelField::ChannelField(ChannelFieldDataType type, std::string name) :
    _type(type),
    _name(name)
{
}

ChannelField::ChannelField(ChannelFieldDataType type, const char* name) :
    _type(type),
    _name(std::string(name))
{
}

ChannelFieldData& ChannelField::at(uint32_t pos)
{
    return _data.at(pos);
}

ChannelFieldData& ChannelField::operator [](uint32_t pos)
{
    return at(pos);
}

std::string ChannelField::toStringAt(uint32_t pos, FlagType fl) const
{   
    if(WHIMSYDATA_ISNULL(_data.at(pos)))
        return std::string("-");
 
    std::string         retval;
    std::ostringstream  retstream;
    switch(_type)
    {
        case Boolean_field:
            retstream << std::dec << (int) (_data.at(pos).byte_t & 1);
            
            return retstream.str();
        break;
        
        case Nibble_field:
            if(fl & WHIMSYFLAG_HEX)
                retstream << std::hex << (int) (_data.at(pos).byte_t & 15);
            else
                retstream << (int) (_data.at(pos).byte_t & 15);
            
            return retstream.str();
        break;
        
        case Byte_field:
            if(fl & WHIMSYFLAG_HEX)
                retstream << std::hex << (int) _data.at(pos).byte_t;
            else
                retstream << (int) _data.at(pos).byte_t;
            
            return retstream.str();
        break;
        
        case Word_field:
            if(fl & WHIMSYFLAG_HEX)
                retstream << std::hex << _data.at(pos).word_t;
            else
                retstream << _data.at(pos).word_t;
            
            return retstream.str();
        break;
        
        case Note_field:
            int chrome, octave, prenote;
            prenote =   _data.at(pos).note_t - WHIMSYNOTE_OFFSET;
            
            chrome =    prenote % 12;
            octave =    prenote / 12;
            
            switch(chrome)
            {
                case 0:     retstream << "C-"; break;
                case 1:     (fl & WHIMSYFLAG_BEMOL) ? (retstream << "Db") : (retstream << "C#"); break;
                case 2:     retstream << "D-"; break;
                case 3:     (fl & WHIMSYFLAG_BEMOL) ? (retstream << "Eb") : (retstream << "D#"); break;
                case 4:     retstream << "E-"; break;
                case 5:     retstream << "F-"; break;
                case 6:     (fl & WHIMSYFLAG_BEMOL) ? (retstream << "Gb") : (retstream << "F#"); break;
                case 7:     retstream << "G-"; break;
                case 8:     (fl & WHIMSYFLAG_BEMOL) ? (retstream << "Ab") : (retstream << "G#"); break;
                case 9:     retstream << "A-"; break;
                case 10:    (fl & WHIMSYFLAG_BEMOL) ? (retstream << "Bb") : (retstream << "A#"); break;
                case 11:    retstream << "B-"; break;
                default:    retstream << "--";
            }
            retstream << octave;
            
            return retstream.str();
        break;
                    
        default:
            return std::string("Unknown");
        
    }
}

std::string ChannelField::toString(FlagType fl) const
{
    std::ostringstream  retval;
    uint32_t            cursor;
    
    for(cursor = 0; cursor < _data.size(); cursor++)
        retval << toStringAt(cursor, fl) << " | ";
    
    return retval.str();
}

ChannelFieldData ChannelField::interpret()
{
    ChannelFieldData    d;
    WHIMSYDATA_SETNULL(d);
    return d;
}

ChannelFieldData ChannelField::interpret(int data)
{
    ChannelFieldData    d;
    NoteType            pseudodata;
    switch(_type)
    {
        case Boolean_field:
            d.byte_t = (uint8_t)(data & 1);
        break;
        case Nibble_field:
            d.byte_t = (uint8_t)(data & 15);
        break;
        case Byte_field:
            d.byte_t = (uint8_t)data;
        break;
        case Word_field:
            d.word_t = (uint16_t)data;
        break;
        case Note_field:
            pseudodata = static_cast<NoteType>(data);
            if(pseudodata < WHIMSYNOTE_OFFSET)
                WHIMSYDATA_SETNULL(d);
            else
                d.note_t = (NoteType)pseudodata;
        break;
        default:
            WHIMSYDATA_SETNULL(d);
    }

    return d;
}

ChannelFieldData ChannelField::interpret(float data)
{
    ChannelFieldData    d;
    if(_type == Float_field)
        d.float_t = data;
    else
        WHIMSYDATA_SETNULL(d);

    return d;
}

ChannelFieldData ChannelField::interpret(const char* data)
{
    ChannelFieldData    d;
    int                 retval;

    if(strlen(data) <= 0 || strcmp(data, "-") == 0)
    {
        WHIMSYDATA_SETNULL(d);
        return d;
    }

    switch(_type)
    {
        case Boolean_field:
        case Nibble_field:
        case Byte_field:
        case Word_field:
            if(strncmp(data, "0x", 2) == 0 || strncmp(data, "0X", 2))
                retval = strtol(&(data[2]), NULL, 16);
            else
                retval = strtol(&(data[2]), NULL, 10);
            d = interpret(retval);
        break;
        case Float_field:
            d = interpret(strtof(data, NULL));
        break;
        case Note_field:
            d.note_t = interpretNote(data);
        break;
        default:
            WHIMSYDATA_SETNULL(d);
    }

    return(d);
}

ChannelField& ChannelField::append()
{
    ChannelFieldData    d;
    WHIMSYDATA_SETNULL(d);
    _data.push_back(d);

    return *this;
}

ChannelField& ChannelField::append(int data)
{
    _data.push_back(interpret(data));
    return *this;
}

ChannelField& ChannelField::append(float data)
{
    _data.push_back(interpret(data));
    return *this;
}

ChannelField& ChannelField::append(NoteType data)
{
    return append((int)data);
}

ChannelField& ChannelField::append(const char *data)
{
    _data.push_back(interpret(data));
    return *this;
}

ChannelField& ChannelField::remove(int index)
{
    if(index >= 0)
        _data.erase(_data.begin() + index);
    else
        _data.erase(_data.end() - index + 1);
    return *this;
}

ChannelField& ChannelField::removeLast()
{
    _data.erase(_data.end() - 1);
    return *this;
}

ChannelField& ChannelField::insert(int position)
{
    _data.insert(_data.begin() + position, interpret());
    return *this;
}

ChannelField& ChannelField::insert(int data, int position)
{
    _data.insert(_data.begin() + position, interpret(data));
    return *this;
}

ChannelField& ChannelField::insert(float data, int position)
{
    _data.insert(_data.begin() + position, interpret(data));
    return *this;
}

ChannelField& ChannelField::insert(NoteType data, int position)
{
    insert((int) data, position);
    return *this;
}

ChannelField& ChannelField::insert(const char* data, int position)
{
    _data.insert(_data.begin() + position, interpret(data));
    return *this;
}

ChannelField& ChannelField::operator<<(NullType)
{
    return append();
}

ChannelField& ChannelField::operator<<(int data)
{
    return append(data);
}

ChannelField& ChannelField::operator<<(float data)
{
    return append(data);
}

ChannelField& ChannelField::operator<<(NoteType data)
{
    return append(data);
}

ChannelField& ChannelField::operator<<(const char* data)
{
    return append(data);
}

NoteType ChannelField::interpretNote(const char* note)
{
    char                chrome, octave = 4;
    char*               octavepos;
    //                                    A, B,  C, D, E, F, G
    uint8_t             chrome_table[] = {9, 11, 0, 2, 4, 5, 7,};

    if(strlen(note) > 3)
        return (NoteType) 0;

    octavepos = const_cast<char*>(note);
    while(!(*octavepos >= '0' && *octavepos <= '9') && *octavepos != '\0')
        octavepos = &(octavepos[1]);

    octave = strtol(octavepos, NULL, 10);

    if(note[0] >= 'A' && note[0] <= 'G')
        chrome = chrome_table[note[0] - 'A'];
    else if(note[0] >= 'a' && note[0] <= 'g')
        chrome = chrome_table[note[0] - 'a'];
    else
        return (NoteType) 0;

    if(note[1] == '#')
        chrome++;
    else if(note[1] == 'b' || note[1] == 'B')
        chrome--;

    return((NoteType) WHIMSYNOTE_OFFSET + chrome + octave*12);
}

Channel& Channel::addField(ChannelFieldDataType type, std::string name)
{
    int current_field_amount = _fields.size();

    // Case insensitive. To uppercase.
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    // Element exists, therefore no field added.
    if(_name_map.find(name) != _name_map.end())
        return *this;
    else
    {
        _fields.push_back(ChannelField(type, name));
        _name_map.insert(std::pair<std::string, int>(name, current_field_amount));
    }

    return *this;
}

Channel& Channel::removeField(std::string name)
{
    int pos_to_be_removed;

    // Case insensitive. To uppercase.
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    // Element does not exist.
    if(_name_map.find(name) == _name_map.end())
        return *this;
    else
    {
        pos_to_be_removed =     _name_map[name];
        _name_map.erase(_name_map.find(name));
        _fields.erase(_fields.begin() + pos_to_be_removed);
    }

    return *this;
}

void Channel::verbose()
{
    std::cout << "Amount of fields: " << _fields.size() << std::endl;
    
    uint16_t    field_cursor = 0;
    std::deque<ChannelField>::iterator  f_it;
    for(f_it = _fields.begin(); f_it != _fields.end(); f_it++, field_cursor++)
    {
        std::cout   << "****************************************" << std::endl
                    << "Channel " << field_cursor << std::endl
                    << "Name: " << (*f_it)._name << std::endl
                    << "Type: " << (*f_it)._type << std::endl
                    << "Data: " << (*f_it).toString() << std::endl;
    }
}

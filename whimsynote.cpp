#include "whimsynote.h"
#include <sstream>

WhimsyNote::WhimsyNote(const char *notestr)
{
    fromString(notestr);
}

WhimsyNote::WhimsyNote(std::string notestr)
{
    fromString(notestr.c_str());
}

void WhimsyNoteProto::fromString(std::string note)
{
    fromString(note.c_str());
}

void WhimsyNoteProto::fromString(const char *note)
{
    char                chrome, octave = 4;
    char*               octavepos;
    //                                    A, B,  C, D, E, F, G
    uint8_t             chrome_table[] = {9, 11, 0, 2, 4, 5, 7,};

    if(strlen(note) > 3)
    {
        _notedata = WHIMSYNOTE_NULL;
        return;
    }

    octavepos = const_cast<char*>(note);
    while(!(*octavepos >= '0' && *octavepos <= '9') && *octavepos != '\0')
        octavepos = &(octavepos[1]);

    octave = strtol(octavepos, NULL, 10);

    if(note[0] >= 'A' && note[0] <= 'G')
        chrome = chrome_table[note[0] - 'A'];
    else if(note[0] >= 'a' && note[0] <= 'g')
        chrome = chrome_table[note[0] - 'a'];
    else
    {
        _notedata = WHIMSYNOTE_NULL;
        return;
    }

    if(note[1] == '#')
        chrome++;
    else if(note[1] == 'b' || note[1] == 'B')
        chrome--;

    _notedata =     WHIMSYNOTE_OFFSET + chrome + octave*12;
}

std::string WhimsyNoteProto::toString() const
{   
    std::ostringstream  retstream;
    int chrome, octave, prenote;
    prenote =   _notedata - WHIMSYNOTE_OFFSET;

    chrome =    prenote % 12;
    octave =    prenote / 12;

    switch(chrome)
    {
        case 0:     retstream << "C-"; break;
        //case 1:     (bemol) ? (retstream << "Db") : (retstream << "C#"); break;
        case 1:     retstream << "C#"; break;
        case 2:     retstream << "D-"; break;
        //case 3:     (bemol) ? (retstream << "Eb") : (retstream << "D#"); break;
        case 3:     retstream << "D#"; break;
        case 4:     retstream << "E-"; break;
        case 5:     retstream << "F-"; break;
        //case 6:     (bemol) ? (retstream << "Gb") : (retstream << "F#"); break;
        case 6:     retstream << "F#"; break;
        case 7:     retstream << "G-"; break;
        //case 8:     (bemol) ? (retstream << "Ab") : (retstream << "G#"); break;
        case 8:     retstream << "G#"; break;
        case 9:     retstream << "A-"; break;
        //case 10:    (bemol) ? (retstream << "Bb") : (retstream << "A#"); break;
        case 10:    retstream << "A#"; break;
        case 11:    retstream << "B-"; break;
        default:    retstream << "--";
    }
    retstream << octave;

    return retstream.str();
}

unsigned char& WhimsyNoteProto::value()
{
    return _notedata;
}

int WhimsyNoteProto::toInt() const
{
    return static_cast<int>(_notedata);
}

bool WhimsyNoteProto::isNull() const
{
    return (_notedata == WHIMSYNOTE_NULL);
}

std::string WhimsyNote::toString() const
{
    return WhimsyNoteProto::toString();
}

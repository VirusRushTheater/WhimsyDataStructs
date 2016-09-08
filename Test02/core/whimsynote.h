#pragma once

#include "whimsybase.h"

#include <cstring>
#include <string>

#define     WHIMSYNOTE_NULL             0
#define     WHIMSYNOTE_OFFSET           128

#define     WHIMSYNOTE_SPECIAL_STOP     1
#define     WHIMSYNOTE_SPECIAL_RELEASE  2

namespace whimsycore
{

/**
 * @brief Use Note class instead, please.
 */
class NoteProto
{
    friend class Note;

protected:
    unsigned char notedata;

public:
    void fromString(const char* note);
    void fromString(std::string note);

    unsigned char   value() const;
    unsigned char&  ref();
    std::string     toString() const;
    int             toInt() const;

    bool            isNull() const;
};

/**
 * @brief Convenient way to store a note's information.
 */
class Note : public NoteProto, public Base
{
public:
    WHIMSY_OBJECT_NAME("WhimsyNote")

    static const Note   null, stop, release;

    Note(){notedata = WHIMSYNOTE_NULL;}
    Note(const NoteProto& c){notedata = c.notedata;}
    Note(int note){notedata = note & 255;}
    Note(const char* notestr);
    Note(std::string notestr);

    std::string     toString() const;
};
}


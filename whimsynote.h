#ifndef WHIMSYNOTE_H
#define WHIMSYNOTE_H

#include "whimsybase.h"

#include <cstring>
#include <string>

#define     WHIMSYNOTE_NULL         0
#define     WHIMSYNOTE_OFFSET       128

/**
 * @brief Use WhimsyNote class instead, please.
 */
class WhimsyNoteProto
{
    friend class WhimsyNote;

protected:
    unsigned char _notedata;

public:
    void fromString(const char* note);
    void fromString(std::string note);

    unsigned char&  value();
    std::string     toString() const;
    int             toInt() const;

    bool            isNull() const;
};

/**
 * @brief Convenient way to store a note's information.
 */
class WhimsyNote : public WhimsyNoteProto, public WhimsyBase
{
public:
    WHIMSY_OBJECT_NAME("WhimsyNote")

    WhimsyNote(){_notedata = WHIMSYNOTE_OFFSET;}
    WhimsyNote(const WhimsyNoteProto& c){_notedata = c._notedata;}
    WhimsyNote(int note){_notedata = note & 255;}
    WhimsyNote(const char* notestr);
    WhimsyNote(std::string notestr);

    std::string     toString() const;
};

#endif // WHIMSYNOTE_H

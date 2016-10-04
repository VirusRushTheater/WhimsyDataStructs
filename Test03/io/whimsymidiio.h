#pragma once

#include "../whimsycore.h"

namespace whimsyio
{

using namespace whimsycore;

/**
 * @brief A test class to see how this thing will be structured.
 * I'm thinking for the main Whimsy song data files to be compatible with MIDI. I hope this thing works!
 */
class MidiSong : public SequencedSong
{
protected:
    ByteStream  filedata;

public:
    MidiSong();
};

/**
 * @brief Collection of Readers/Writers for MIDI files.
 */
class MidiIO
{
public:

    /**
     * @brief Reads a MIDI file.
     * @param [In] filename     Path of the MIDI file you want to open.
     * @param [Out] tracks      Reference to a vector to store the tracks in.
     * @return                  Amount of bytes read.
     */
    //static size_t read(const char* filename);

    /**
     * @brief Writes a MIDI file.
     * @param [In] filename     Path of the new MIDI file.
     * @param [In] tracks       Reference to a vector holding tracks info.
     * @return                  Amount of bytes written.
     */
    //static size_t write(const char* filename);
};

}

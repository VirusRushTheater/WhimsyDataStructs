#pragma once
#include "../whimsycore.h"

namespace whimsyio
{

using namespace whimsycore;

class MidiIO;

/**
 * @brief Stores all the data needed for a MIDI track.
 */
class MidiTrack : public Base
{
    friend class MidiIO;

public:
    unsigned int    tempo_bpm;
    struct
    {
        byte        num;
        byte        den;
    }               timesignature;

    TypedTable      tdata;

public:
    WHIMSY_OBJECT_NAME("IO/MidiTrack")
};

/**
 * @brief Collection of Readers/Writers for MIDI files.
 */
class MidiIO
{
    /**
     * @brief Reads a MIDI file.
     * @param [In] filename     Path of the MIDI file you want to open.
     * @param [Out] tracks      Reference to a vector to store the tracks in.
     * @return                  Amount of bytes read.
     */
    static size_t read(const char* filename, WhimsyVector<TypedTable>& tracks);

    /**
     * @brief Writes a MIDI file.
     * @param [In] filename     Path of the new MIDI file.
     * @param [In] tracks       Reference to a vector holding tracks info.
     * @return                  Amount of bytes written.
     */
    static size_t write(const char* filename, WhimsyVector<TypedTable>& tracks);
};

}

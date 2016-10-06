#pragma once

#include "../whimsycore.h"

namespace whimsyio
{

using namespace whimsycore;

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

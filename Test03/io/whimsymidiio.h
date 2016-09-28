#pragma once

#include "../whimsycore.h"

namespace whimsyio
{

using namespace whimsycore;

/**
 * @brief A Test class for song MIDI IO.
 */
class MidiTrackTest : public SequencedSong
{
private:
    WhimsyVector<PatternTable>  channels;

public:
    MidiTrackTest()
    {
        PatternFieldHeader note_hdr[] =
        {
            PatternFieldHeader("Note", "NOTE", Variant::Note),
            PatternFieldHeader("Instrument", "INS", Variant::Byte, 0, 127),
            PatternFieldHeader("Volume", "VOL", Variant::Byte, 0, 127),
            PatternFieldHeader("Software FX", "SWFX", Variant::VariantArray)
        };

        PatternFieldHeader perc_hdr[] =
        {
            PatternFieldHeader("Patch", "PATCH", Variant::Byte, 35, 81),
            PatternFieldHeader("Instrument", "INS", Variant::Byte, 0, 127),
            PatternFieldHeader("Volume", "VOL", Variant::Byte, 0, 127),
            PatternFieldHeader("Software FX", "SWFX", Variant::VariantArray)
        };
    }
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

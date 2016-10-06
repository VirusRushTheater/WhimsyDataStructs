#include "whimsymidiio.h"

using namespace whimsyio;
using namespace whimsycore;

/**
 * @brief Constructor. Fixes dynamic MIDI channel data.
 */
/*
MidiSong::MidiSong()
{

    // channelheaders[channel][field] -> Fields: Note, Instrument, FX
    PatternFieldHeader channelheaders[16][4];

    char chname[16];
    char chcodename[16];

    for(byte i = 0; i < 16; i++)
    {
        std::snprintf(chname, 16, "Channel %02d", i + 1);
        std::snprintf(chcodename, 16, "CH%02d", i + 1);
        channelheaders[i][0] = PatternFieldHeader("Note", "NOTE", Variant::Note);
        channelheaders[i][1] = PatternFieldHeader("Instrument", "INST", Variant::Byte, 0, 127);
        channelheaders[i][2] = PatternFieldHeader("Volume", "VOL ", Variant::Byte, 0, 127);
        channelheaders[i][3] = PatternFieldHeader("Effects", "SWFX", Variant::VariantArray);

        channels.push_back(PatternTable(chname, chcodename)
            .addField(channelheaders[i][0])
            .addField(channelheaders[i][1])
            .addField(channelheaders[i][2])
            .addField(channelheaders[i][3]));
        channel_pointer_map[std::string(chcodename)] =  &(channels.at(i));
        channel_pos_map[std::string(chcodename)] =      i;
    }

}
*/

/*
size_t MidiIO::read(const char* filename, WhimsyVector<TypedTable>& tracks)
{
    ByteStream pool;
    size_t retval = pool.read(filename);


    return retval;
}


size_t MidiIO::write(const char* filename, WhimsyVector<TypedTable>& tracks)
{
    ByteStream pool, trkpool, headertrkpool;
    const unsigned int deltaticks = 1000;

    pool.addItems("MThd",               0x00, 0x00, 0x00, 0x06,
                  0x00,                 0x01)
         .addWordBigEndian(tracks.size())
         .addWordBigEndian(deltaticks);

    for(unsigned int i = 0; i < tracks.size(); i++)
    {
        headertrkpool.clear();
        headertrkpool.addItems("MTrk");

        trkpool.clear();

        // End of track Meta-event
        trkpool.addItems(0x2F, 0x00);

        headertrkpool.addIntBigEndian(trkpool.size());
        pool.concatenate(headertrkpool);
        pool.concatenate(trkpool);
    }

    return pool.write(filename);
}
*/

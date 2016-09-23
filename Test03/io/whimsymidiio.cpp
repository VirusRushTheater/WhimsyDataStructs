#include "whimsymidiio.h"

using namespace whimsyio;
using namespace whimsycore;

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

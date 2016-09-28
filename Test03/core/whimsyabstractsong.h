#pragma once

#include "whimsybase.h"
#include "whimsypatterntable.h"

namespace whimsycore
{

/**
 * @brief Defines a common ground for use in all types of songs, like tempo, time signatures and common IO and engine
 * communication functionality.
 *
 * Currently there are implemented 2 ways to store a song in memory:
 * 1. `SequencedSong`: Simplest of all. It stores each row for
 */
class AbstractSong : public Base
{
protected:

public:
    AbstractSong();
};

}

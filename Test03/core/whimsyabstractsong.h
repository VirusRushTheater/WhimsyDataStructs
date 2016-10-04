#pragma once

#include "whimsybase.h"
#include "whimsypatterntable.h"

#include "../third_party/tinyxml/tinyxml2.h"

namespace whimsycore
{

class SequencedSong;
class MappedSong;

/**
 * @brief Enables easy selection of a portion of a pattern table with several depth levels.
 *
 * You start referencing a song with the PatternSelector (using its constructor or ChangeSong)
 * Then, its procedure is a bit different depending on which type of song does it select.
 *
 * === SequencedSong ===
 * As SequencedSong is not mapped, the entire song information is stored in only one row of PatternTables
 * Then, __if PatternSelector points to a SequencedSong__
 * - PatternSelector[int] selects a row. Alias for PatternSelector.selectRow()
 * - PatternSelector[string] selects a channel. Alias for PatternSelector.selectChannel()
 * - They both point to a PatternTable.
 *
 * __if PatternSelector points to a PatternTable (channel)__
 * - PatternSelector[int] selects a channel row. Alias for PatternSelector.selectRow()
 * - PatternSelector[string] selects a channel field. Alias for PatternSelector.selectField()
 *
 * __if PatternSelector points to a PatternTableField (channel field)__
 * - PatternSelector[int] selects a cell variable.
 *
 * __if PatternSelector points to a Row__
 * - If nothing else selected, PatternSelector[string] selects a channel. Alias for PatternSelector.selectChannel()
 * - If channel already selected, PatternSelector[string] selects a field. Alias for PatternSelector.selectField()
 *
 */
class PatternSelector : public Base
{
private:
    // One of them will be null.
    SequencedSong*      _seqsong;
    MappedSong*         _mapsong;

    // Different depth levels
    PatternTable*       _songchannel;
    int                 _rowpos;
    PatternTableField*  _channelfield;

public:
    /**
     * @brief Constructor for SequencedSong selection.
     * @param seqsong   Pointer to a SequencedSong.
     */
    PatternSelector(SequencedSong* seqsong);

    /**
     * @brief Resets row, channel, field and map selectors.
     * @return  Reference to this PatternSelector.
     */
    void reset();

    /**
     * @brief Clears (turns into Variant::null) all the field associated data in the selection.
     */
    void clear();
};

/**
 * @brief Defines a common ground for use in all types of songs, like tempo, time signatures and common IO and engine
 * communication functionality.
 */
class AbstractSong : public Base
{
protected:

public:
    AbstractSong();

    std::string toString() const
    {
        return "[Abstract song]";
    }
};

}

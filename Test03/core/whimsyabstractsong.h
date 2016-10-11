#pragma once

#include "whimsybase.h"
#include "whimsypatterntable.h"
#include "whimsysystemprofile.h"

namespace whimsycore
{

/**
 * @brief Enables easy selection of a portion of a pattern table with several depth levels.
 *
 * You start referencing a song with the PatternSelector (using its constructor or ChangeSong)
 * Then, its procedure is a bit different depending on which type of song does it select.
 *
 * === Explanation ===
 * If it helps you, think on each patterned song as a table of 4 dimensions. This selector helps to slice
 * each one of these dimensions until you get to a single point you can modify.
 * There's a mathematical definition of what I'm doing.
 * - `S(channel, pattern, field, row)` = a single value you can modify (represented as a reference to a Variant)
 *
 * You can swap any way you like, but with the following requirements:
 * - You must select `channel` prior to `field`. Names and amount of fields depend on the selected channel. Not doing so may lead to unexpected behavior.
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
class Song;

class PatternSelector : public Base
{   
    friend class Song;

private:
    // Selected song
    Song*       _selectedSong;

    // Different depth levels
    PatternTable*       _songchannel;
    int                 _patternpos;
    PatternTableField*  _channelfield;
    int                 _rowpos;

public:
    // TODO: Implement it tomorrow.
    PatternSelector(const Song& _song) :
        _selectedSong(&_song), _songchannel(NULL), _patternpos(-1), _channelfield(NULL), _rowpos(-1) {}

    PatternSelector&    selectChannel(const char* channelid);
    PatternSelector&    selectChannel(size_t channel_index);

    PatternSelector&    selectPattern(size_t pattern_index);

    PatternSelector&    selectField(const char* fieldid);
    PatternSelector&    selectField(size_t field_index);

    PatternSelector&    selectRow(size_t row_index);

    Variant*            operator&();

    PatternSelector&    operator =(const Variant& equal);
};

/**
 * @brief Defines a common ground for use in all types of songs, like tempo, time signatures and common IO and engine
 * communication functionality.
 */
class Song : public Base
{
private:
    void constructFromSysProfile();

protected:
    // Stores system info, for quick song copying.
    SystemProfile                               sysprofile;

    // Normally it would be an integer array, but Variant grants more flexibility, as it may have NULL values and others which may appear in unknown systems.
    // It's a rectangular table indicating rows of polyphonic patterns, played at the same time, in a FamiTracker/Deflemask fashion.
    WhimsyVector<WhimsyVector<Variant> >        sequence_map;

    // Each PatternTable represents a patterned segment in a channel.
    WhimsyVector<WhimsyVector<PatternTable> >   channels;

    // Maps to translate code names into
    std::map<std::string, unsigned int>         channel_pos_map;

public:
    Song();

    std::string toString() const
    {
        return "[Abstract song]";
    }

    /**
     * @brief Loads this song's system profile (channels and fields disposition) from an XML file. See references in the folder system_presets for more information.
     * @param filename  Path of the system profile XML.
     */
    void loadSystemProfileFromXMLFile(const char* filename);

    /**
     * @brief Loads this song's system profile (channels and fields disposition) from a XML string. See references in the folder system_presets for more information.
     * @param xmlstring  String with XML information.
     */
    void loadSystemProfileFromXMLString(const char* xmlstring);

    /**
     * @brief Clears and loads a system profile.
     * @param sp    Loaded system profile.
     */
    void loadSystemProfile(const SystemProfile& sp);

    /**
     * @brief Gets this song's system profile.
     * @return
     */
    SystemProfile getSystemProfile() const;

    /**
     * @brief Clears all this song's and system's info.
     */
    void clear();

    /**
     * @brief Adds a pattern table to a channel.
     * @param channelid     ID (codename) of the channel you want to add a pattern to.
     * @return Pointer to the newly added pattern.
     */
    virtual PatternTable* addChannelPattern(std::string channelid);
    virtual PatternTable* addChannelPattern(size_t channelindex);

    /**
     * @brief Returns a PatternSelector pointing to this song, allowing rows, channels, fields and patterns to be easily selected.
     * Their implementation depends on the c
     * hild class. Read their references for more information.
     * @return
     */
    //virtual PatternSelector     select() = 0;
};

}

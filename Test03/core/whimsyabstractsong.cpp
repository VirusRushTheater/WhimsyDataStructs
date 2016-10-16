#include "whimsyabstractsong.h"
#include "whimsybytestream.h"
#include "../third_party/tinyxml/tinyxml2.h"

using namespace whimsycore;

PatternSelector::PatternSelector(Song& _song) :
    _selectedSong(&_song),
    _channelindex(-1),
    _patternindex(-1),
    _channelandpattern(NULL),
    _fieldindex(-1),
    _channelfield(NULL),
    _rowindex(-1)
{
}

PatternSelector::PatternSelector(Song* _song) :
    _selectedSong(_song),
    _channelindex(-1),
    _patternindex(-1),
    _channelandpattern(NULL),
    _fieldindex(-1),
    _channelfield(NULL),
    _rowindex(-1)
{
}

PatternSelector& PatternSelector::selectChannelUnsafe(const char *channelid)
{
    return selectChannelUnsafe(_selectedSong->channel_pos_map[std::string(channelid)]);
}

PatternSelector& PatternSelector::selectChannelUnsafe(size_t channel_index)
{
    // Sets channel
    _channelindex = channel_index;

    // Resets others
    _patternindex =         -1;
    _channelandpattern =    NULL;
    _fieldindex =           -1;
    _channelfield =         NULL;
    _rowindex =             -1;

    return *this;
}

PatternSelector& PatternSelector::selectChannel(const char *channelid)
{
    if(!_selectedSong)
    {
        throw Exception(this, Exception::IncompleteSongSelector, "No song selected.");
        return *this;
    }
    if(_selectedSong->channel_pos_map.find(std::string(channelid)) == _selectedSong->channel_pos_map.end())
    {
        throw Exception(this, Exception::ChannelDoesNotExist, "Channel does not exist");
        return *this;
    }

    return selectChannel(_selectedSong->channel_pos_map[std::string(channelid)]);
}

PatternSelector& PatternSelector::selectChannel(size_t channel_index)
{
    if(!_selectedSong)
    {
        throw Exception(this, Exception::IncompleteSongSelector, "No song selected.");
        return *this;
    }
    if(channel_index >= _selectedSong->channels.size())
    {
        throw Exception(this, Exception::ChannelDoesNotExist, "Channel out of bounds");
        return *this;
    }

    return selectChannelUnsafe(channel_index);
}

WhimsyVector<std::string> PatternSelector::getChannels() const
{
    WhimsyVector<std::string> retval;

    if(!_selectedSong)
    {
        throw Exception(this, Exception::IncompleteSongSelector, "No song selected.");
        return retval;
    }

    std::map<std::string, unsigned int>::const_iterator pmap;
    for(pmap = _selectedSong->channel_pos_map.begin();
        pmap != _selectedSong->channel_pos_map.end();
        pmap++)
    {
        retval.push_back(pmap->first);
    }

    return retval;
}

size_t PatternSelector::getChannelAmount() const
{
    if(!_selectedSong)
    {
        throw Exception(this, Exception::IncompleteSongSelector, "No song selected.");
        return 0;
    }

    return _selectedSong->channels.size();
}

PatternSelector& PatternSelector::selectPatternUnsafe(size_t pattern_index)
{
    _patternindex =         pattern_index;
    _channelandpattern =    &(_selectedSong->channels[_channelindex][_patternindex]);

    // Resets others
    _fieldindex =           -1;
    _channelfield =         NULL;
    _rowindex =             -1;

    return *this;
}

PatternSelector& PatternSelector::selectPattern(size_t pattern_index)
{
    if(pattern_index >= getPatternAmount())
    {
        throw Exception(this, Exception::ArrayOutOfBounds, "Pattern index does not exist.");
        return *this;
    }

    return selectPatternUnsafe(pattern_index);
}

size_t PatternSelector::getPatternAmount() const
{
    return _selectedSong->channels[_channelindex].size();
}

PatternSelector& PatternSelector::selectFieldUnsafe(const char *fieldid)
{
    //_channelfield = _channelandpattern->codename_map[std::string(fieldid)];
    _channelfield = &_channelandpattern->fields[_channelandpattern->codename_pos[std::string(fieldid)]];
    _fieldindex =   _channelandpattern->codename_pos[std::string(fieldid)];

    // Resets others
    _rowindex =             -1;

    return *this;
}

PatternSelector& PatternSelector::selectFieldUnsafe(size_t field_index)
{
    _channelfield = &(_channelandpattern->fields[field_index]);
    _fieldindex =   field_index;

    // Resets others
    _rowindex =             -1;

    return *this;
}

PatternSelector& PatternSelector::selectField(const char *fieldid)
{
    if(_channelandpattern == NULL)
    {
        throw Exception(this, Exception::IncompleteSongSelector, "Pattern not selected yet. Can't select field.");
        return *this;
    }
    if(_channelandpattern->codename_map.find(std::string(fieldid)) == _channelandpattern->codename_map.end())
    {
        throw Exception(this, Exception::FieldDoesNotExist, "Field not found.");
        return *this;
    }

    return selectFieldUnsafe(fieldid);
}

PatternSelector& PatternSelector::selectField(size_t field_index)
{
    if(field_index >= getFieldAmount())
    {
        throw Exception(this, Exception::ArrayOutOfBounds, "Field index does not exist.");
        return *this;
    }
    return selectFieldUnsafe(field_index);
}

WhimsyVector<std::string> PatternSelector::getFields() const
{
    WhimsyVector<std::string> retval;

    if(!_channelandpattern)
    {
        throw Exception(this, Exception::IncompleteSongSelector, "No pattern selected.");
        return retval;
    }

    std::map<std::string, int>::const_iterator pmap;
    for(pmap = _channelandpattern->codename_pos.begin();
        pmap != _channelandpattern->codename_pos.end();
        pmap++)
    {
        retval.push_back(pmap->first);
    }

    return retval;
}

size_t PatternSelector::getFieldAmount() const
{
    if(!_channelandpattern)
        return 0;

    return _channelandpattern->fields.size();
}


PatternSelector& PatternSelector::selectRowUnsafe(size_t row_index)
{
    _rowindex = row_index;
    return *this;
}

PatternSelector& PatternSelector::selectRow(size_t row_index)
{
    if(row_index >= getRowAmount())
    {
        throw Exception(this, Exception::ArrayOutOfBounds, "Row index does not exist.");
        return *this;
    }

    return selectRowUnsafe(row_index);
}

size_t PatternSelector::getRowAmount() const
{
    if(!_channelfield)
        return 0;

    return _channelfield->data.size();
}

Variant PatternSelector::value() const
{
    return _channelfield->data[_rowindex];
}

PatternSelector& PatternSelector::setValue(const Variant &v)
{
    _channelfield->data[_rowindex] = v;
    return *this;
}

Variant& PatternSelector::operator * ()
{
    return _channelfield->data[_rowindex];
}

PatternSelector& PatternSelector::operator = (const Variant& v)
{
    return setValue(v);
}

PatternSelector& PatternSelector::appendPattern()
{
    size_t patternno = getPatternAmount();

    _selectedSong->addChannelPattern(_channelindex);

    return selectPatternUnsafe(patternno);
}

PatternSelector& PatternSelector::appendRow()
{
    size_t rowno = getRowAmount();

    _channelandpattern->addEmptyRows(1);

    return selectRowUnsafe(rowno);
}

PatternSelector& PatternSelector::appendRows(size_t no)
{
    size_t rowno = getRowAmount();

    _channelandpattern->addEmptyRows(no);

    return selectRowUnsafe(rowno + no - 1);
}

void PatternSelector::resizePattern(size_t newsize)
{
    _channelandpattern->setHeight(newsize);

    // Resets others
    _rowindex =             -1;
}

// ---------------------------------------------------------------------------------

Song::Song()
{

}

void Song::loadSystemProfileFromXMLFile(const char *filename)
{
    ByteStream xmlstring;
    const char* xmlfiledata;

    // ByteStream automatically closes files upon reading them.
    xmlstring.readFile(filename);

    xmlfiledata = reinterpret_cast<char*>(xmlstring.data());
    return loadSystemProfileFromXMLString(xmlfiledata);
}

void Song::loadSystemProfileFromXMLString(const char *xmlstring)
{
    sysprofile.loadFromXML(xmlstring);
    constructFromSysProfile();
}

void Song::loadSystemProfile(const SystemProfile &sp)
{
    sysprofile = sp;
    constructFromSysProfile();
}

SystemProfile Song::getSystemProfile() const
{
    return sysprofile;
}

void Song::constructFromSysProfile()
{
    // Prepares the sequence map. Fills it with NULL elements.
    sequence_map.insert(sequence_map.end(), sysprofile.channels.size(), WhimsyVector<Variant>());

    // Prepares the segment tables.
    channel_pos_map = sysprofile.channel_id_map;
    channels.insert(channels.end(), sysprofile.channels.size(), WhimsyVector<PatternTable>());
}

void Song::clear()
{
    sequence_map.clear();
    channels.clear();
    channel_pos_map.clear();

    sysprofile.name = "";
    sysprofile.channels.clear();
    sysprofile.channel_id_map.clear();
}

PatternTable* Song::addChannelPattern(std::string channelid)
{
    return addChannelPattern(channel_pos_map[channelid]);
}

PatternTable* Song::addChannelPattern(size_t channelindex)
{
    channels[channelindex].push_back(PatternTable(sysprofile.channels[channelindex].name, sysprofile.channels[channelindex].id, sysprofile.channels[channelindex].fields));
    return &(channels[channelindex][channels[channelindex].size() - 1]);
}

PatternSelector Song::select()
{
    return PatternSelector(this);
}

std::string Song::toString() const
{
    std::ostringstream sstr;

    return sstr.str();
}

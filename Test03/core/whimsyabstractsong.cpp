#include "whimsyabstractsong.h"
#include "whimsybytestream.h"
#include "../third_party/tinyxml/tinyxml2.h"

using namespace whimsycore;

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

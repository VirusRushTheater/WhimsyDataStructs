#include "whimsysequencedsong.h"

using namespace whimsycore;

SequencedSong::SequencedSong()
 : _height(0)
{

}

size_t SequencedSong::height() const
{
    return _height;
}

void SequencedSong::setHeight(size_t _newheight)
{
    for(size_t i = 0; i < channels.size(); i++)
        channels[i].setHeight(_newheight);

    _height = _newheight;
}

std::string SequencedSong::toString() const
{
    std::ostringstream totalinfo, headerinfo, rowinfo;
    char chinfo[64];

    headerinfo << "[[SYSTEM INFO]]" << std::endl;

    for(unsigned int i = 0; i < channels.size(); i++)
    {
        std::snprintf(chinfo, 64, "  Channel %02d \"%s\" [%s]", i, channels.at(i)._name.c_str(), channels.at(i)._codename.c_str());
        headerinfo << chinfo << std::endl;
        for(unsigned int j = 0; j < channels[i].fields.size(); j++)
        {
            std::snprintf(chinfo, 64, "    Field %02d.%02d \"%s\" [%s]\t (Type: %s)", i, j,
                          channels[i].fields[j].header.name.c_str(), channels[i].fields[j].header.codename.c_str(), Variant::typeToString(channels[i].fields[j].header.type));
            headerinfo << chinfo << std::endl;
        }
        headerinfo << std::endl;
    }

    totalinfo << headerinfo.str();
    totalinfo << "[[PATTERN INFO]]" << std::endl;


    return totalinfo.str();
}

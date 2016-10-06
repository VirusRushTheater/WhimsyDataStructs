#pragma once

#include "whimsybase.h"
#include "whimsypatterntable.h"
#include "whimsyvector.h"

namespace whimsycore {

struct ChannelHeader : public Base
{
    // Channel names and variables
    std::string                         name, id;
    std::string                         type;
    WhimsyVector<PatternFieldHeader>    fields;

    // Fields mapping variables
    std::map<std::string, unsigned int> field_id_map;
};

struct SystemProfile : public Base
{
    // System variables
    std::string                                 name;

    // Profile related variables
    bool                                        uses_song_mapping;
    WhimsyVector<ChannelHeader>                 channels;

    // Channel mapping variables
    std::map<std::string, unsigned int>         channel_id_map;

public:
    SystemProfile();

    /**
     * @brief Loads the system profile from an XML text.
     * @param xmltext   Null-terminated character string containing the text of a system profile XML.
     */
    void loadFromXML(const char* xmltext);

};

}

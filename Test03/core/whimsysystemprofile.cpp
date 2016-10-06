#include "whimsysystemprofile.h"
#include "../third_party/tinyxml/tinyxml2.h"

#include <iostream>

using namespace whimsycore;

SystemProfile::SystemProfile() :
    uses_song_mapping(false)
{
}

void SystemProfile::loadFromXML(const char *xmltext)
{
    tinyxml2::XMLDocument xmldoc;
    tinyxml2::XMLElement* system_root;

    tinyxml2::XMLElement *channel_node, *field_node;

    ChannelHeader       chh;
    PatternFieldHeader  phh;

    char                codename_limit[5];
    const char*         attribute_test;

    xmldoc.Parse(xmltext);
    system_root = xmldoc.RootElement();

    // System node attributes: name, pattern_based.
    name = std::string(system_root->Attribute("name"));
    uses_song_mapping = system_root->BoolAttribute("mapped");

    // Channel child nodes.
    for(channel_node = system_root->FirstChildElement();
        channel_node != NULL;
        channel_node = channel_node->NextSiblingElement())
    {
        // Not a "channel" field? Ignore.
        if(strcasecmp(channel_node->Name(), "channel") != 0)
            continue;

        // Refreshes the channel. Limits code name to 4 characters.
        chh.name = std::string(channel_node->Attribute("name"));
        strncpy(codename_limit, channel_node->Attribute("id"), 4);
        codename_limit[4] = '\0';
        chh.id = std::string(codename_limit);
        chh.type = std::string(channel_node->Attribute("type"));

        chh.fields.clear();
        chh.field_id_map.clear();

        // Field child nodes.
        for(field_node = channel_node->FirstChildElement();
            field_node != NULL;
            field_node = field_node->NextSiblingElement())
        {
            // Not a "field" field? Ignore.
            if(strcasecmp(field_node->Name(), "field") != 0)
                continue;

            phh.name = std::string(field_node->Attribute("name"));
            strncpy(codename_limit, field_node->Attribute("id"), 4);
            phh.id = std::string(codename_limit);
            phh.type = Variant::typeFromString(field_node->Attribute("type"));

            if((attribute_test = field_node->Attribute("minvalue")) != NULL)
                phh.minvalue = Variant(attribute_test).convert(phh.type);

            if((attribute_test = field_node->Attribute("maxvalue")) != NULL)
                phh.maxvalue = Variant(attribute_test).convert(phh.type);

            if((attribute_test = field_node->Attribute("convertible")) != NULL)
                phh.convertible = strcasecmp(attribute_test, "true") == 0;
            else
                phh.convertible = true;

            chh.field_id_map[phh.id] = chh.fields.size();
            chh.fields.push_back(phh);
        }

        channel_id_map[chh.id] = channels.size();
        channels.push_back(chh);
    }
}

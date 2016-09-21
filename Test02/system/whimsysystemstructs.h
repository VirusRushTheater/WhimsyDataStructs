#pragma once

#include <string>
#include <map>
#include <vector>

#include "../whimsycore.h"

namespace whimsysystem
{

struct ChannelFieldHeader
{
    std::string                         fname;
    whimsycore::Variant::Type           ftype;

    ChannelFieldHeader(std::string fname_, whimsycore::Variant::Type ftype_) : fname(fname_), ftype(ftype_) {}
};

struct ChannelHeader
{
    std::string                         cname;
    std::map<std::string, int>          cfields_namemap;
    std::vector<ChannelFieldHeader>     cfields;

    ChannelHeader(std::string cname_) : cname(cname_) {}

    ChannelHeader& addField(ChannelFieldHeader cfh);
};

struct SystemProfileHeader
{
    std::string                         pname;
    std::map<std::string, int>          pchannels_namemap;
    std::vector<ChannelHeader>          pchannels;

    SystemProfileHeader(std::string pname_) : pname(pname_) {}

    SystemProfileHeader& addChannel(ChannelHeader chf);
};

}

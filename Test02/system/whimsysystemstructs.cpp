#include "whimsysystemstructs.h"

using namespace whimsysystem;

ChannelHeader& ChannelHeader::addField(ChannelFieldHeader cfh)
{
    cfields.push_back(cfh);
    cfields_namemap.at(cfh.fname) =     cfields.size() - 1;
    return *this;
}

SystemProfileHeader& SystemProfileHeader::addChannel(ChannelHeader chf)
{
    pchannels.push_back(chf);
    pchannels_namemap.at(chf.cname) =   pchannels.size() - 1;
    return *this;
}

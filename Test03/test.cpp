#include "whimsycore.h"
#include "whimsyio.h"

#include <iostream>
#include <cstdio>

using namespace whimsycore;

int main(int argc, char** argv)
{
    SystemProfile sp;
    Song sng;

    sng.loadSystemProfileFromXMLFile("../../../Test03/system_presets/preset_midi.xml");

    sng.addChannelPattern("CH01");

    return 0;
}

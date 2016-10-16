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

    PatternSelector sngs = sng.select();
    sngs.selectChannel("CH01").appendPattern().selectField("NOTE").appendRows(8);

    sngs.selectRow(0) = Note("F#2");
    sngs.selectRow(4) = Note("A-2");

    std::cout << sng.select().getChannelAmount() << std::endl;

    return 0;
}

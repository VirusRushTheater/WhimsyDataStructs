#include "whimsycore.h"
#include "whimsyio.h"

#include <iostream>
#include <cstdio>

using namespace whimsycore;

int main(int argc, char** argv)
{
    SystemProfile sp;
    ByteStream xmlfile;
    xmlfile.readFile("../../../Test03/system_presets/preset_midi.xml");

    char* xmlfiledata = reinterpret_cast<char*>(xmlfile.data());

    sp.loadFromXML(xmlfiledata);

    return 0;
}

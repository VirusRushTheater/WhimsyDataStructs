#include "whimsycore.h"
#include "whimsyio.h"

#include <iostream>
#include <cstdio>

using namespace whimsycore;

int main(int argc, char** argv)
{
    whimsyio::MidiSong bullshit;

    bullshit.setHeight(64);

    std::cout << bullshit << std::endl;

    return 0;
}

#include "whimsycore.h"
#include "whimsyio.h"

#include <iostream>
#include <cstdio>

using namespace whimsycore;

int main(int argc, char** argv)
{
    WhimsyVector<TypedTable> wtt;
    wtt.push_back(TypedTable());

    whimsyio::MidiIO::write("thanks.mid", wtt);

    return 0;
}

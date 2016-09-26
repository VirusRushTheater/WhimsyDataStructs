#include "whimsycore.h"
#include "whimsyio.h"

#include <iostream>
#include <cstdio>

using namespace whimsycore;

int main(int argc, char** argv)
{
    WhimsyVector<TypedTable> wtt;
    wtt.push_back(TypedTable());
    wtt[0].addFields(Variant::Note, Variant::Byte, Variant::Byte, Variant::Effect);

    wtt[0].addRow(Note("G-5"),  63,             64,                 Variant::null);
    wtt[0].addRow(Note("G#5"),  Variant::null,  Variant::null,      Variant::null);
    wtt[0].addRow(Note("G-5"),  Variant::null,  Variant::null,      Variant::null);
    wtt[0].addRow(Note("G#5"),  Variant::null,  Variant::null,      Variant::null);
    wtt[0].addRow(Note("G-5"),  Variant::null,  Variant::null,      Variant::null);

    whimsyio::MidiIO::write("thanks.mid", wtt);

    std::cout << wtt[0] << std::endl;

    return 0;
}

#include "whimsycore.h"

#include <iostream>

using namespace whimsycore;

int main(int argc, char** argv)
{
    Variant t = 2;
    int k = 2 + (int)t;

    std::cout << "t + 2 = " << k << std::endl;

    /*
    Channel     testch;

    testch.addField(Variant::Note, "pitch");
    testch.addField(Variant::Byte, "instrument");
    testch.addField(Variant::Nibble, "don't know");

    // testch << ChannelRow() << Note("C-3") << 240 << 15;

    testch._fields[0] << Note("C-3") << Variant::null << Note("A-4") << Variant::null << Note("C3") << Note("B2");
    testch._fields[1] << 12 << Variant::null << Variant::null << Variant::null;
    testch._fields[2] << 15 << Variant::null << Variant::null << Variant::null;

    testch._fields[0].resize(16);
    testch._fields[1].resize(16);
    testch._fields[2].resize(14);

    std::cout << testch << std::endl;
    */

    return 0;
}

#include "whimsycore.h"

#include <iostream>

using namespace whimsycore;

int main(int argc, char** argv)
{
    Channel     testch;
    Note        qn = "C4";
    Variant     vn = 36;
    std::cout << vn.convert(Variant::VariantArray).convert(Variant::String);

    testch.addField(Variant::Note, "pitch");
    testch.addField(Variant::Byte, "instrument");
    testch.addField(Variant::Byte, "don't know");

    //testch.removeField("don't know");

    testch._fields[0] << Note("C-3") << "-" << Note("A-4") << Variant::null;
    testch._fields[1] << 12 << Variant::null << Variant::null << Variant::null;
    testch._fields[2] << 15 << Variant::null << Variant::null << Variant::null;
    std::cout << testch << std::endl;

    return 0;
}

#include "whimsycore.h"
#include "whimsysystem.h"

#include <iostream>

using namespace whimsycore;

int main(int argc, char** argv)
{
    TypedTable t;
    t.addFieldsVector(WhimsyVector<Variant::Type>()   << Variant::Note << Variant::Byte << Variant::Nibble << Variant::Effect);
    t.addRow(Note("C-2"), 2,                0xF,            Variant::null);
    t.addRow(Note("C-2"), Variant::null,    Variant::null,  Variant::null);
    t.addRow(Note("C-2"), Variant::null,    Variant::null,  Variant::null);
    t.addRow(Note("D-2"), Variant::null,    Variant::null,  Variant::null);

    std::cout << t << std::endl;

    return 0;
}

#include "ChannelField.h"

#include "whimsyexception.h"
#include "whimsyvariant.h"
#include "whimsynote.h"
#include "whimsychannelfield.h"

#include <iostream>

using namespace whimsy;

int main(int argc, char** argv)
{
    //throw WhimsyException("Test purposes, no bully!");

    WhimsyChannelField  wchf(WhimsyVariant::Note, "Notes");
    wchf << WhimsyNote("G-5");

    WhimsyVariant wena;

    /*
    Channel             testch;

    testch.addField(Note_field, "pitch");
    testch.addField(Byte_field, "instrument");
    testch.addField(Byte_field, "don't know");
    testch.addField(Nibble_field, "volume");

    testch.removeField("don't know");

    testch._fields[0] << "C-3" << "-" << "A-4" << WHIMSYDATA_NULL;
    testch._fields[1] << "0x0C" << "-" << "-" << "-";
    testch._fields[2] << "0xF" << "-" << "-" << "-";
    */

    std::cout << wchf << std::endl;

    //std::cout << std::endl << "WhimsyChannelField test: " << wchf[2] << std::endl;

    return 0;
}

#include "whimsycore.h"
#include "whimsyio.h"

#include <iostream>
#include <cstdio>

using namespace whimsycore;

int main(int argc, char** argv)
{
    int p;

    ByteStream k;
    k.addMidiVarLen(180375);
    k.getMidiVarLen(p);

    std::cout << p << std::endl;

    return 0;
}

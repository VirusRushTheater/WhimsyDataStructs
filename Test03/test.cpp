#include "whimsycore.h"
#include "whimsyio.h"

#include <iostream>
#include <cstdio>

using namespace whimsycore;

int main(int argc, char** argv)
{
    ByteStream bs;
    bs.addVariableBigEndian<long long>(0xFF00EE11DD22CC33);

    return 0;
}

#include "whimsycore.h"
#include "whimsyio.h"

#include <iostream>
#include <cstdio>

using namespace whimsycore;

int main(int argc, char** argv)
{
    ByteStream k;
    k.read("ahueonao.txt");

    std::cout << k << std::endl;
    return 0;
}

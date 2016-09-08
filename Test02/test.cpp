#include "whimsycore.h"

#include <iostream>

using namespace whimsycore;

int main(int argc, char** argv)
{
    Variant e = 130;

    std::cout << e.noteValue() << std::endl;

    return 0;
}

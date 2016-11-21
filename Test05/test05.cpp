#include "whimsycore.h"
#include <iostream>
#include <stdio.h>

#define JSON_PATH   "variant.json"

using namespace whimsycore;

int main(int argc, char** argv)
{
    ByteStream bs;
    bs.addItems("Welcome to version 2 of Boost.Python, a C++ library which enables seamless interoperability between C++ and the Python programming language. The new version has been rewritten from the ground up, with a more convenient and flexible interface, and many new capabilities, including support for: ");

    std::cout << std::endl << "-> " << bs.base64Encode(true) << std::endl;

    return 0;
}

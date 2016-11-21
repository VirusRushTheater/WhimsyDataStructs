#include "whimsycore.h"
#include <iostream>
#include <stdio.h>

#define JSON_PATH   "variant.json"

using namespace whimsycore;

int main(int argc, char** argv)
{
    Variant jsontree;
    ByteStream fdump;
    char* parserfeed;

    fdump.readFile("../../../Test04/export_files/test.json");
    fdump.push_back(0);

    parserfeed = (char*) fdump.lowLevelData();

    jsontree.parse(parserfeed);

    return 0;
}

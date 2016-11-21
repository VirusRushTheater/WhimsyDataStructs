#include "whimsycore.h"
#include <iostream>
#include <stdio.h>

#define JSON_PATH   "variant.json"

using namespace whimsycore;

int main(int argc, char** argv)
{
    /*
    // Part 1
    FILE*   fh;
    char*   fbuffer = NULL;
    Variant json;
    size_t  fsize;

    fh = fopen(JSON_PATH, "r");
    if(!fh)
        return 1;

    fseek(fh, 0, SEEK_END);
    fsize = ftell(fh);
    rewind(fh);

    fbuffer = (char*) malloc(fsize + 1);

    fread(fbuffer, sizeof(char), fsize + 1, fh);
    fclose(fh);

    json.parse(fbuffer);
    std::cout << json.toJSONPretty() << std::endl;

    free(fbuffer);
    */

    ByteStream bs;
    bs.addItems("This kinda award game and shiet.");

    std::cout << std::endl << "-> " << bs.base64Encode() << std::endl;

    return 0;
}

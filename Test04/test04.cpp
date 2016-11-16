#include "whimsycore.h"
#include <iostream>
#include <stdio.h>

#define JSON_PATH   "variant.json"

using namespace whimsycore;

int main(int argc, char** argv)
{
    FILE*   fh;
    char*   fbuffer;
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

    return 0;
}

#pragma once

#include "whimsybase.h"
#include "whimsyvariant.h"
#include "whimsyexception.h"

namespace whimsycore
{
class Parser : public Base
{
private:
    char* rawstr;
/*
    Tree        parseValue(char** jsonstr);
    Tree        parseObject(char** jsonstr);
    Tree        parseArray(char** jsonstr);
    std::string parseString(char** jsonstr);
    Variant     parseNumber(char** jsonstr);
*/
public:
    Parser(const char* rstr);
    ~Parser();

    //Tree parse();
};

}

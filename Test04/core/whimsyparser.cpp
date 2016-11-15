#include "whimsyparser.h"

using namespace whimsycore;

Parser::Parser(const char* rstr)
{
    rawstr = strdup(rstr);
}

Parser::~Parser()
{
    free(rawstr);
}

// It's unknown which type of value we will find.
// But we are expecting a value. That's for sure.
/*
Tree Parser::parseValue(char **jsonstr)
{
    Tree retval;
    char character = **jsonstr;

    for(;**jsonstr != '\0'; (*jsonstr)++)
    {
        // Omit whitespaces.
        if(character == ' ' || character == '\n' || character == '\t' || character == '\r')
            continue;

        // Parse a number.
        if(character == '-' || (character >= '0' && character <= '9'))
        {
            retval.data() = parseNumber(jsonstr);
            return retval;
        }

        // Parse a string.
        if(character == '\"')
        {
            retval.data() = parseString(jsonstr);
            return retval;
        }

        // Parse an object.
        if(character == '{')
        {

        }
    }
}
*/

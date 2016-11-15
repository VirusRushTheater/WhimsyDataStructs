#include "whimsycore.h"
#include <iostream>

using namespace whimsycore;

int main(int argc, char** argv)
{
    Variant hst;
    hst["webo"][4]["lel"] = "pedro";

    hst["mobius"] = "The Architect";
    hst["kek"] = "Json";
    hst["kek"]["1"] = "1";
    hst["kek"]["2"] = "2";
    hst["kek"]["3"]["a"]["i"] = "3ai";
    hst["kek"]["3"]["a"]["ii"] = "3aii";
    hst["kek"]["3"]["a"]["iii"] = "3aiii";
    hst["kek"]["3"]["b"] = Note("C-2");
    hst["kek"]["3"]["c"] = Note("C#2");
    hst["kek"]["3"]["d"][0] = "the host 1";
    hst["kek"]["3"]["d"][1] = "the host 2";
    hst["kek"]["3"]["d"][2] = 5.5;
    hst["kek"]["3"]["d"][3] = "the host 4";


    std::cout << hst.toJSONPretty();

    return 0;
}

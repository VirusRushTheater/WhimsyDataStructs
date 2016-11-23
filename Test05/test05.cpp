#include <boost/python.hpp>

#include "whimsycore.h"
#include <iostream>
#include <stdio.h>

#define PLUGINS_FOLDER  "../../../Test05/plugins"

using namespace whimsycore;
using namespace boost::python;

int main(int argc, char** argv)
{
    Variant v1, v2;
    v1["uno"]["uno"] = 1;
    v2["uno"]["uno"] = 2;

    v1.merge(v2);

    std::cout << v1 << std::endl;
    /*
    Py_Initialize();

    object main_module =        import("__main__");
    object main_namespace =     main_module.attr("__dict__");

    object ignored =            exec("hello = file('hello.txt', 'w')\n"
                                     "hello.write('Hello world!')\n"
                                     "hello.close()\n"
                                     "print \"Hello agent\"",
                                     main_namespace);
    */

    return 0;
}

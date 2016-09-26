# WhimsyDataStructs #
Some module tests for core data structures for a program I want to make as a personal project.

## How to compile ##
Nothing besides C++ standard library and a C++11 compatible compiler such as GCC. This uses CMake as a convenient way to get everything built.

### Which test modules does it have ###
This has 3 test modules.
- _Test01_: This module features Variant functionality.
- _Test02_: This module features a more robust core class system, and ultimately, tests the TypedTable, basis for future data structures.
- _Test03_: This module features IO file support, testing how these data structures will hold and arrange data in several, flexible formats.

### How does this work ###
Data structures for this project use many of the design freedoms C++11 grants (like Variadic arguments and architecture-independent fixed size
variables) to make them as format-independent as possible.
Therefore you have:
- _whimsycore::Base_: Parent of most of the data structures used in this project. Grants a virtual, inheritable `toString()` function, which allows
for a simple way to debug and contrast results using standard output or dumping data into a file. Once you implement `toString()` in your class, you
can also use it to directly operate it using C++ STL stream classes, like `std::cout`, making `std::cout << [class instance];` possible.
- _whimsycore::Variant_: Cornerstone of music storage classes. Can take a myriad of different values and formats, including 4, 8, 16, 32 and 64 bit integers,
single and double precision floating point numbers, STL string, an array of Variants, and a Null value. It's 3 byte sized. As long as we don't have 100 million on memory,
everything's okay. Your average 13MP camera uses more memory to display an image than what you would need to store music in most cases, don't worry.
- _whimsycore::Note_: A convenience class to store a musical note information, with parsing and interpreting methods. It can store a note ranging from C-0 to G-10 (0 ~ 127),
plus Stop (254), Release (253) and Null (255) notes. `fromString()` is a parser class which accepts any note-formatted string from `C-0` to `B-9` and stores it into a Note variable.
- _whimsycore::WhimsyVector_: A wrapper for `std::vector`. Includes operator <<, and a variadic function to both create it with a couple elements, and store elements into.
- _whimsycore::ByteStream_: A specialized wrapper for byte-based `WhimsyVector`s. It adds some C `stdio`-like functionality (like seek, tell, rewind and cursor-reading methods, including the >> operator),
transferring a file's content in memory, to read and write MIDI variable length numbers, and to read and write 2 and 4 byte variables in both endians.
- _whimsycore::TypedTable_: A 2D Variant arrangement designed to emulate a channel's data. It has a variable number of fields, which force `rows` to be in a given format. Each field has a name, in order to
let an IO module or System engine to interpret these the best way it can.


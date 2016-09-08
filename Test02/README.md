== Classes used in this experiment

=== Core
The core folder has some vital common data strucutres used through the program.
- **whimsycore::Base** is the base class for all classes used in the project. Offers some debug and exception catching facilities, like toString(), std::cout support and class name storage.
- **whimsycore::Exception** is used to throw exceptions.
- **whimsycore::Variant** is used to define different formats of variables, such as integers, floating point decimals, notes, strings and arrays, granting system-flexibility to the program.
- **whimsycore::Note** defines a musical note and certain special commands like Stop and Release.

== System
The system folder has classes to structure how both a song collection and the system in which it would be played.
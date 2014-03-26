// defines some interfaces for MainProgram.cpp. If an interface has different
// implementations, find them in MainProgram_Windows.cpp and MainProgram_Linux.cpp

#include <string>

// Allows the user to press Ctrl+C to shutdown the program. Return true if
// setup succees.
bool setupInterruptHandler();

std::string getLoggingConfigFilePath();
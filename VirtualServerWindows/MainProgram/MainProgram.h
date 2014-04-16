#pragma once
// defines some interfaces for MainProgram.cpp. If an interface has different
// implementations, find them in MainProgram_Windows.cpp and MainProgram_Linux.cpp
#include <stdlib.h>
#include <crtdbg.h>
#include <string>
#include "MainObjectFactoryImpl.h"
#include "XMLDocument.h"

class MainProgram{
public:
    MainProgram();
    void launch();
private:
    MainObjectFactoryImpl* factory;
    // Make sure that ./_config/config.xml and logging configuration file exists.
    void checkConfigs();
    // Sets up loggers.
    void setupLoggers();
    // Sets up configs by "config.xml" file. If failed to parse the file, throw InvalidFormatException.
    void setupConfigs();
    // Sets up all modules.
    void setupModules();
    // Allows the user to press Ctrl+C to shutdown the program.
    void setupSignalHandler();
    // Create and run a HTTP server.
    void runHttpServer();
    // clear
    void clear();

    // Returns the path of logging config file.
    std::string getLoggingConfigFilePath();

    // Returns the current platform such as "Windows", "Linux x86" and "Linux x64".
    std::string getCurrentPlatform();
};

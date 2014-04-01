#pragma once

#include <string>
#include <vector>

using namespace std;

// A data struct of a dynamic library file.
struct DynamicLibraryStruct{
    // the path, related to module's directory
    string path;
    // the platform, such as "Windows", "Linux x86" and "Linux x64"
    string platform;
    // the version
    string version;
};

// A data struct of a module
struct ModuleStruct{
    // the name
    string name;
    // the display name, displayed to user
    string displayName;
    // the description, displayed to user
    string description;
    // its library files
    vector<DynamicLibraryStruct> libraries;
};

// A class to manage modules. It can load modules and provide info of loaded modules.
class IModuleManager{
public:
    // Destructor.
    virtual ~IModuleManager() {}
    // Returns info of all loaded modules.
    virtual vector<ModuleStruct> getModules() = 0;
    // Load one module by its directory path, related to current working directory.
    virtual void load(string modulePath) = 0;
    // Search the current working directory and load all modules.
    virtual void loadAll() = 0;
    // Returns true if the module has been loaded.
    virtual bool isModuleLoaded(string moduleName) = 0;
    // Returns the state such as "Running", "Loading Error", "Unsupport Platform", "Running Error", "Stopped"
    virtual string getModuleState(string moduleName) = 0;
    // Sets the state such as "Running", "Loading Error", "Unsupport Platform", "Running Error", "Stopped"
    virtual void setModuleState(string moduleName, string state) = 0;
};

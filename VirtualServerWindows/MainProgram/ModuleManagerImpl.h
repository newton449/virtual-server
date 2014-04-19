#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../interfaces/IModuleManager.h"
#include "../interfaces/IModuleObjectFactory.h"
#include "XMLDocument.h"
#include "DefaultHttpServletMapping.h"
#include "MainObjectFactoryImpl.h"
#include <mutex>

using namespace std;

class MainObjectFactoryImpl;

class ModuleManagerImpl : public IModuleManager{
public:
    ModuleManagerImpl();
    vector<ModuleStruct> getModules();
    // Load one module by its name. The name should be module's directory. Returns true if no error.
    void load(const string& moduleName);
    // Search the current working directory and load all modules.
    void loadAll();
    // Returns true if the module has been loaded.
    bool isModuleLoaded(const string& moduleName);
    // Returns the state such as "Running", "Loading Error", "Unsupport Platform", "Running Error", "Stopped"
    // If no such state, return an empty string.
    string getModuleState(const string& moduleName);
    // Sets the state such as "Running", "Loading Error", "Unsupport Platform", "Running Error", "Stopped"
    void setModuleState(const string& moduleName, const string& state);
private:
    void addModule(ModuleStruct module);
    void addModuleObjectFactory(string moduleName, IModuleObjectFactory* moduleFactory);
    IModuleObjectFactory* loadDllAndGetModuleFactory(string path);

    void loadBasicInfo(const std::string& moduleName, tinyxml2::XMLElement*& root, ModuleStruct& module);

    void loadProperties(const std::string& moduleName, tinyxml2::XMLElement*& root);

    bool loadLibrariesInfo(const std::string& moduleName, tinyxml2::XMLElement*& root, ModuleStruct& module, IModuleObjectFactory*& moduleFactory);

    void loadServletsInfo(const std::string& moduleName, tinyxml2::XMLElement*& root, IModuleObjectFactory*& moduleFactory, DefaultHttpServletMapping*& mapping);

    void loadStaticResourcesInfo(const std::string& moduleName, tinyxml2::XMLElement*& root, IModuleObjectFactory*& moduleFactory, DefaultHttpServletMapping*& mapping);

    void loadMenuInfo(const std::string& moduleName, tinyxml2::XMLElement*& root);

    MainObjectFactoryImpl* factory;
    vector<ModuleStruct> modules;
    unordered_map<string, string> stateMap;
    unordered_map<string, IModuleObjectFactory*> factoryMap;
    std::unordered_set<std::string>* primaryKeys;
    std::recursive_mutex lock;
};
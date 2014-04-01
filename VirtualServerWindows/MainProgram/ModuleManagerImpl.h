#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "../interfaces/IModuleManager.h"
#include "../interfaces/IModuleObjectFactory.h"

using namespace std;

class ModuleManagerImpl : public IModuleManager{
public:
	vector<ModuleStruct> getModules();
	// Load one module by its name. The name should be module's directory. Returns true if no error.
    void load(string moduleName);
	// Search the current working directory and load all modules.
	void loadAll();
    // Returns true if the module has been loaded.
    bool isModuleLoaded(string moduleName);
    // Returns the state such as "Running", "Loading Error", "Unsupport Platform", "Running Error", "Stopped"
    // If no such state, return an empty string.
    string getModuleState(string moduleName);
    // Sets the state such as "Running", "Loading Error", "Unsupport Platform", "Running Error", "Stopped"
    void setModuleState(string moduleName, string state);
private:
	void addModule(ModuleStruct module);
	void addModuleObjectFactory(string moduleName, IModuleObjectFactory* moduleFactory);
	IModuleObjectFactory* loadDllAndGetModuleFactory(string path);

	vector<ModuleStruct> modules;
    unordered_map<string, string> stateMap;
    unordered_map<string, IModuleObjectFactory*> factoryMap;
};
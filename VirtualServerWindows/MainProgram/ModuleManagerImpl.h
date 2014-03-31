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
	// Load one module by its name. The name should be module's directory.
    void load(string moduleName);
	// Search the current working directory and load all modules.
	void loadAll();
    // Returns true if the module has been loaded.
    bool isModuleLoaded(string moduleName);
private:
	void addModule(ModuleStruct module);
	void addModuleObjectFactory(string moduleName, IModuleObjectFactory* moduleFactory);
	IModuleObjectFactory* loadDllAndGetModuleFactory(string path);

	vector<ModuleStruct> modules;
	map<string, IModuleObjectFactory*> factoryMap;
};
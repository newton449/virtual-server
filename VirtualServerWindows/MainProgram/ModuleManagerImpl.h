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
	// Load one module by its directory path.
	void load(string modulePath);
	// Search the current working directory and load all modules.
	void loadAll();
private:
	void addModule(ModuleStruct module);
	void addModuleObjectFactory(string moduleName, IModuleObjectFactory* moduleFactory);
	IModuleObjectFactory* loadDllAndGetModuleFactory(string path);

	vector<ModuleStruct> modules;
	map<string, IModuleObjectFactory*> factoryMap;
};
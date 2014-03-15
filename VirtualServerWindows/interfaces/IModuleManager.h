#pragma once

#include <string>
#include <vector>

using namespace std;

 struct DynamicLibraryStruct{
	string path;
	string platform;
	string version;
};

 struct ModuleStruct{
	string displayName;
	string description;
	DynamicLibraryStruct* libraries;
	int librarySize;
};

class IModuleManager{
public:
	virtual ~IModuleManager() {}
	// Returns info of all loaded modules.
	virtual vector<ModuleStruct> getModules() = 0;
	// Load one module by its directory path.
	virtual void load(string modulePath) = 0;
	// Search the current working directory and load all modules.
	virtual void loadAll() = 0;
};
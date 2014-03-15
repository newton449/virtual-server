#pragma once

#include <string>
#include "IModuleManager.h"
#include "IClientManager.h"
#include "ILogger.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////
// An object factory provided by MainProgram for every components to use.
class IMainObjectFactory{
public:
	virtual ~IMainObjectFactory() {}
	// Returns an object by key.
	virtual void* getObject(const string& key) = 0;
	// Sets an object with its key.
	virtual void setObject(const string& key, void* object) = 0;
	// Returns an instance of IModuleManager.
	virtual IModuleManager* getModuleManager() = 0;
	// Returns an instance of IClientManager.
	virtual IClientManager* getClientManager() = 0;
};
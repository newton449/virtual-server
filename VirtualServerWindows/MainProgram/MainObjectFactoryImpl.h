#pragma once

#include <unordered_map>
#include "../interfaces/IMainObjectFactory.h"
#include "AggregateHttpServletMapping.h"
#include "ModuleManagerImpl.h"
#include "ClientManagerImpl.h"

typedef std::map<std::string, std::string> PropertyMap;

class MainObjectFactoryImpl : public IMainObjectFactory{
public:
	static MainObjectFactoryImpl* getInstance();
	// Returns an object by key.
	void* getObject(const string& key);
	// Sets an object with its key.
	void setObject(const string& key, void* object);
	// Returns an instance of IModuleManager.
	IModuleManager* getModuleManager();
	// Returns an instance of IClientManager.
	IClientManager* getClientManager();
    // Returns an property map of configurations.
    PropertyMap* getPropertyMap();

	AggregateHttpServletMapping* getAggregateHttpServletMapping();
private:
	static MainObjectFactoryImpl* INSTANCE;
	AggregateHttpServletMapping* mapping;

	unordered_map<string, void*> objectMap;
};

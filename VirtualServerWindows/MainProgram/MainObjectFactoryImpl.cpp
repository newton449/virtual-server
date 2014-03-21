#include "MainObjectFactoryImpl.h"
#include "ModuleManagerImpl.h"
#include "ClientManagerImpl.h"
#include "AggregateHttpServletMapping.h"
#include "Logger.h"

MainObjectFactoryImpl* MainObjectFactoryImpl::INSTANCE = NULL;

MainObjectFactoryImpl* MainObjectFactoryImpl::getInstance(){
	if (INSTANCE == NULL){
		// create one
		INSTANCE = new MainObjectFactoryImpl();
		INSTANCE->setObject("IModuleManager", new ModuleManagerImpl());
		INSTANCE->setObject("IClientManager", new ClientManagerImpl());
		INSTANCE->mapping = new AggregateHttpServletMapping();
	}
	return INSTANCE;
}

void* MainObjectFactoryImpl::getObject(const string& key){
	unordered_map<string, void*>::iterator it = objectMap.find(key);
	if (it == objectMap.end()){
		return NULL;
	}
	return it->second;
}

void MainObjectFactoryImpl::setObject(const string& key, void* object){
	unordered_map<string, void*>::iterator it = objectMap.find(key);
	if (it == objectMap.end()){
		objectMap[key] = object;
	}
	else{
		// delete old object
		delete it->second;
		it->second = object;
	}
}

IModuleManager* MainObjectFactoryImpl::getModuleManager(){
	return (IModuleManager*)getObject("IModuleManager");
}

IClientManager* MainObjectFactoryImpl::getClientManager(){
	return (IClientManager*)getObject("IClientManager");
}

AggregateHttpServletMapping* MainObjectFactoryImpl::getAggregateHttpServletMapping(){
	return mapping;
}

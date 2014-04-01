#include "MainObjectFactoryImpl.h"
#include "ModuleManagerImpl.h"
#include "ClientManagerImpl.h"
#include "AggregateHttpServletMapping.h"
#include "Logger.h"
#include <exception>
#include <stdexcept>

MainObjectFactoryImpl* MainObjectFactoryImpl::INSTANCE = NULL;

MainObjectFactoryImpl* MainObjectFactoryImpl::getInstance() {
    if (INSTANCE == NULL) {
        // create one
        INSTANCE = new MainObjectFactoryImpl();
        INSTANCE->setObject("IModuleManager", new ModuleManagerImpl());
        INSTANCE->setObject("IClientManager", new ClientManagerImpl());
        INSTANCE->setObject("PropertyMap", new PropertyMap());
        INSTANCE->mapping = new AggregateHttpServletMapping();
    }
    return INSTANCE;
}

void* MainObjectFactoryImpl::getObject(const string& key) {
    unordered_map<string, void*>::iterator it = objectMap.find(key);
    if (it == objectMap.end()) {
        return NULL;
    }
    return it->second;
}

void MainObjectFactoryImpl::setObject(const string& key, void* object) {
    unordered_map<string, void*>::iterator it = objectMap.find(key);
    if (it == objectMap.end()) {
        objectMap[key] = object;
    }
    else {
        // not allow, because we don't know how to delete old object
        // If we delete it directly, its destructor will not be called.
        throw std::logic_error("A object of the key \"" + key + "\" has been set.");
    }
}

IModuleManager* MainObjectFactoryImpl::getModuleManager() {
    return (IModuleManager*)getObject("IModuleManager");
}

IClientManager* MainObjectFactoryImpl::getClientManager() {
    return (IClientManager*)getObject("IClientManager");
}

AggregateHttpServletMapping* MainObjectFactoryImpl::getAggregateHttpServletMapping() {
    return mapping;
}

PropertyMap* MainObjectFactoryImpl::getPropertyMap(){
    return (PropertyMap*)getObject("PropertyMap");
}

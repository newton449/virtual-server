#include "MainObjectFactoryImpl.h"
#include "ModuleManagerImpl.h"
#include "ClientManagerImpl.h"
#include "DefaultHttpServletMapping.h"
#include "Logger.h"
#include <exception>
#include <stdexcept>

MainObjectFactoryImpl* MainObjectFactoryImpl::INSTANCE = NULL;
std::recursive_mutex MainObjectFactoryImpl::staticLock;

MainObjectFactoryImpl* MainObjectFactoryImpl::getInstance() {
    std::lock_guard<std::recursive_mutex> guard(staticLock);
    if (INSTANCE == NULL) {
        // create one
        INSTANCE = new MainObjectFactoryImpl();
        INSTANCE->setObject("IModuleManager", new ModuleManagerImpl());
        INSTANCE->setObject("IClientManager", new ClientManagerImpl());
        INSTANCE->setObject("PropertyMap", new PropertyMap());
        INSTANCE->setObject("primaryKeys", new KeySet());
        INSTANCE->mapping = new DefaultHttpServletMapping();
    }
    return INSTANCE;
}

void MainObjectFactoryImpl::clearInstance(){
    std::lock_guard<std::recursive_mutex> guard(staticLock);
    if (INSTANCE != NULL){
        delete INSTANCE;
        INSTANCE = NULL;
    }
}

MainObjectFactoryImpl::~MainObjectFactoryImpl(){
    // delete known objects
    delete mapping;

    IModuleManager* o1 = getModuleManager();
    delete o1;
    IClientManager* o2 = getClientManager();
    delete o2;
    PropertyMap* o3 = getPropertyMap();
    delete o3;
    KeySet* o4 = getPrimaryKeys();
    delete o4;
    // TODO delete unknown objects
}

void* MainObjectFactoryImpl::getObject(const string& key) {
    std::lock_guard<std::mutex> guard(lock);
    unordered_map<string, void*>::iterator it = objectMap.find(key);
    if (it == objectMap.end()) {
        return NULL;
    }
    return it->second;
}

void MainObjectFactoryImpl::setObject(const string& key, void* object) {
    std::lock_guard<std::mutex> guard(lock);
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

DefaultHttpServletMapping* MainObjectFactoryImpl::getHttpServletMapping() {
    std::lock_guard<std::mutex> guard(lock);
    return mapping;
}

PropertyMap* MainObjectFactoryImpl::getPropertyMap(){
    return (PropertyMap*)getObject("PropertyMap");
}

KeySet* MainObjectFactoryImpl::getPrimaryKeys(){
    return (KeySet*)getObject("primaryKeys");
}


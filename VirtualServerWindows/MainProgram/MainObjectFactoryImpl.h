#pragma once

#include <unordered_map>
#include "../interfaces/IMainObjectFactory.h"
#include "DefaultHttpServletMapping.h"
#include "ModuleManagerImpl.h"
#include "ClientManagerImpl.h"
#include <mutex>

typedef std::map<std::string, std::string> PropertyMap;

typedef std::unordered_set<std::string> KeySet;

class MainObjectFactoryImpl : public IMainObjectFactory{
public:
    static MainObjectFactoryImpl* getInstance();

    static void clearInstance();

    ~MainObjectFactoryImpl();
    // Returns an object by key.
    void* getObject(const string& key);
    // Sets an object with its key.
    void setObject(const string& key, void* object);
    // Sets an object with its key and returns the old object.
    void* replaceObject(const std::string& key, void* object);
    // Removes an object by its key and returns the removed object.
    void* removeObject(const std::string& key);
    // Returns an instance of IModuleManager.
    IModuleManager* getModuleManager();
    // Returns an instance of IClientManager.
    IClientManager* getClientManager();
    // Returns an property map of configurations.
    PropertyMap* getPropertyMap();

    KeySet* getPrimaryKeys();

    DefaultHttpServletMapping* getHttpServletMapping();
private:
    static MainObjectFactoryImpl* INSTANCE;
    static std::recursive_mutex staticLock;

    DefaultHttpServletMapping* mapping;
    unordered_map<string, void*> objectMap;
    std::mutex lock;

    void* getExistingObject(const string& key);
};

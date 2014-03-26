#pragma once

#include <string>
#include "IModuleManager.h"
#include "IClientManager.h"
#include "ILogger.h"

using namespace std;
extern "C" {
    // An object factory, provided by MainProgram for every module to use.

    class IMainObjectFactory {
    public:
        // Destructor.

        virtual ~IMainObjectFactory() {
        }
        // Returns an object by key.
        virtual void* getObject(const string& key) = 0;
        // Sets an object with its key. This class will delete/release it. If it already exists, the old
        // one will be deleted and released.
        virtual void setObject(const string& key, void* object) = 0;
        // Returns an instance of IModuleManager. It can also be get by getObject("IModuleManager").
        virtual IModuleManager* getModuleManager() = 0;
        // Returns an instance of IClientManager. It can also be get by getObject("IClientManager").
        virtual IClientManager* getClientManager() = 0;
    };
}

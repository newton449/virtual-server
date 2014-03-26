#include<stdio.h>
#include<dlfcn.h>
#include<stdlib.h>
#include "../../VirtualServerWindows/MainProgram/ModuleManagerImpl.h"
#include "../../VirtualServerWindows/MainProgram/MainObjectFactoryImpl.h"
#include "../../VirtualServerWindows/interfaces/ILogger.h"
#include "../../VirtualServerWindows/interfaces/IModuleObjectFactory.h"

IModuleObjectFactory* ModuleManagerImpl::loadDllAndGetModuleFactory(string path) {
    void *handler;
    char *error;
    handler = dlopen(path.c_str(), RTLD_LAZY);
    if (!handler) {
        LOG(ERROR) << "Failed to open the dynamic library " << path << ": " << dlerror();
        return NULL;
    }
    loadModuleAndReturnFactory func = (loadModuleAndReturnFactory) dlsym(handler, "loadModuleAndReturnFactory");
    if ((error = dlerror()) != NULL) {
        LOG(ERROR) << "Failed to get the function.";
        exit(1);
    }
    IModuleObjectFactory* ret = func(MainObjectFactoryImpl::getInstance());

    //dlclose(handler); /* closing the file handle */

    return ret;
}
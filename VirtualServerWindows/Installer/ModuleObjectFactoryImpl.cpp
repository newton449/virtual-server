#include "ModuleObjectFactoryImpl.h"
#include "../interfaces/ILogger.h"

ModuleObjectFactoryImpl::ModuleObjectFactoryImpl() {
    factory = new ServletFactoryImpl();
}

IServletFactory* ModuleObjectFactoryImpl::getServletFactory(){
    return factory;
}

extern "C"{
DLLEXPORT IModuleObjectFactory* loadModuleAndReturnFactory(IMainObjectFactory* mainFactory){
#ifdef ENABLE_LOGGING
    el::Helpers::setStorage(*((el::base::type::StoragePointer*)mainFactory->getObject("LoggingStorage")));
#endif
    return new ModuleObjectFactoryImpl();
}
}

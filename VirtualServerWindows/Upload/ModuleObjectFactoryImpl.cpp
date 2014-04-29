#include "ModuleObjectFactoryImpl.h"
#include "../interfaces/ILogger.h"

ModuleObjectFactoryImpl* ModuleObjectFactoryImpl::INSTANCE = NULL;

ModuleObjectFactoryImpl* ModuleObjectFactoryImpl::getInstance(){
    if (INSTANCE == NULL){
        INSTANCE = new ModuleObjectFactoryImpl();
    }
    return INSTANCE;
}

ModuleObjectFactoryImpl::ModuleObjectFactoryImpl() {
    servletFactory = new ServletFactoryImpl();
    mainObjectFactory = NULL;
}

IServletFactory* ModuleObjectFactoryImpl::getServletFactory() {
    return servletFactory;
}

IMainObjectFactory* ModuleObjectFactoryImpl::getMainObjectFactory(){
    return mainObjectFactory;
}

void ModuleObjectFactoryImpl::setMainObjectFactory(IMainObjectFactory* factory){
    mainObjectFactory = factory;
}

DLLEXPORT IModuleObjectFactory* loadModuleAndReturnFactory(IMainObjectFactory* mainFactory) {
    el::Helpers::setStorage(*((el::base::type::StoragePointer*)mainFactory->getObject("LoggingStorage")));
    ModuleObjectFactoryImpl* ret= ModuleObjectFactoryImpl::getInstance();
    ret->setMainObjectFactory(mainFactory);
    return ret;
}
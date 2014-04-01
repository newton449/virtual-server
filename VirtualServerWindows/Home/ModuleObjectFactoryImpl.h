#pragma once

#include "../interfaces/IModuleObjectFactory.h"
#include "ServletFactoryImpl.h"
#include "../interfaces/IMainObjectFactory.h"

class ModuleObjectFactoryImpl : public IModuleObjectFactory{
public:
	IServletFactory* getServletFactory();
    static ModuleObjectFactoryImpl* getInstance();
    IMainObjectFactory* getMainObjectFactory();
    void setMainObjectFactory(IMainObjectFactory* factory);
private:
    static ModuleObjectFactoryImpl* INSTANCE;
    ServletFactoryImpl* servletFactory;
    IMainObjectFactory* mainObjectFactory;

    ModuleObjectFactoryImpl();
};

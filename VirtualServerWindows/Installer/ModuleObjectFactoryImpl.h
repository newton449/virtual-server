#pragma once

#include "../interfaces/IModuleObjectFactory.h"
#include "ServletFactoryImpl.h"

class ModuleObjectFactoryImpl : public IModuleObjectFactory{
public:
	ModuleObjectFactoryImpl();
	IServletFactory* getServletFactory();
private:
	ServletFactoryImpl* factory;
};

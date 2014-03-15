/*
  Modules should provide this ModuleObjectFactory for MainProgram to get objects.
  */
#pragma once

#include "IServletFactory.h"
#include "IMainObjectFactory.h"

class IModuleObjectFactory{
public:
	virtual ~IModuleObjectFactory() {}
	// Returns an IServletFactory. The caller should destory the instance.
	virtual IServletFactory* getServletFactory() = 0;
};

#ifdef MAIN_PROGRAM
typedef IModuleObjectFactory* (*loadModuleAndReturnFactory)(IMainObjectFactory* mainFactory);
#else
extern "C"{
	__declspec(dllexport) IModuleObjectFactory* loadModuleAndReturnFactory(IMainObjectFactory* mainFactory);
}
#endif

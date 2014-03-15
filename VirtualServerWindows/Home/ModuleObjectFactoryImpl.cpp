#include "ModuleObjectFactoryImpl.h"
#include "../interfaces/ILogger.h"

ModuleObjectFactoryImpl::ModuleObjectFactoryImpl() {
	factory = new ServletFactoryImpl();
}

IServletFactory* ModuleObjectFactoryImpl::getServletFactory(){
	return factory;
}
extern "C"{
	__declspec(dllexport) IModuleObjectFactory* loadModuleAndReturnFactory(IMainObjectFactory* mainFactory){
		el::Helpers::setStorage(*((el::base::type::StoragePointer*)mainFactory->getObject("LoggingStorage")));
		return new ModuleObjectFactoryImpl();
	}
}

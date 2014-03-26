#include "ServletFactoryImpl.h"
#include "HttpServletsImpl.h"

IHttpServlet* ServletFactoryImpl::createInstance(const std::string name){
	if (name == "ModulesListServlet"){
		return new ModulesListServlet();
	}
	if (name == "CheckDependenciesServlet"){
		return new CheckDependenciesServlet();
	}
	if (name == "CreateServerServlet"){
		return new CreateServerServlet;
	}
	if (name == "GetUrlServlet"){
		return new GetUrlServlet;
	}
	return NULL;
}

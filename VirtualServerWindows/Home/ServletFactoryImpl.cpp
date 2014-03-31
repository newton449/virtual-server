#include "ServletFactoryImpl.h"
#include "HttpServletsImpl.h"

IHttpServlet* ServletFactoryImpl::createInstance(const std::string name){
	if (name == "RedirectToHomeServlet"){
		return new RedirectToHomeServlet();
	}
	if (name == "MenuListServlet"){
		return new MenuListServlet();
	}
    if (name == "ServerInfoServlet"){
        return new ServerInfoServlet();
    }
	return NULL;
}

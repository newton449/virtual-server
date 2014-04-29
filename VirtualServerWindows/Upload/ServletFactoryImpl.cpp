#include "ServletFactoryImpl.h"
#include "HttpServletsImpl.h"

IHttpServlet* ServletFactoryImpl::createInstance(const std::string name){
	if (name == "UploadServlet"){
		return new UploadServlet();
	}
	if (name == "TreeViewServlet"){
		return new TreeViewServlet();
	}
	return NULL;
}

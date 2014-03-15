#pragma once

#include "../interfaces/IServletFactory.h"

class ServletFactoryImpl : public IServletFactory{
public:
	IHttpServlet* createInstance(const std::string name);
};
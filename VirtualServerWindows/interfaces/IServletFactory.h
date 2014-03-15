/*
 A factory to create servlet by name (instead of URL).
 */
#pragma once

#include <string>
#include "IHttpServlet.h"

class IServletFactory{
public:
	virtual ~IServletFactory() {}
	virtual IHttpServlet* createInstance(const std::string name) = 0;
};
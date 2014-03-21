#pragma once

#include <string>
#include "IHttpServlet.h"

using namespace std;

// An interface to provide servlets according to URLs. 
class IHttpServletMapping{
public:
	// virtual destructor
	virtual ~IHttpServletMapping() {}
	// Returns an IHttpServlet according to the url. The caller should delete the instance. If no
	// servlet can handle this URL, returns null.
	virtual IHttpServlet* createServlet(const string& url) = 0;
};

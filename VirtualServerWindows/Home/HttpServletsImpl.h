#pragma once

#include "../interfaces/IHttpServlet.h"

class RedirectToHomeServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
};

class MenuListServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
};

class ServerInfoServlet : public IHttpServlet{
public:
    // Do the HTTP method.
    void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
};
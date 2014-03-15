#pragma once

#include "../interfaces/IHttpServlet.h"

class ModulesListServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
};

class CheckDependenciesServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
};

class CreateServerServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
};

class GetUrlServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
private:
	static int COUNT;

	String buildResult(String url, int size, float percentage, int waiting);
};

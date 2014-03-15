/*
  An aggregate implementation of IHttpServletMapping. We can add multiple IServletFactory
  instances with patterns to it so that it can choose one between them according to the patterns.
*/
#pragma once

#include <unordered_map>
#include "../interfaces/IHttpServletMapping.h"
#include "../interfaces/IServletFactory.h"

using namespace std;

class AggregateHttpServletMapping : public IHttpServletMapping{
public:
	// Returns an IHttpServlet according to the url. The caller should
	// delete the instance.
	IHttpServlet* createServlet(const string& url);
	// Maps an URL to a servlet factory and servlet name. When creating servlet for the URL, it will
	// ask the factory to create a servlet with the servlet name. 
	void addServletMapping(const string& url, IServletFactory* servletFactory,
		const string& servletName);
	// Maps a context path to a directory path for static resources.
	void addResourcesMapping(const string& contextPath, const string& directory);
private:
	unordered_map<string, pair<IServletFactory*, string> > servletMap;

	unordered_map<string, string> resourceMap;
};

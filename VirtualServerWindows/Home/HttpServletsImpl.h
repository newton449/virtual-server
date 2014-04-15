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

class UploadingServlet : public IHttpServlet{
public:
    // Do the HTTP method.
    void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
};

#include <istream>
#include <string>

using namespace std;

class UploadingHandler{
public:
    std::string getTempDirectory();
    void setTempDirectory(std::string dir);
    void handleRequestBody(IHttpServletRequest& request);
    std::string getFirstFile();
private:
    std::string tempDirectory;
    std::map<std::string, std::string> fieldMap;

    std::string getBoundary(IHttpServletRequest& request);
    std::map<std::string, std::string> parseHeaders(istream& in);
    std::map<std::string, std::string> parseDisposition(std::string headerValue);


};
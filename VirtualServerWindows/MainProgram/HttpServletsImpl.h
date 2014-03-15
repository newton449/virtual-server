/*
  It provides some general IHttpServlet implementation for modules to use.
  */

#pragma once

#include "../interfaces/IHttpServlet.h"
#include "Logger.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////
// A default implementation of IHttpServlet. It just responses 405 errors.
class DefaultHttpServlet : public IHttpServlet{
public:
	// virtual destructor
	virtual ~DefaultHttpServlet() {}
	// Do the HTTP method.
	virtual void doMethod(String methodName, IHttpServletRequest& request,
		IHttpServletResponse& response);
};

//////////////////////////////////////////////////////////////////////////
// A servlet to reply static resources in a directory according to URLs and context path.
class StaticResourcesServlet : public DefaultHttpServlet{
public:
	// Construct it with context path and directory path. It will accept URLs in the context path,
	// search a static resource in the directory path according to the rest of URL (no context path),
	// and reply the whole contents of the resource. A context path is the string between first and
	// second slash in URL. A context path may be empty.
	StaticResourcesServlet(string contextPath, string directoryPath);
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
private:
	string contextPath;
	string directoryPath;
};


////////////////////////////////////////////////////////////////////////
// A servlet to receive uploaded file. It requires the following params:
// - file_name: a string for the file name stored in the server.
class UploadFileServlet : public DefaultHttpServlet{
public:
	// Constructor with the folder to save uploaded files.
	explicit UploadFileServlet(std::string folder);
	// Do HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
private:
	std::string folder;
	// Checks the request. Returns false if error occurred.
	bool checkRequest(IHttpServletRequest& request, IHttpServletResponse& response);
	// Create the folder for the file.
	void createFolderForFile(std::string file);
	// Reads one chunk in the input stream. Returns false to break the
	// loop.
	bool readOneChunk(std::istream& in, int& chunkSize, std::string& chunkSizeLine, bool& error, char*& buf, int& bufSize, std::ofstream& fout, IHttpServletResponse& response);
};
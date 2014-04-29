#pragma once

#include "../interfaces/IHttpServlet.h"

/////////////////////////////////////////////
// Bei Li Add New Servlet Here
//////////////////////////////////////////////
class UploadServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
private:
	bool checkRequest(IHttpServletRequest& request, IHttpServletResponse& response);
	// Create the folder for the file.
	//void createFolderForFile(std::string file);
	// Reads one chunk in the input stream. Returns false to break the
	// loop.
	bool readOneChunk(std::istream& in, int& chunkSize, std::string& chunkSizeLine, bool& error, char*& buf, int& bufSize, std::ofstream& fout, IHttpServletResponse& response);
    std::string getFileName(std::istream& in, std::string boundary);
	std::string getDirName(std::istream& in, std::string boundary);
};

class TreeViewServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
};
#include <fstream>
#include "HttpServletsImpl.h"
#include "FileSystem.h"
#include "Logger.h"
#include "StringUtils.h"

////////////////////////////////////////////////////////////////////////
// Function implementations of DefaultHttpServlet

// Do the HTTP method.
void DefaultHttpServlet::doMethod(String methodName, IHttpServletRequest& request,
	IHttpServletResponse& response){
	response.sendError(405); // 405 Method Not Allowed
}

////////////////////////////////////////////////////////////////////////
// Function implementations of StaticResourcesServlet
StaticResourcesServlet::StaticResourcesServlet(string contextPath, string directoryPath)
:contextPath(contextPath), directoryPath(directoryPath){

}

void StaticResourcesServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	// Only get method is allowed
	if (request.getMethod() != "GET"){
		response.sendError(404);
		return;
	}

	// check context path
	string url = request.getRequestUrl();
	if (!StringUtils::startWith(url, contextPath + "/")){
		response.sendError(500);
		LOG(WARNING) << "The url \"" << url << "\" does not match the context path \"" << contextPath << "\".";
		return;
	}

	// get short url (without first slash) 
	url = url.substr(contextPath.length() + 1);
	if (url.empty()){
		url = "index.html"; // default page
	}

	// build file path
    string filePath = StringUtils::fixFilePath(directoryPath + url);

	// check whether it exists
	if (!FileSystem::File::exists(filePath)){
		LOG(DEBUG) << "Failed to find a file for \"" << url << "\" in directory \"" << directoryPath << "\"";
		response.sendError(404);
		return;
	}

	// get file size
	LOG(DEBUG) << "Sending file: " << filePath;
	FileSystem::FileInfo info(filePath);
	size_t fileSize = info.size();
	response.setContentLength(fileSize);
	// TODO set content type according to mine-type
	if (StringUtils::hasEnding(filePath, ".html")){
		response.setContentType("text/html");
	}
	else if (StringUtils::hasEnding(filePath, ".zip")){
		response.setContentType("application/x-compressed");
	}
	else if (StringUtils::hasEnding(filePath, ".png")){
		response.setContentType("image/png");
	}
	else if (StringUtils::hasEnding(filePath, ".gif")){
		response.setContentType("image/gif");
	}
	else if (StringUtils::hasEnding(filePath, ".jpg")){
		response.setContentType("image/jpg");
	}
	else if (StringUtils::hasEnding(filePath, ".js")){
		response.setContentType("text/javascript");
	}
	else if (StringUtils::hasEnding(filePath, ".txt")){
		response.setContentType("text/plain");
	}
	else if (StringUtils::hasEnding(filePath, ".css")){
		response.setContentType("text/css");
	}
	else {
		LOG(WARNING) << "Unknown MIME type";
		response.sendError(404);
	}

    response.flushBuffer();

	// send the file to response
	ostream& out = response.getOutputStream();
	ifstream fin(filePath, ifstream::in | ifstream::binary);
    int sentCount = 0;
    if (fin.good()){
        char buf[1024];
        while (true){
            fin.read(buf, 1024);
            if (fin){
                out.write(buf, fin.gcount());
            }
            else{
                out.write(buf, fin.gcount());
                break;
            }
        }
        fin.close();
    }
    else{
        response.sendError(404);
    }
	//int c = fin.get();
	//while (c != EOF){
	//	out.put(c);
	//	c = fin.get();
	//}
	//fin.close();
}

////////////////////////////////////////////////////////////////////////
// Function implementations of UploadFileServlet

// Constructor with the folder to save uploaded files.
UploadFileServlet::UploadFileServlet(std::string folder){
	if (folder.empty()){
		this->folder = ".\\";
	}
	else if (folder[folder.size() - 1] == '\\'){
		this->folder = folder;
	}
	else{
		this->folder = folder + "\\";
	}
}

// Do HTTP method.
void UploadFileServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	if (!checkRequest(request, response)){
		return;
	}
	// Create the file. The current file will be overrided.
	std::string name = request.getParameter("file_name");
	createFolderForFile(folder + name);
	std::ofstream fout;
	fout.open(folder + name, std::ofstream::out | std::ofstream::binary);
	if (!fout){
		response.sendErrorWithMessage(500, "Cannot open the file.");
		return;
	}
	// Read input
	bool error = true;
	std::istream& in = request.getInputStream();
	std::string chunkSizeLine;
	std::string tmp;
	int chunkSize;
	std::getline(in, chunkSizeLine);
	char* buf = NULL;
	int bufSize = 0;
	while (in){
		if (!readOneChunk(in, chunkSize, chunkSizeLine, error, buf, bufSize, fout, response)){
			break;
		}
		// Read the next chunk
		std::getline(in, chunkSizeLine);
	}
	if (buf != NULL){
		delete buf;
	}
	// close the file
	fout.close();
	// Send error if occurred
	if (error){
		if (!response.isCommitted()){
			response.sendErrorWithMessage(400, "Wrong chunked format");
		}
		// throw an exception to close connection
		throw std::logic_error("Wrong chunked format");
	}
	else{
		LOG(INFO) << "Saved the file \"" << folder << name << "\".";
	}
}

void UploadFileServlet::createFolderForFile(std::string file){
	size_t pos = file.find_last_of("\\");
	if (pos != std::string::npos){
		std::string dir = file.substr(0, pos);
		if (!FileSystem::Directory::exists(dir)){
			FileSystem::Directory::create(dir);
		}
	}
}

// Checks the request. Returns false if error occurred.
bool UploadFileServlet::checkRequest(IHttpServletRequest& request, IHttpServletResponse& response){
	// Check whether it is chunck mode
	if (request.getHeader("Transfer-Encoding") != "chunked"){
		response.sendErrorWithMessage(501, "Please use chunked mode");
		return false;
	}
	std::string name = request.getParameter("file_name");
	if (name.empty()){
		// PENDING 404?
		response.sendErrorWithMessage(404, "Invalid file name");
		return false;
	}
	return true;
}

// Reads one chunk in the input stream. Returns false to break the
// loop.
bool UploadFileServlet::readOneChunk(std::istream& in, int& chunkSize, std::string& chunkSizeLine, bool& error, char*& buf, int& bufSize, std::ofstream& fout, IHttpServletResponse& response){
	std::string tmp;
	if (chunkSizeLine.empty() || chunkSizeLine[0]<48 || chunkSizeLine[0]>57){
		// it is an invalid chuncked format
		return false;
	}
	chunkSize = std::atoi(chunkSizeLine.c_str()); // ignore optional alphabets.
	if (chunkSize == 0){
		// read the empty line
		std::getline(in, tmp);
		error = false; // exit normally
		return false;
	}
	// check buf
	if (bufSize < chunkSize){
		if (buf != NULL){
			delete buf;
		}
		buf = new char[chunkSize];
		bufSize = chunkSize;
	}
	// read chunk
	in.read(buf, chunkSize);
	if (!in){
		return false;
	}
	// read the \r\n
	std::getline(in, tmp);
	if (tmp != "\r" && !tmp.empty()){
		return false;
	}
	// Save to the file
	fout.write(buf, chunkSize);
	if (!fout){
		response.sendErrorWithMessage(500, "Failed to save the file.");
		return false;
	}
	return true;
}

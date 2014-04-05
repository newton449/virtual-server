/////////////////////////////////////////////////////////////////////
//  HttpServerSupport.h - provides some classes for HttpServer.    //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2012                                 //
//  Platform:      Windows 8                                       //
//  Application:   CSE687 Pr3, Spring 2013                         //
//  Author:        Sheng Wang                                      //
/////////////////////////////////////////////////////////////////////

#include <regex>
#include "HttpServerSupport.h"

////////////////////////////////////////////////////////////////////////
// Function implementations of HttpServletRequestImpl

// Constructor with the istream.
HttpServletRequestImpl::HttpServletRequestImpl(std::istream& input)
: input(input) {
}

// Add a header with the name and the value.
void HttpServletRequestImpl::addHeader(String name, String value){
	headerMap[name].push_back(value);
}

// Set HTTP method.
void HttpServletRequestImpl::setMethod(String method){
	httpMethod = method;
}

// Add a parameter with the name and value.
void HttpServletRequestImpl::addParameter(String name, String value){
	paramMap[name].push_back(value);
}

// Set a header with the name and the value.
void HttpServletRequestImpl::setHeader(String name, String value){
	Vector& vec = headerMap[name];
	vec.clear();
	vec.push_back(value);
}

// Set the query string.
void HttpServletRequestImpl::setQueryString(String str){
	queryString = str;
}

// Set the request url.
void HttpServletRequestImpl::setRequestUrl(String url){
	requestUrl = url;
}

// Returns character encoding in the "Content-Type" header such as
// "iso-8859-1" and "utf-8".
HttpServletRequestImpl::String HttpServletRequestImpl::getCharacterEncoding(){
	String type = getHeader("Content-Type");
	if (type.empty()){
		return "";
	}
	// Content-Type is something like text/html; charset=utf-8. It may
	// not contain the charset.
	size_t pos = type.find("charset=");
	if (pos == String::npos){
		return "";
	}
	return type.substr(pos + 8, type.length() - pos - 8);
}

// Returns the length of request body excluding headers. Returns -1 
// if not exists.
int HttpServletRequestImpl::getContentLength(){
	return getIntHeader("Content-Length");
}

// Returns the header value of the name. Returns an empty string if 
// no such header. Returns the first value if it has more than one 
// values.
HttpServletRequestImpl::String HttpServletRequestImpl::getHeader(String name){
	Map::iterator itr = headerMap.find(name);
	if (itr == headerMap.end()){
		return "";
	}
	if (itr->second.empty()){
		return "";
	}
	return itr->second[0];
}

// Returns all header names in the request.
HttpServletRequestImpl::Vector HttpServletRequestImpl::getHeaderNames(){
	Vector ret;
	for (auto& pair : headerMap){
		ret.push_back(pair.first);
	}
	return ret;
}

// Returns an istream for reading the request body.
std::istream& HttpServletRequestImpl::getInputStream(){
	return input;
}

// Returns the integer value of the specific name. Returns -1 if the
// header does not exist. Return 0 if the value is zero or not a 
// number.
int HttpServletRequestImpl::getIntHeader(String name){
	String str = getHeader(name);
	if (str.empty()){
		return -1;
	}
	// Convert it to a number. Return 0 if it is not a number.
	return atoi(str.c_str());
}

// Returns HTTP method of the request such as "GET" and "POST".
HttpServletRequestImpl::String HttpServletRequestImpl::getMethod(){
	return httpMethod;
}

// Returns the parameter of the name. For "GET" method, parameters
// are in the first line of HTTP request after the token "?". For
// "POST" method, parameters are in the request body.
HttpServletRequestImpl::String HttpServletRequestImpl::getParameter(String name){
	Map::iterator itr = paramMap.find(name);
	if (itr == paramMap.end()){
		return "";
	}
	if (itr->second.empty()){
		return "";
	}
	return itr->second[0];
}

// Returns the parameter map. For "GET" method, parameters are in the
// firsr line of HTTP request after the token "?". For "POST" method,
// parameters are in the request body.
HttpServletRequestImpl::Map HttpServletRequestImpl::getParameterMap(){
	return paramMap;
}

// Returns the parameter names. For "GET" method, parameters are in
// the first line of HTTP request after the token "?". For "POST"
// method, parameters are in the request body.
HttpServletRequestImpl::Vector HttpServletRequestImpl::getParameterNames(){
	Vector ret;
	for (auto& pair : paramMap){
		ret.push_back(pair.first);
	}
	return ret;
}

// Returns the query string in first line of HTTP request after the
// token "?". It is like "n1=v1&n2=v2&t3".
HttpServletRequestImpl::String HttpServletRequestImpl::getQueryString(){
	return queryString;
}

// Returns the request url in first line of HTTP request before the
// token "?". Returns "/" at least.
HttpServletRequestImpl::String HttpServletRequestImpl::getRequestUrl(){
	return requestUrl;
}

////////////////////////////////////////////////////////////////////////
// Functions implementations of HttpServletResponseImpl

// Constructor.
HttpServletResponseImpl::HttpServletResponseImpl(std::ostream& socketOutput)
: socketOutput(socketOutput), expectedBytesLength(-1),
bufferSize(2147483647), status(200), committed(false),
keepAliveAllowed(false), outputFinished(false){
}

// Returns true if the socketOutput can keep alive. It is meanless 
// until the response is committed.
bool HttpServletResponseImpl::isKeepAliveAllowed(){
	return keepAliveAllowed;
}

// Tells that all headers and body contents are all set. The response
// will try to set Content-Length if possible.
void HttpServletResponseImpl::notifyOutputFinished(){
	if (!outputFinished){
		if (committed){
			// Just flush buffer
		}
		else{
			long len = (long)bufOutput.tellp();
			if (expectedBytesLength < 0){
				// Content-Length hasn't been set.
				if (getHeader("Transfer-Encoding") != "chunked"){
					// Should not set the length in chunked mode.
					setContentLength(len);
				}
			}
			else{
				if (expectedBytesLength != len){
					// The lenghs of buf and expected are different. 
					// This function should not be called.
					throw IllegalOperationException("Cannot notifyOutputFinished() because the lengths of buffer and expected are different.");
				}
				else{
					// Flush them
				}
			}
		}
		flushBuffer();
		outputFinished = true;
	}
}

// Returns true if the client supports keep-alive.
void HttpServletResponseImpl::setKeepAliveSupported(bool supported){
	if (committed){
		throw IllegalOperationException("The response has been committed.");
	}
	keepAliveAllowed = supported;
}

// Adds a header with the name and the value.
void HttpServletResponseImpl::addHeader(String name, String value){
	if (committed){
		throw IllegalOperationException("The response has been committed.");
	}
	if (name == "Content-Length"){
		setContentLength(atoi(value.c_str()));
	}
	else{
		headerMap[name].push_back(value);
	}
}

// Adds an integer value of the name.
void HttpServletResponseImpl::addIntHeader(String name, int value){
	addHeader(name, std::to_string(value));
}

// Returns true if the response contains the header.
bool HttpServletResponseImpl::containsHeader(String name){
	return headerMap.find(name) != headerMap.end();
}

// Writes the data in the buffer to the client. This will make
// response committed.
void HttpServletResponseImpl::flushBuffer(){
	if (!committed){
		// Write status code and headers firstly.
		writeHeaders();
	}
	// Copy contents from bufOutput to socketOutput
	long ctnLen = (long) bufOutput.tellp();
	if (ctnLen != 0){
		if (outputFinished){
			throw IllegalOperationException("Cannot write after output finished.");
		}
		if (expectedBytesLength >= 0 && ctnLen > expectedBytesLength){
			// Bytes to send are larger than excepcted.
			throw IllegalOperationException("All bytes of Content-Length has been sent. Cannot send anymore.");
		}
		std::string ctn = bufOutput.str();
		socketOutput << ctn;
		// Clear bufOutput
		bufOutput.str("");
		if (!socketOutput){
			bufOutput.setstate(socketOutput.rdstate());
		}
		// Change expected bytes length if needed
		if (expectedBytesLength > 0){
			expectedBytesLength -= ctn.length();
		}
	}
}

// Returns the buffer size.
int HttpServletResponseImpl::getBufferSize(){
	// TODO bufferSize does not work now.
	return bufferSize;
}

// Returns the character encoding in "Content-Type" header.
HttpServletResponseImpl::String HttpServletResponseImpl::getCharacterEncoding(){
	String contentType = getContentType();
	if (contentType.empty()){
		return "";
	}
	// Find "=". Contents following "=" are charset.
	size_t pos = contentType.find("=");
	if (pos == String::npos){
		return "";
	}
	return contentType.substr(pos + 1, contentType.length() - 1);
}

// Returns the value of the "Content-Type" header.
HttpServletResponseImpl::String HttpServletResponseImpl::getContentType(){
	return getHeader("Content-Type");
}

// Returns the value of the specific header name.
HttpServletResponseImpl::String HttpServletResponseImpl::getHeader(String name){
	Map::iterator itr = headerMap.find(name);
	if (itr == headerMap.end()){
		return "";
	}
	if (itr->second.empty()){
		return "";
	}
	return itr->second[0];
}

// Returns all header names.
HttpServletResponseImpl::Vector HttpServletResponseImpl::getHeaderNames(){
	Vector ret;
	for (auto& pair : headerMap){
		ret.push_back(pair.first);
	}
	return ret;
}

// Returns all values of the specific header.
HttpServletResponseImpl::Vector HttpServletResponseImpl::getHeaders(String name){
	Map::iterator itr = headerMap.find(name);
	if (itr == headerMap.end()){
		return Vector();
	}
	return itr->second;
}

// Returns an ostream to write data to the client.
std::ostream& HttpServletResponseImpl::getOutputStream(){
	return bufOutput;
}

// Returns the HTTP response status code.
int HttpServletResponseImpl::getStatus(){
	return status;
}

// Returns true if the headers has been written to the client.
bool HttpServletResponseImpl::isCommitted(){
	return committed;
}

// Resets status, all headers and buffer. It must be called before
// committed.
void HttpServletResponseImpl::reset(){
	if (committed){
		throw IllegalOperationException("The response has been committed.");
	}
	headerMap.clear();
	status = 200;
	expectedBytesLength = -1;
	bufOutput.str("");
}

// Resets buffer. It must be called before committed.
void HttpServletResponseImpl::resetBuffer(){
	bufOutput.str("");
}

// Sends the response error with the specific statusCode. It will be 
// committed after using this function.
void HttpServletResponseImpl::sendError(int statusCode){
	sendErrorWithMessage(statusCode, "");
}

// Sends the response error with the specific statusCode and message.
// It will be committed after using this function.
void HttpServletResponseImpl::sendErrorWithMessage(int statusCode, String message){
	if (committed){
		throw IllegalOperationException("The response has been committed.");
	}
	status = statusCode;
	setHeader("Content-Type", "text/html; charset=iso-8859-1");
	headerMap.erase("Content-Length");
	resetBuffer();
	// Build HTML body
	bufOutput << "<!DOCTYPE html>\n";
	bufOutput << "<html>\n";
	bufOutput << "\t<head>\n";
	bufOutput << "\t\t<title>" << std::to_string(status) << " Error</title>\n";
	bufOutput << "\t</head>\n";
	bufOutput << "\t<body>\n";
	bufOutput << "\t\t<h1>" << std::to_string(status) << " Error: " << getStatusExplaination() << "</h1>\n";
	bufOutput << "\t\t<p>" << message << "</p>\n";
	bufOutput << "\t</body>\n";
	bufOutput << "</html>\n";
	// Write headers so that we can make it committed.
	notifyOutputFinished();
	flushBuffer();
}

// Sets the preferred buffer size. 
void HttpServletResponseImpl::setBufferSize(int size){
	// TODO need more researchs.
	throw IllegalOperationException("Not supported.");
}

// Sets the character encoding in the "Content-Type" header.
void HttpServletResponseImpl::setCharacterEncoding(String charset){
	if (committed){
		throw IllegalOperationException("The response has been committed.");
	}
	// Get "Content-Type".
	String type = getContentType();
	if (type.empty()){
		// Set with "text/plain" and the charset
		setContentType("text/plain; charset=" + charset);
	}
	else{
		size_t pos = type.find("charset=");
		if (pos == String::npos){
			// Cannot find the current charset. Just append the new one.
			setContentType(type + " charset=" + charset);
		}
		else{
			// Replace the current charset with the new one.
			setContentType(type.substr(0, pos) + "charset=" + charset);
		}
	}
}

// Sets the Content-Length header.
void HttpServletResponseImpl::setContentLength(long len){
	if (committed){
		throw IllegalOperationException("The response has been committed.");
	}
	// If it is negative, remove the header from headerMap
	if (len < 0){
		headerMap.erase("Content-Length");
		expectedBytesLength = -1;
	}
	else{
		// Set the length
		Vector& vec = headerMap["Content-Length"];
		vec.clear();
		vec.push_back(std::to_string(len));
		expectedBytesLength = len;
	}
}

// Sets the ContentType header.
void HttpServletResponseImpl::setContentType(String type){
	setHeader("Content-Type", type);
}

// Sets the header with the name and its value.
void HttpServletResponseImpl::setHeader(String name, String value){
	if (committed){
		throw IllegalOperationException("The response has been committed.");
	}
	if (name == "Content-Length"){
		setContentLength(atoi(value.c_str()));
	}
	else{
		Vector& vec = headerMap[name];
		vec.clear();
		vec.push_back(value);
	}
}

// Sets the integer header with the name and its value.
void HttpServletResponseImpl::setIntHeader(String name, int value){
	setHeader(name, std::to_string(value));
}

// Sets the response status code.
void HttpServletResponseImpl::setStatus(int sc){
	if (committed){
		throw IllegalOperationException("The response has been committed.");
	}
	status = sc;
}

// Writes headers.
void HttpServletResponseImpl::writeHeaders(){
	// Set up all required headers.
	if (keepAliveAllowed){
		if (getHeader("Transfer-Encoding") == "chunked"){
			// It can be keep-alive in chunked mode.
		}
		else if (!containsHeader("Content-Length")){
			// The content length does not exists. It cannot keep alive.
			keepAliveAllowed = false;
		}
	}
	if (keepAliveAllowed){
		setHeader("Connection", "keep-alive");
	}
	else{
		setHeader("Connection", "close");
	}
	// In Firefox there is a program that if Content-Length is 0, Firefox will keep waiting.
	if (headerMap["Content-Length"].front() == "0"){
		// Add a header to solve Firefox's program.
		headerMap["Cache-Control"].push_back("no-cache");
	}
	// Build and send the first line.
	String explain = getStatusExplaination();
	if (explain.empty()){
		// Cannot find the explaination.
		throw IllegalOperationException("Unknown status code " + status);
	}
	// Now we can make it committed
	committed = true;
	socketOutput << "HTTP/1.1 " << std::to_string(status) << " " << explain << "\n";
	// Write headers
	for (auto& pair : headerMap){
		for (auto& val : pair.second){
			socketOutput << pair.first << ": " << val << "\r\n";
		}
	}
	// Write an extra line and flush.
	socketOutput << "\r\n";
	socketOutput.flush();
}

// Returns the status explaination.
HttpServletResponseImpl::String HttpServletResponseImpl::getStatusExplaination(){
	static std::map<int, String> map;
	if (map.empty()){
		// Build the map.
		map[200] = "OK";  map[201] = "Created"; map[202] = "Accepted";
		map[203] = "Non-Authoritative Information";   map[204] = "No Content";
		map[205] = "Reset Content";   map[206] = "Partial Content";
		map[207] = "Multi-Status";    map[208] = "Already Reported";
		map[300] = "Multiple Choices";    map[301] = "Moved Permanently";
		map[302] = "Found";   map[303] = "See Other";   map[304] = "Not Modified";
		map[305] = "Use Proxy";   map[306] = "Switch Proxy";
		map[307] = "Temporary Redirect";  map[308] = "Permanent Redirect";
		map[400] = "Bad Request"; map[401] = "Unauthorized";
		map[402] = "Payment Required";    map[403] = "Forbidden";
		map[404] = "Not Found";   map[405] = "Method Not Allowed";
		map[406] = "Not Acceptable";  map[407] = "Proxy Authentication Required";
		map[408] = "Request Timeout"; map[409] = "Conflict";
		map[410] = "Gone";    map[411] = "Length Required";
		map[412] = "Precondition Failed"; map[413] = "Request Entity Too Large";
		map[414] = "Request-URI Too Long";
		//...
		map[500] = "Internal Server Error";   map[501] = "Not Implemented";
		map[502] = "Bad Gateway"; map[503] = "Service Unavailable";
		map[504] = "Gateway Timeout"; map[505] = "HTTP Version Not Supported";
		map[506] = "Variant Also Negotiates"; map[507] = "Insufficient Storage";
		map[508] = "Loop Detected";   map[509] = "Bandwidth Limit Exceeded";
		map[510] = "Not Extended";    map[511] = "Network Authentication Required";
		map[550] = "Permission denied";
	}
	if (map.find(status) != map.end()){
		return map[status];
	}
	return "";
}

#ifdef TEST_HTTPSERVERSUPPORT

#include <iostream>
#include <sstream>
using namespace std;

// Check whether the two value are the same.
template <typename T>
void assertEquals(T actual, T expected){
	if(actual!=expected){
		cout<<"Expect "<<expected<<", but got "<<actual<<endl;;
	}
}

// Check whether the bool value is true. If not, prints message.
void assertTrue(bool b, string msg){
	if(!b){
		cout<<"Expect true, but got false because "<<msg<<endl;;
	}
}

// Check whether the string contains another string.
void assertContains(string str, string contained){
	if(str.find(contained)==string::npos){
		cout<<"Cannot find \""<<contained<<"\" in the string.\n";
	}
}

// Check whether the string not contains another string.
void assertNotContains(string str, string contained){
	if(str.find(contained)!=string::npos){
		cout<<"Should not contains: \""<<contained<<"\"\n";
	}
}

// Notify that this code should not be run.
void failed(string str){
	cout<<"Should not be here after: "<<str<<endl;
}

// second part test
void testHttpServletRequestImpl2(HttpServletRequestImpl& request){
	// Testing getHeaderNames()
	vector<string> vec=request.getHeaderNames();
	assertTrue(find(vec.begin(), vec.end(), "h1")!=vec.end(), "Cannot find h1");
	assertTrue(find(vec.begin(), vec.end(), "h2")!=vec.end(), "Cannot find h2");
	assertTrue(find(vec.begin(), vec.end(), "Content-Type")!=vec.end(), "Cannot find Content-Type");
	assertTrue(find(vec.begin(), vec.end(), "Content-Length")!=vec.end(), "Cannot find Content-Length");
	// Testing getIntHeader()
	assertEquals(request.getIntHeader("ih"), -1);
	request.setHeader("ih", "xxx");
	assertEquals(request.getIntHeader("ih"), 0);
	request.setHeader("ih", "0");
	assertEquals(request.getIntHeader("ih"), 0);
	request.setHeader("ih", "11");
	assertEquals(request.getIntHeader("ih"), 11);
	// Testing addParameter(), getParameter()
	request.addParameter("p1", "v1-1");
	request.addParameter("p1", "v1-2");
	assertEquals(request.getParameter("p1"), string("v1-1"));
	// Testing getParameterNames()
	request.addParameter("p2", "v2");
	vec=request.getParameterNames();
	assertTrue(find(vec.begin(), vec.end(), "p1")!=vec.end(), "Cannot find p1");
	assertTrue(find(vec.begin(), vec.end(), "p2")!=vec.end(), "Cannot find p2");
	cout<<"If nothing was printted, the test was passed.\n\n";
}

// first part test
void testHttpServletRequestImpl(){
	cout<<"/*** Testing HttpServletRequestImpl ***/\n";
	istringstream input("My input contents");
	HttpServletRequestImpl request=HttpServletRequestImpl(input);
	request.addHeader("h1", "v1");
	request.setMethod("POST");
	assertEquals(request.getMethod(), string("POST"));
	request.setQueryString("theQueryString");
	assertEquals(request.getQueryString(), string("theQueryString"));
	request.setRequestUrl("theRequestUrl");
	assertEquals(request.getRequestUrl(), string("theRequestUrl"));
	// Testing setHeader(), getHeader()
	request.addHeader("h2", "v2-1");
	request.addHeader("h2", "v2-2");
	assertEquals(request.getHeader("h2"), string("v2-1"));
	request.setHeader("h2", "v2-final");
	assertEquals(request.getHeader("h2"), string("v2-final"));
	// Testing getCharacterEncoding()
	request.setHeader("Content-Type", "text/plain; charset=utf-8");
	string charEnco=request.getCharacterEncoding();
	assertEquals(charEnco, string("utf-8"));
	// Testing getContentLength()
	assertEquals(request.getContentLength(), -1);
	request.setHeader("Content-Length", to_string(0));
	assertEquals(request.getContentLength(), 0);
	request.setHeader("Content-Length", to_string(100));
	assertEquals(request.getContentLength(), 100);
	testHttpServletRequestImpl2(request);
}

// test throwing exception part 2
void testCommittedLock2(ostringstream*& pOut, HttpServletResponseImpl*& pRes){
	try{
		pRes->setContentType("text/plain; charset=utf-8");
		failed("setContentType()");
	}catch(IllegalOperationException&){    }
	try{
		pRes->setHeader("h2", "v2");
		failed("setHeader()");
	}catch(IllegalOperationException&){    }
	try{
		pRes->setIntHeader("h3", 3);
		failed("setIntHeader()");
	}catch(IllegalOperationException&){    }
	try{
		pRes->setStatus(404);
		failed("setStatus()");
	}catch(IllegalOperationException&){    }
	try{
		// Should not throw exceptions.
		pRes->resetBuffer();
		pRes->isKeepAliveAllowed();
		pRes->containsHeader("aa");
		pRes->flushBuffer();
		pRes->getBufferSize();
		pRes->getCharacterEncoding();
		pRes->getContentType();
		pRes->getHeader("aa");
		pRes->getHeaderNames();
		pRes->getHeaders("bb");
		pRes->getOutputStream();
		pRes->getStatus();
		pRes->isCommitted();
		pRes->setBufferSize(100);
	}catch(IllegalOperationException&){
		failed("Should not throw exceptions.");
	}
	delete pRes;
	delete pOut;
}

// test throwing exception part 1
void testCommittedLock(){
	// Testing committed lock
	ostringstream* pOut=new ostringstream();
	HttpServletResponseImpl* pRes=new HttpServletResponseImpl(*pOut);
	pRes->flushBuffer();
	assertTrue(pRes->isCommitted(), "Should be committed.");
	try{
		pRes->setKeepAliveSupported(true);
		failed("setKeepAliveSupported()");
	}catch(IllegalOperationException&){  }
	try{
		pRes->addHeader("h1", "v1");
		failed("addHeader()");
	}catch(IllegalOperationException&){    }
	try{
		pRes->addIntHeader("h1", 1);
		failed("addIntHeader()");
	}catch(IllegalOperationException&){    }
	try{
		pRes->reset();
		failed("reset()");
	}catch(IllegalOperationException&){    }
	try{
		pRes->sendError(404);
		failed("sendError()");
	}catch(IllegalOperationException&){    }
	try{
		pRes->sendErrorWithMessage(404, "msg");
		failed("sendErrorWithMessage()");
	}catch(IllegalOperationException&){    }
	try{
		pRes->setCharacterEncoding("utf-8");
		failed("setCharacterEncoding()");
	}catch(IllegalOperationException&){    }
	try{
		pRes->setContentLength(1);
		failed("setContentLength()");
	}catch(IllegalOperationException&){    }
	testCommittedLock2(pOut, pRes);
}

// test HttpServletResponseImpl part3
void testHttpServletResponseImpl3(){
	// Testing sendError(), sendErrorWithMessage()
	ostringstream* pOut=new ostringstream();
	HttpServletResponseImpl* pRes=new HttpServletResponseImpl(*pOut);
	pRes->sendErrorWithMessage(404, "error msg");
	assertTrue(pRes->isCommitted(), "Should be committed");
	pRes->flushBuffer();
	string ret=pOut->str();
	assertContains(ret, "HTTP/1.1 404 Not Found\n");
	assertContains(ret, "Content-Length:");
	assertContains(ret, "error msg");
	delete pRes;
	delete pOut;
	// Testing setContentLength() with output
	pOut=new ostringstream();
	pRes=new HttpServletResponseImpl(*pOut);
	pRes->setContentLength(5);
	pRes->getOutputStream()<<"1234";// Should be OK.
	pRes->flushBuffer();
	try{
		pRes->getOutputStream()<<"567"; // Should throw exception here or below.
		pRes->flushBuffer();
		failed("flushBuffer() for testing setContentLength()");
	}catch(IllegalOperationException&){
	}
	delete pRes;
	delete pOut;
	// Testing setKeepAliveSupported(), isKeepAliveAllowed()
	pOut=new ostringstream();
	pRes=new HttpServletResponseImpl(*pOut);
	assertTrue(!pRes->isKeepAliveAllowed(), "Default Keep-Alive should be false.");
	pRes->setKeepAliveSupported(true);
	pRes->flushBuffer(); // Should not allow Keey-Alive because no content length.
	assertTrue(!pRes->isKeepAliveAllowed(), "Should not allow Keep-Alive because of no content length.");
	delete pOut;
	delete pRes;
	pOut=new ostringstream();
	pRes=new HttpServletResponseImpl(*pOut);
	pRes->setKeepAliveSupported(true);
	pRes->setContentLength(0);
	pRes->flushBuffer(); // Should allow Keey-Alive.
	assertTrue(pRes->isKeepAliveAllowed(), "Should allow Keep-Alive");
	delete pOut;
	delete pRes;
}

// test testHttpServletResponseImpl part 2
void testHttpServletResponseImpl2(){
	// Testing flushBuffer()
	ostringstream* pOut=new ostringstream();
	HttpServletResponseImpl* pRes=new HttpServletResponseImpl(*pOut);
	pRes->setStatus(201);
	pRes->flushBuffer(); // flush headers only
	string ret=pOut->str();
	size_t len=ret.length();
	assertContains(ret, "HTTP/1.1 201 Created\n");
	pRes->flushBuffer(); // flush no more
	pRes->flushBuffer();
	ret=pOut->str();
	assertEquals(ret.length(), len);
	pRes->getOutputStream()<<"This is response body.\n";
	pRes->flushBuffer(); // flush body
	ret=pOut->str();
	assertContains(ret, "\nThis is response body.\n");
	delete pRes;
	delete pOut;
	// Testing committed lock
	testCommittedLock();
	// Testing reset(), resetBuffer()
	pOut=new ostringstream();
	pRes=new HttpServletResponseImpl(*pOut);
	pRes->setStatus(202);
	pRes->addHeader("h5", "v5");
	pRes->getOutputStream()<<"XXXXXX";
	pRes->setContentLength(1);
	pRes->reset();
	pRes->getOutputStream()<<"YYYYYY";
	pRes->resetBuffer();
	pRes->getOutputStream()<<"ZZZZZZ";
	pRes->flushBuffer();
	ret=pOut->str();
	assertNotContains(ret, "XXXXXX");
	assertNotContains(ret, "h5");
	assertNotContains(ret, "v5");
	assertNotContains(ret, "Content-Length:");
	assertNotContains(ret, "YYYYYY");
	assertContains(ret, "ZZZZZZ");
	delete pRes;
	delete pOut;
}

// test testHttpServletResponseImpl part 1-1
void testHttpServletResponseImpl1_1(HttpServletResponseImpl& res){
	// Testing contiansHeader()
	assertTrue(!res.containsHeader("h4"), "Where does it come?");
	res.addHeader("h4", "v4");
	assertTrue(res.containsHeader("h4"), "Cannot find h4");
	// Testing getContentType(), setContentType()
	res.setContentType("text/plain; charset=utf-8");
	assertEquals(res.getContentType(), string("text/plain; charset=utf-8"));
	// Testing getCharacterEncoding(), setCharacterEncoding()
	res.setHeader("Content-Type", "text/plain; charset=utf-8");
	string charEnco=res.getCharacterEncoding();
	assertEquals(charEnco, string("utf-8"));
	res.setCharacterEncoding("gbk");
	assertEquals(res.getCharacterEncoding(), string("gbk"));
	assertEquals(res.getContentType(), string("text/plain; charset=gbk"));
	// Testing getContentLength()
	assertEquals(res.getHeader("Content-Length"), string(""));
	res.setHeader("Content-Length", to_string(0));
	assertEquals(res.getHeader("Content-Length"), string("0"));
	res.setHeader("Content-Length", to_string(100));
	assertEquals(res.getHeader("Content-Length"), string("100"));
	// Testing getStatus(), setStatus()
	assertEquals(res.getStatus(), 200);
	res.setStatus(404);
	assertEquals(res.getStatus(), 404);
}

// test HttpServletResponseImpl part 1
void testHttpServletResponseImpl1(){
	ostringstream mockSocOut;
	HttpServletResponseImpl res(mockSocOut);
	// Testing addHeader(), getHeader(), getHeaderNames(), setHeader()
	// and getHeaders()
	res.addHeader("h1", "v1");
	res.addHeader("h2", "v2-1");
	res.addHeader("h2", "v2-2");
	res.addHeader("h3", "v3-1");
	res.setHeader("h3", "v3");
	assertEquals(res.getHeader("h1"), string("v1"));
	assertEquals(res.getHeader("h2"), string("v2-1"));
	assertEquals(res.getHeader("h3"), string("v3"));
	vector<string> vec=res.getHeaderNames();
	assertTrue(find(vec.begin(), vec.end(), "h1")!=vec.end(), "Cannot find h1");
	assertTrue(find(vec.begin(), vec.end(), "h2")!=vec.end(), "Cannot find h2");
	assertTrue(find(vec.begin(), vec.end(), "h3")!=vec.end(), "Cannot find h3");
	vec=res.getHeaders("h2");
	assertTrue(find(vec.begin(), vec.end(), "v2-1")!=vec.end(), "Cannot find v2-1");
	assertTrue(find(vec.begin(), vec.end(), "v2-2")!=vec.end(), "Cannot find v2-2");
	// Testing addIntHeader(), setIntHeader()
	res.addIntHeader("i1", 0);
	assertEquals(res.getHeader("i1"), string("0"));
	res.setIntHeader("i1", 11);
	assertEquals(res.getHeader("i1"), string("11"));
	testHttpServletResponseImpl1_1(res);
}

// test HttpServletResponseImpl
void testHttpServletResponseImpl(){
	cout<<"/*** Testing HttpServletResponseImpl ***/\n";
	testHttpServletResponseImpl1();
	testHttpServletResponseImpl2();
	testHttpServletResponseImpl3();
	// Testing notifyOutputFinished()
	ostringstream* pOut=new ostringstream();
	HttpServletResponseImpl* pRes=new HttpServletResponseImpl(*pOut);
	pRes->setKeepAliveSupported(true);
	pRes->getOutputStream()<<"123456789";
	pRes->notifyOutputFinished(); // it can calculate content-length for us and keep connection alive.
	assertTrue(pRes->isKeepAliveAllowed(), "Keep-alive should be allowed.");
	delete pOut;
	delete pRes;
	pOut=new ostringstream();
	pRes=new HttpServletResponseImpl(*pOut);
	pRes->setKeepAliveSupported(true);
	pRes->getOutputStream()<<"12345";
	pRes->flushBuffer();
	pRes->getOutputStream()<<"6789";
	pRes->notifyOutputFinished(); // it can not calculate content-length because it has been flushed.
	assertTrue(!pRes->isKeepAliveAllowed(), "Keep-alive should be not allowed.");
	delete pOut;
	delete pRes;
	// TODO test chunked
	// END
	cout<<"If nothing was printted, the test was passed.\n\n";
}

void main(){
	testHttpServletRequestImpl();

	testHttpServletResponseImpl();
}
#endif
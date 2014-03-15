#pragma once

#include <string>
#include <vector>
#include <map>

/////////////////////////////////////////////////////////////////////////
// An interface for servlets to handle request.
class IHttpServletRequest {
public:
	typedef std::string String;
	typedef std::vector<String> Vector;
	typedef std::map<String, Vector> Map;
	// Destructor.
	virtual ~IHttpServletRequest() {}
	// Returns character encoding in the "Content-Type" header such as
	// "iso-8859-1" and "utf-8".
	virtual String getCharacterEncoding() = 0;
	// Returns the length of request body excluding headers. Returns -1 
	// if not exists.
	virtual int getContentLength() = 0;
	// Returns the header value of the name. Returns an empty string if 
	// no such header. Returns the first value if it has more than one 
	// values.
	virtual String getHeader(String name) = 0;
	// Returns all header names in the request.
	virtual Vector getHeaderNames() = 0;
	// Returns an istream for reading the request body.
	virtual std::istream& getInputStream() = 0;
	// Returns the integer value of the specific name. Returns -1 if the
	// header does not exist. Return 0 if the value is zero or not a 
	// number.
	virtual int getIntHeader(String name) = 0;
	// Returns HTTP method of the request such as "GET" and "POST".
	virtual String getMethod() = 0;
	// Returns the parameter of the name. For "GET" method, parameters
	// are in the first line of HTTP request after the token "?". For
	// "POST" method, parameters are in the request body.
	virtual String getParameter(String name) = 0;
	// Returns the parameter map. For "GET" method, parameters are in the
	// first line of HTTP request after the token "?". For "POST" method,
	// parameters are in the request body.
	virtual Map getParameterMap() = 0;
	// Returns the parameter names. For "GET" method, parameters are in
	// the first line of HTTP request after the token "?". For "POST"
	// method, parameters are in the request body.
	virtual Vector getParameterNames() = 0;
	// Returns the query string in first line of HTTP request after the
	// token "?". It is like "n1=v1&n2=v2&t3".
	virtual String getQueryString() = 0;
	// Returns the request url in first line of HTTP request before the
	// token "?". Returns "/" at least.
	virtual String getRequestUrl() = 0;
};


/////////////////////////////////////////////////////////////////////////
// An interface for servlets to handle response.
class IHttpServletResponse {
public:
	typedef std::string String;
	typedef std::vector<String> Vector;
	typedef std::map<String, Vector> Map;
	// Destructor.
	virtual ~IHttpServletResponse() {}
	// Adds a header with the name and the value.
	virtual void addHeader(String name, String value) = 0;
	// Adds an integer value of the name.
	virtual void addIntHeader(String name, int value) = 0;
	// Returns true if the response contains the header.
	virtual bool containsHeader(String name) = 0;
	// Writes the data in the buffer to the client. This will make
	// response committed.
	virtual void flushBuffer() = 0;
	// Returns the buffer size.
	virtual int getBufferSize() = 0;
	// Returns the character encoding in "Content-Type" header.
	virtual String getCharacterEncoding() = 0;
	// Returns the value of the "Content-Type" header.
	virtual String getContentType() = 0;
	// Returns the value of the specific header name.
	virtual String getHeader(String name) = 0;
	// Returns all header names.
	virtual Vector getHeaderNames() = 0;
	// Returns all values of the specific header.
	virtual Vector getHeaders(String name) = 0;
	// Returns an ostream to write data to the client.
	virtual std::ostream& getOutputStream() = 0;
	// Returns the HTTP response status code.
	virtual int getStatus() = 0;
	// Returns true if the headers has been written to the client.
	virtual bool isCommitted() = 0;
	// Resets status, all headers and buffer. It must be called before
	// committed.
	virtual void reset() = 0;
	// Resets buffer. It must be called before committed.
	virtual void resetBuffer() = 0;
	// Sends the response error with the specific statusCode. It will be 
	// committed after using this function.
	virtual void sendError(int statusCode) = 0;
	// Sends the response error with the specific statusCode and message.
	// It will be committed after using this function.
	virtual void sendErrorWithMessage(int statusCode, String message) = 0;
	// Sets the preferred buffer size. 
	virtual void setBufferSize(int size) = 0;
	// Sets the character encoding in the "Content-Type" header.
	virtual void setCharacterEncoding(String charset) = 0;
	// Sets the Content-Length header.
	virtual void setContentLength(int len) = 0;
	// Sets the ContentType header.
	virtual void setContentType(String type) = 0;
	// Sets the header with the name and its value.
	virtual void setHeader(String name, String value) = 0;
	// Sets the integer header with the name and its value.
	virtual void setIntHeader(String name, int value) = 0;
	// Sets the response status code.
	virtual void setStatus(int sc) = 0;
};

/////////////////////////////////////////////////////////////////////////
// An interface to handle each HTTP request.
class IHttpServlet{
public:
	typedef std::string String;
	// virtual destructor
	virtual ~IHttpServlet() {}
	// Do the HTTP method.
	virtual void doMethod(IHttpServletRequest& request, IHttpServletResponse& response) = 0;
};

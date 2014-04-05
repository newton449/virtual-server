#pragma once

#include <string>
#include <vector>
#include <map>

// An exception, thrown if a function should not be called. For example, calling reset(), reset(),
// sendError() and set headers after commited.
class IllegalOperationException;


// An interface for servlets to handle request. It will be passed to servlet's doMethod() function.
class IHttpServletRequest {
public:
	typedef std::string String;
	typedef std::vector<String> Vector;
	typedef std::map<String, Vector> Map;
	// Destructor.
	virtual ~IHttpServletRequest() {}
	// Returns character encoding in the "Content-Type" header such as "iso-8859-1" and "utf-8". If
	// no such header, returns an empty string.
	virtual String getCharacterEncoding() = 0;
	// Returns the length of request body excluding headers. Returns -1 if not exists.
	virtual int getContentLength() = 0;
	// Returns the header value of the name. If no such header, returns an empty string. If it has
	// more than one values, returns the first value.
	virtual String getHeader(String name) = 0;
	// Returns all header names in the request.
	virtual Vector getHeaderNames() = 0;
	// Returns an istream for reading the request body. Do not close the stream.
	virtual std::istream& getInputStream() = 0;
	// Returns the integer value of the specific name. Returns -1 if the header does not exist.
	// Return 0 if the value is zero or not a number.
	virtual int getIntHeader(String name) = 0;
	// Returns HTTP method of the request such as "GET" and "POST".
	virtual String getMethod() = 0;
	// Returns the parameter of the name. For "GET" method, parameters are in the first line of HTTP
	// request after the token "?". For "POST" method, parameters are in the request body. For other
	// methods, parameters will not be analyzed.
	virtual String getParameter(String name) = 0;
	// Returns the parameter map. For "GET" method, parameters are in the first line of HTTP request
	// after the token "?". For "POST" method, parameters are in the request body. For other
	// methods, parameters will not be analyzed.
	virtual Map getParameterMap() = 0;
	// Returns the parameter names. For "GET" method, parameters are in the first line of HTTP
	// request after the token "?". For "POST" method, parameters are in the request body. For other
	// methods, parameters will not be analyzed.
	virtual Vector getParameterNames() = 0;
	// Returns the query string in first line of HTTP request after the token "?". For example, "n1=v1&n2=v2&t3".
	virtual String getQueryString() = 0;
	// Returns the request url in first line of HTTP request before the token "?". Returns "/" at least.
	virtual String getRequestUrl() = 0;
};

/////////////////////////////////////////////////////////////////////////
// An interface for servlets to handle response. It will be passed to
// servlet's doMethod() function.
class IHttpServletResponse {
public:
	typedef std::string String;
	typedef std::vector<String> Vector;
	typedef std::map<String, Vector> Map;
	// Destructor.
	virtual ~IHttpServletResponse() {}
	// Adds a header with the name and the value. It supports multiple values for the same header.To
	// set one value only, use setHeader().
	virtual void addHeader(String name, String value) = 0;
	// Adds an integer value of the name. It supports multiple values for the same header. To set
	// one value only, use setIntHeader().
	virtual void addIntHeader(String name, int value) = 0;
	// Returns true if the response contains the header.
	virtual bool containsHeader(String name) = 0;
	// Writes the data in the buffer to the client. This will make response committed. Once
	// committed, headers will be sent to client, and client cannot get final content length in the
	// header. This function also will be called automatically when the buffer is full.
	virtual void flushBuffer() = 0;
	// Returns the buffer size. The output data will be stored in the buffer until it is full or
	// flushBuffer() is called.
	virtual int getBufferSize() = 0;
	// Returns the character encoding in "Content-Type" header. If no such header, returns empty string.
	virtual String getCharacterEncoding() = 0;
	// Returns the value of the "Content-Type" header. If no such header, returns empty string.
	virtual String getContentType() = 0;
	// Returns the value of the specific header name. If no such header, returns empty string.
	virtual String getHeader(String name) = 0;
	// Returns all header names.
	virtual Vector getHeaderNames() = 0;
	// Returns all values of the specific header. If no such header, returns empty vector.
	virtual Vector getHeaders(String name) = 0;
	// Returns an ostream to write data to the client. The output data will be stored in the buffer
	// until it is full or flushBuffer() is called. It is able to reset() or resetBuffer() before
	// sending data to clients.
	virtual std::ostream& getOutputStream() = 0;
	// Returns the HTTP response status code. The default value is 200.
	virtual int getStatus() = 0;
	// Returns true if the headers has been written to the client. Once committed, headers will be
	// sent to client, and client cannot get final content length in the header.
	virtual bool isCommitted() = 0;
	// Resets status, all headers and buffer. It must be called before committed, otherwise
	// IllegalOperationException will be thrown.
	virtual void reset() = 0;
	// Resets buffer. It must be called before committed, otherwise IllegalOperationException will
	// be thrown.
	virtual void resetBuffer() = 0;
	// Sends the response error with the specific statusCode. The server will send an error page for
	// it. It will be committed after using this function. It must be called before committed,
	// otherwise IllegalOperationException will be thrown.
	virtual void sendError(int statusCode) = 0;
	// Sends the response error with the specific statusCode and message. The server will send an
	// error page for it. It will be committed after using this function. It must be called before
	// committed, otherwise IllegalOperationException will be thrown.
	virtual void sendErrorWithMessage(int statusCode, String message) = 0;
	// Sets the preferred buffer size. If it is not supported or size is too large,
	// IllegalOperationException will be thrown.
	virtual void setBufferSize(int size) = 0;
	// Sets the character encoding in the "Content-Type" header. It must be called before committed,
	// otherwise IllegalOperationException will be thrown.
	virtual void setCharacterEncoding(String charset) = 0;
	// Sets the Content-Length header. It must be called before committed, otherwise
	// IllegalOperationException will be thrown.
	virtual void setContentLength(long len) = 0;
	// Sets the ContentType header. It must be called before committed, otherwise
	// IllegalOperationException will be thrown.
	virtual void setContentType(String type) = 0;
	// Sets the header with the name and its value. It will replace existing values. To add multiple
	// values, use addHeader(). It must be called before committed, otherwise
	// IllegalOperationException will be thrown.
	virtual void setHeader(String name, String value) = 0;
	// Sets the integer header with the name and its value. It will replace existing values. To add
	// multiple values, use addIntHeader(). It must be called before committed, otherwise
	// IllegalOperationException will be thrown.
	virtual void setIntHeader(String name, int value) = 0;
	// Sets the response status code. The server will not send an error page for it. It must be
	// called before committed, otherwise IllegalOperationException will be thrown.
	virtual void setStatus(int sc) = 0;
};


// An interface to handle each HTTP request.
class IHttpServlet{
public:
	typedef std::string String;
	// virtual destructor
	virtual ~IHttpServlet() {}
	// Do the HTTP method.
	virtual void doMethod(IHttpServletRequest& request, IHttpServletResponse& response) = 0;
};

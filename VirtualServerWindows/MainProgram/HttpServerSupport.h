#ifndef HTTPSERVERSUPPORT_H
#define HTTPSERVERSUPPORT_H

/////////////////////////////////////////////////////////////////////
//  HttpServerSupport.h - provides some classes for HttpServer.    //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2012                                 //
//  Platform:      Windows 8                                       //
//  Application:   CSE687 Pr3, Spring 2013                         //
//  Author:        Sheng Wang                                      //
/////////////////////////////////////////////////////////////////////
/*
Module Operations: 
==================
This module provides some classes for HttpServer. It provides
IHttpServletRequest for servlets to get requests and provides
IHttpServletResponse for servlets to get responses. The server will 
create them and pass them to the servlets.

Main Class:
 - IHttpServletRequest : An interface for servlets to handle request.
 - IHttpServletResponse : An interface for servlets to handle response.

Other Class:
 - HttpServletRequestImpl : A class to store information of requests.
 - HttpServletResponseImpl : A class to store information of responses.
 - IllegalOperationException : thrown if the functions should not be called.

Public Interface:
=================
// Create instances.
HttpServletRequestImpl request;
HttpServletResponseImpl response;
// Add headers, parameters and so on
request.addHeader("h1", "v1");
request.addParameter("p1", "v1");
// Pass them to a servelt
IHttpServlet* pServlet=...
pServlet->doGet(request, resposne);

==============
Required files (all)
- HttpServerSupport.h, HttpServerSupport.cpp

Build commands
- devenv Test_HttpServerSupport.vcxproj /rebuild debug

Maintenance History:
====================
ver 1.0 : 4/15/2013
- first release

*/

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <istream>
#include <stdexcept>
#include "../interfaces/IHttpServlet.h"

/////////////////////////////////////////////////////////////////////////
// A class to store information of requests.
class HttpServletRequestImpl : public IHttpServletRequest{
public:
    /********************* new functions *******************************/
    // Constructor with the istream.
    explicit HttpServletRequestImpl(std::istream& input);
    // Add a header with the name and the value.
    void addHeader(String name, String value);
    // Set HTTP method.
    void setMethod(String method);
    // Add a parameter with the name and value.
    void addParameter(String name, String value);
    // Set a header with the name and the value.
    void setHeader(String name, String value);
    // Set the query string.
    void setQueryString(String str);
    // Set the request url.
    void setRequestUrl(String url);
    /********************* overrided functions *************************/
    // Returns character encoding in the "Content-Type" header such as
    // "iso-8859-1" and "utf-8".
    String getCharacterEncoding();
    // Returns the length of request body excluding headers. Returns -1 
    // if not exists.
    int getContentLength();
    // Returns the header value of the name. Returns an empty string if 
    // no such header. Returns the first value if it has more than one 
    // values.
    String getHeader(String name);
    // Returns all header names in the request.
    Vector getHeaderNames();
    // Returns an istream for reading the request body.
    std::istream& getInputStream();
    // Returns the integer value of the specific name. Returns -1 if the
    // header does not exist. Return 0 if the value is zero or not a 
    // number.
    int getIntHeader(String name);
    // Returns HTTP method of the request such as "GET" and "POST".
    String getMethod();
    // Returns the parameter of the name. For "GET" method, parameters
    // are in the first line of HTTP request after the token "?". For
    // "POST" method, parameters are in the request body.
    String getParameter(String name);
    // Returns the parameter map. For "GET" method, parameters are in the
    // first line of HTTP request after the token "?". For "POST" method,
    // parameters are in the request body.
    Map getParameterMap();
    // Returns the parameter names. For "GET" method, parameters are in
    // the first line of HTTP request after the token "?". For "POST"
    // method, parameters are in the request body.
    Vector getParameterNames();
    // Returns the query string in first line of HTTP request after the
    // token "?". It is like "n1=v1&n2=v2&t3".
    String getQueryString();
    // Returns the request url in first line of HTTP request before the
    // token "?". Returns "/" at least.
    String getRequestUrl();
private:
    std::istream& input;
    String httpMethod;
    String requestUrl;
    String queryString;
    Map headerMap;
    Map paramMap;
};

/////////////////////////////////////////////////////////////////////////
// A class to store information of responses.
class HttpServletResponseImpl : public IHttpServletResponse{
public:
    // Constructor.
    explicit HttpServletResponseImpl(std::ostream& socketOutput);
    // Returns true if the socketOutput can keep alive. It is meanless 
    // until the response is committed.
    bool isKeepAliveAllowed();
    // Tells that all headers and body contents are all set. The response
    // will try to set Content-Length if possible.
    void notifyOutputFinished();
    // Returns true if the client supports keep-alive.
    void setKeepAliveSupported(bool supported);
    /******************** overrided functions **************************/
    // Adds a header with the name and the value.
    void addHeader(String name, String value);
    // Adds an integer value of the name.
    void addIntHeader(String name, int value);
    // Returns true if the response contains the header.
    bool containsHeader(String name);
    // Writes the data in the buffer to the client. This will make
    // response committed.
    void flushBuffer();
    // Returns the buffer size.
    int getBufferSize();
    // Returns the character encoding in "Content-Type" header.
    String getCharacterEncoding();
    // Returns the value of the "Content-Type" header.
    String getContentType();
    // Returns the value of the specific header name.
    String getHeader(String name);
    // Returns all header names.
    Vector getHeaderNames();
    // Returns all values of the specific header.
    Vector getHeaders(String name);
    // Returns an ostream to write data to the client.
    std::ostream& getOutputStream();
    // Returns the HTTP response status code.
    int getStatus();
    // Returns true if the headers has been written to the client.
    bool isCommitted();
    // Resets status, all headers and buffer. It must be called before
    // committed.
    void reset();
    // Resets buffer. It must be called before committed.
    void resetBuffer();
    // Sends the response error with the specific statusCode. It will be 
    // committed after using this function.
    void sendError(int statusCode);
    // Sends the response error with the specific statusCode and message.
    // It will be committed after using this function.
    void sendErrorWithMessage(int statusCode, String message);
    // Sets the preferred buffer size. 
    void setBufferSize(int size);
    // Sets the character encoding in the "Content-Type" header.
    void setCharacterEncoding(String charset);
    // Sets the Content-Length header.
    void setContentLength(int len);
    // Sets the ContentType header.
    void setContentType(String type);
    // Sets the header with the name and its value.
    void setHeader(String name, String value);
    // Sets the integer header with the name and its value.
    void setIntHeader(String name, int value);
    // Sets the response status code.
    void setStatus(int sc);
private:
    Map headerMap;
    std::ostream& socketOutput;
    std::ostringstream bufOutput;
    // The expected length of bytes to be sent.
    int expectedBytesLength;
    int bufferSize;
    int status; // defaut 200
    bool committed; // true if headers has been written
    bool keepAliveAllowed;
    bool outputFinished;
    // Writes headers.
    void writeHeaders();
    // Returns the status explaination.
    String getStatusExplaination();
};

// In the ISO C++11 Standard, the noexcept operator is introduced, but support
// for this feature is not yet present in Visual C++.
#ifndef NOEXCEPT
#ifdef WIN32
#define NOEXCEPT throw()
#else
#define NOEXCEPT noexcept(true)
#endif
#endif

/////////////////////////////////////////////////////////////////////////
// An exception which is thrown when illegal arguments are passed to 
// request/resposne or functions are called in illegal status.
class IllegalOperationException : public std::logic_error{
public:
    // Constructor with message.
    explicit IllegalOperationException (const std::string& what_arg)
        : std::logic_error(what_arg){
    }
    // Constructor with message.
    explicit IllegalOperationException (const char* what_arg)
        : std::logic_error(what_arg){
    }
    // Destructor.
    virtual ~IllegalOperationException() NOEXCEPT{}
};

#endif
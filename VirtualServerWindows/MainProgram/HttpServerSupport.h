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
==============
- IHttpServletRequest : An interface for servlets to handle request.
- IHttpServletResponse : An interface for servlets to handle response.

Other Class:
==============
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

Required files (all)
==============
- HttpServerSupport.h, HttpServerSupport.cpp

Build commands
- devenv Test_HttpServerSupport.vcxproj /rebuild debug

Maintenance History:
====================
ver 1.0 : 4/15/2013
- first release

*/
#pragma once

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
    void addHeader(const String& name, const String& value);

    // Set HTTP method.
    void setMethod(const String& method);

    // Add a parameter with the name and value.
    void addParameter(const String& name, const String& value);

    // Set a header with the name and the value.
    void setHeader(const String& name, const String& value);

    // Set the query string.
    void setQueryString(const String& str);

    // Set the request url.
    void setRequestUrl(const String& url);

    /********** overrided functions (see comments of super functions)*********/

    // Returns character encoding in the "Content-Type" header.
    String getCharacterEncoding() const;

    // Returns the length of request body excluding headers.
    int getContentLength() const;

    // Returns the header value of the name.
    String getHeader(const String& name) const;

    // Returns all header names in the request.
    Vector getHeaderNames() const;

    // Returns an istream for reading the request body.
    std::istream& getInputStream() const;

    // Returns the integer value of the specific name.
    int getIntHeader(const String& name) const;

    // Returns HTTP method of the request such as "GET" and "POST".
    String getMethod() const;

    // Returns the parameter of the name.
    String getParameter(const String& name) const;

    // Returns the parameter map.
    Map getParameterMap() const;

    // Returns the parameter names.
    Vector getParameterNames() const;

    // Returns the query string in first line of HTTP request after the
    // token "?".
    String getQueryString() const;

    // Returns the request url in first line of HTTP request before the
    // token "?".
    String getRequestUrl() const;
private:
    // inputStream
    std::istream& input;

    // http method
    String httpMethod;

    // request url such as "/index.html"
    String requestUrl;

    // query string such as "h1=v1&h2=v2"
    String queryString;

    // header map
    Map headerMap;

    // parameter map
    Map paramMap;
};

// A class to store information of responses.
class HttpServletResponseImpl : public IHttpServletResponse{
public:
    // Constructor.
    explicit HttpServletResponseImpl(std::ostream& socketOutput);

    // Returns true if the socketOutput can keep alive. It is meanless until the
    // response is committed.
    bool isKeepAliveAllowed();

    // Tells that all headers and body contents are all set. The response
    // will try to set Content-Length if possible.
    void notifyOutputFinished();

    // Returns true if the client supports keep-alive.
    void setKeepAliveSupported(bool supported);

    /******************** overrided functions **************************/

    // Adds a header with the name and the value.
    void addHeader(const String& name, const String& value);

    // Adds an integer value of the name.
    void addIntHeader(const String& name, const int& value);

    // Returns true if the response contains the header.
    bool containsHeader(const String& name) const;

    // Writes the data in the buffer to the client. This will make response
    // committed.
    void flushBuffer();

    // Returns the buffer size.
    int getBufferSize() const;

    // Returns the character encoding in "Content-Type" header.
    String getCharacterEncoding() const;

    // Returns the value of the "Content-Type" header.
    String getContentType() const;

    // Returns the value of the specific header name.
    String getHeader(const String& name) const;

    // Returns all header names.
    Vector getHeaderNames() const;

    // Returns all values of the specific header.
    Vector getHeaders(const String& name) const;

    // Returns an ostream to write data to the client.
    std::ostream& getOutputStream() const;

    // Returns the HTTP response status code.
    int getStatus() const;

    // Returns true if the headers has been written to the client.
    bool isCommitted() const;

    // Resets status, all headers and buffer. It must be called before
    // committed.
    void reset();

    // Resets buffer. It must be called before committed.
    void resetBuffer();

    // Sends the response error with the specific statusCode. It will be
    // committed after using this function.
    void sendError(const int& statusCode);

    // Sends the response error with the specific statusCode and message.
    // It will be committed after using this function.
    void sendErrorWithMessage(const int& statusCode, const String& message);

    // Sets the preferred buffer size.
    void setBufferSize(const int& size);

    // Sets the character encoding in the "Content-Type" header.
    void setCharacterEncoding(const String& charset);

    // Sets the Content-Length header.
    void setContentLength(const long& len);

    // Sets the ContentType header.
    void setContentType(const String& type);

    // Sets the header with the name and its value.
    void setHeader(const String& name, const String& value);

    // Sets the integer header with the name and its value.
    void setIntHeader(const String& name, const int& value);

    // Sets the response status code.
    void setStatus(const int& sc);
private:
    // header map
    Map headerMap;

    // a ostream to write data to socket
    std::ostream& socketOutput;

    // a ostringstream for caching response body
    std::ostringstream bufOutput;

    // The expected length of bytes to be sent, i.e. content length of response
    // body.
    long expectedBytesLength;

    // buffer size for caching response body
    int bufferSize;

    // response status code. default value is 200.
    int status;

    // true if headers has been written
    bool committed;

    // true if the socketOutput can keep alive
    bool keepAliveAllowed;

    // true if the servlet has finished output.
    bool outputFinished;

    // Writes headers to socket.
    void writeHeaders();

    // Returns the status explaination.
    String getStatusExplaination();
};

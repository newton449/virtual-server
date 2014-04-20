///////////////////////////////////////////////////////////////////////////////
//  IHttpServlet.h - provide general interfaces to handle HTTP requests.     //
//  ver 0.9                                                                  //
//  Language:      Visual C++ 2013 & gcc 4.7.2                               //
//  Platform:      Windows 8       & Linux Debian 3.2 x86_x64                //
//  Application:   CSE775 Final Project, Spring 2014                         //
//  Author:        Sheng Wang, Qiuyong Yang, Bei Li                          //
///////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module provides general interfaces to handle HTTP requests. We use
"servlet" for an individual service which handle a HTTP request of some
specific business logic. A servlet shall implement IHttpServlet interface, and
provide callback implementations in doMethod() function. Two interfaces
"IHttpServletRequest" and "IHttpServletResponse" are used to access HTTP
requests and responses. The servelt can use provided functions of them for
request and resposne headers, and use std::istream of them for request and
response bodies.

The typicall usages are to create implementations of IHttpServlet, and provide
them to a http server or a servlet mapping object. When a HTTP request comes,
the doMethod() function of it will be called.

Main Class:
===========
- IHttpServlet: An interface to handle each HTTP request and send response.

Other Class:
============
- IHttpServletRequest: An interface for servlets to handle request.
- IHttpServletResponse: An interface for servlets to handle response.

Exceptions:
============
- IllegalOperationException: thrown if a function should not be called.

Maintenance History:
====================
ver 0.9 : 4/18/2013
- first commented

*/
#pragma once

#include <string>
#include <vector>
#include <map>

// An exception, thrown if a function should not be called. For example, in
// IHttpServletResponse calling reset(), reset(), sendError() and set headers
// after commited.
class IllegalOperationException;

// An interface for servlets to handle request. It will be passed to servlet's
// doMethod() function. Use most functions of it to retreive information of
// HTTP reqeust header. Use getInputStream() to retreive a std::istream to
// read request body.
// 
// This interface is NOT thread-safe guaranteed.
class IHttpServletRequest {
public:
    typedef std::string String;
    typedef std::vector<String> Vector;
    typedef std::map<String, Vector> Map;

    // Destructor.
    virtual ~IHttpServletRequest() {}

    // Returns character encoding in the "Content-Type" header such as
    // "iso-8859-1" and "utf-8". If no such header, returns an empty string.
    virtual String getCharacterEncoding() const = 0;

    // Returns the length of request body excluding headers. Returns -1 if not exists.
    virtual int getContentLength() const = 0;

    // Returns the header value of the name. If no such header, returns an empty
    // string. If it has more than one values, returns the first value.
    virtual String getHeader(const String& name) const = 0;

    // Returns all header names in the request.
    virtual Vector getHeaderNames() const = 0;

    // Returns an std::istream for reading the request body. It will be blocked
    // if no enough data is received.
    //
    // If it reaches the end of a request body, EOF will be set. If errors
    // including timeouts occur, BAD or FAIL will be set. Do not close the
    // stream.
    virtual std::istream& getInputStream() const = 0;

    // Returns the integer value of the specific name. Returns -1 if the header
    // does not exist. Return 0 if the value is zero or not a number.
    virtual int getIntHeader(const String& name) const = 0;

    // Returns HTTP method of the request such as "GET" and "POST".
    virtual String getMethod() const = 0;

    // Returns the parameter of the name. For "GET" method, parameters are in
    // the first line of HTTP request after the token "?". For "POST" method,
    // parameters are in the request body. For other methods, parameters will
    // not be analyzed.
    virtual String getParameter(const String& name) const = 0;

    // Returns the parameter map. For "GET" method, parameters are in the first
    // line of HTTP request after the token "?". For "POST" method, parameters
    // are in the request body. For other methods, parameters will not be
    // analyzed.
    virtual Map getParameterMap() const = 0;

    // Returns the parameter names. For "GET" method, parameters are in the
    // first line of HTTP request after the token "?". For "POST" method,
    // parameters are in the request body. For other methods, parameters will
    // not be analyzed.
    virtual Vector getParameterNames() const = 0;

    // Returns the query string in first line of HTTP request after the token
    // "?". For example, "n1=v1&n2=v2&t3".
    virtual String getQueryString() const = 0;

    // Returns the request url in first line of HTTP request before the token
    // "?". Returns "/" at least.
    virtual String getRequestUrl() const = 0;
};

// An interface for servlets to handle response. It will be passed to servlet's
// doMethod() function. Use most functions of it to set HTTP response header.
// Use getOutputStream() to retreive a std::ostream to write response body. If
// your servlet cannot handle the request, it can use sendError() or
// sendErrorWithMessage() to send a default error HTML page.
// 
// This interface is NOT thread-safe guaranteed.
class IHttpServletResponse {
public:
    typedef std::string String;
    typedef std::vector<String> Vector;
    typedef std::map<String, Vector> Map;

    // Destructor.
    virtual ~IHttpServletResponse() {}

    // Adds a header with the name and the value. It supports multiple values
    // for the same header. To set one value only, use setHeader().
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void addHeader(const String& name, const String& value) = 0;

    // Adds an integer value of the name. It supports multiple values for the
    // same header. To set one value only, use setIntHeader().
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void addIntHeader(const String& name, const int& value) = 0;

    // Returns true if the response contains the header.
    virtual bool containsHeader(const String& name) const = 0;

    // Writes the body data in the buffer to the client.
    //
    // This will make response committed. Once committed, headers will be sent
    // to client. As a result, HTTP server cannot decide the final content
    // length of response body automatically. The servlet can set content length
    // manually or use chunked transfer encoding, otherwise, HTTP server will
    // shutdown the socket output to indicate the end of response body. It just
    // affect performance.
    //
    // This function will also be called automatically when the buffer is full.
    virtual void flushBuffer() = 0;

    // Returns the buffer size. The output body data will be stored in the
    // buffer until it is full or flushBuffer() is called. See flushBuffer() for
    // more details.
    virtual int getBufferSize() const = 0;

    // Returns the character encoding in "Content-Type" header. If no such
    // header, returns empty string.
    virtual String getCharacterEncoding() const = 0;

    // Returns the value of the "Content-Type" header. If no such header,
    // returns empty string.
    virtual String getContentType() const = 0;

    // Returns the value of the specific header name. If no such header, returns
    // empty string.
    virtual String getHeader(const String& name) const = 0;

    // Returns all header names.
    virtual Vector getHeaderNames() const = 0;

    // Returns all values of the specific header. If no such header, returns
    // empty vector.
    virtual Vector getHeaders(const String& name) const = 0;

    // Returns an ostream to write body data to the client.
    //
    // The output data will be stored in the buffer until it is full or
    // flushBuffer() is called. It is able to reset() or resetBuffer() before
    // sending data to clients. See flushBuffer() for more details. Note: call
    // ostream.flush() will only flush data to the buffer instead of the socket.
    //
    // If the socket output is closed, EOF will be set. If errors occur, BAD or
    // FAIL will be set. Do not close the stream.
    virtual std::ostream& getOutputStream() const = 0;

    // Returns the HTTP response status code. The default value is 200.
    virtual int getStatus() const = 0;

    // Returns true if the headers has been written to the client. Once
    // committed, headers will be sent to client. See flushBuffer() for more
    // details.
    virtual bool isCommitted() const = 0;

    // Resets status, all headers and buffer.
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void reset() = 0;

    // Resets buffer. Clear response data in the buffer. See flushBuffer() for
    // more details.
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void resetBuffer() = 0;

    // Sends the response error with the specific statusCode. The server will
    // send an error page for it. It will be committed after using this
    // function. The servlet should not send body data when using this function.
    // If the servlet wants to send custom body data, use setStatus() instead.
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void sendError(const int& statusCode) = 0;

    // Sends the response error with the specific statusCode and message. The
    // server will send an error page for it. It will be committed after using
    // this function. The servlet should not send body data when using this
    // function. If the servlet wants to send custom body data, use setStatus()
    // instead.
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void sendErrorWithMessage(const int& statusCode, const String& message) = 0;

    // Sets the preferred buffer size. However, HTTP server may not accept the
    // size.
    //
    // If it is not supported or size is too large, IllegalOperationException
    // will be thrown.
    virtual void setBufferSize(const int& size) = 0;

    // Sets the character encoding in the "Content-Type" header.
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void setCharacterEncoding(const String& charset) = 0;

    // Sets the Content-Length header.
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void setContentLength(const long& len) = 0;

    // Sets the ContentType header.
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void setContentType(const String& type) = 0;

    // Sets the header with the name and its value. It will replace existing
    // values. To add multiple values, use addHeader().
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void setHeader(const String& name, const String& value) = 0;

    // Sets the integer header with the name and its value. It will replace
    // existing values. To add multiple values, use addIntHeader().
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void setIntHeader(const String& name, const int& value) = 0;

    // Sets the response status code. The server will not send an error page for
    // it.
    //
    // It must be called before committed, otherwise IllegalOperationException
    // will be thrown.
    virtual void setStatus(const int& sc) = 0;
};

// An interface to handle each HTTP request and send response.
//
// This interface is NOT thread-safe guaranteed.
class IHttpServlet{
public:
    typedef std::string String;

    // virtual destructor
    virtual ~IHttpServlet() {}

    // Do the HTTP method. See IHttpServletRequest and IHttpServletResponse for
    // more details.
    virtual void doMethod(IHttpServletRequest& request, IHttpServletResponse& response) = 0;
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


// An exception which is thrown when illegal arguments are passed to
// request/resposne or functions are called in illegal status.
//
// For example, a function of IHttpServletResponse may throw this exception if
// response's state cannot be committed.
class IllegalOperationException : public std::logic_error{
public:
    // Constructor with message.
    explicit IllegalOperationException(const std::string& what_arg)
        : std::logic_error(what_arg){
        }

    // Constructor with message.
    explicit IllegalOperationException(const char* what_arg)
        : std::logic_error(what_arg){
        }

    // Destructor.
    virtual ~IllegalOperationException() NOEXCEPT{}
};

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

/////////////////////////////////////////////////////////////////////
//  HttpServer.h - provides classes to set up a HTTP server.       //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2012                                 //
//  Platform:      Windows 8                                       //
//  Application:   CSE687 Pr3, Spring 2013                         //
//  Author:        Sheng Wang                                      //
/////////////////////////////////////////////////////////////////////
/*
Module Operations: 
==================
This module provides classes to set up a HTTP server. The server will 
run servlets to handle each HTTP request. The caller should provide 
implementations of servlets and return them according to the request
url. The servlet implementations can use IHttpServletRequest and 
IHttpServletResponse to handle the requests and send back responses.

Main Class:
 - HttpServer : the runnable HTTP server

Other Class:
 - IHttpServlet : An interface to handle each HTTP request.
 - DefaultHttpServlet : A default implementation of IHttpServlet.
 - IHttpServletMapping : An interface to provide servlets according to urls
 - RequestHandlerThread : A thread to handle each coming socket and execute servlets.

Public Interface:
=================
// Implement an IHttpServletMapping
IHttpServletMapping* pMapping=...
// Create and start the server
HttpServer server(*pMapping);
server.start();
// stop it
server.stop();
server.join();

==============
Required files (all)
- BlockingQueue.h, BlockingQueue.cpp
- Communicator.h, Communicator.cpp
- FileSystem.h, FileSystem.cpp
- HttpClienlets.h, HttpClienlets.cpp
- HttpClient.h, HttpServer.cpp
- locks.h, locks.cpp
- Logger.h, Logger.cpp
- Sockets.h, Sockets.cpp
- SocketStream.h, SocketStream.cpp
- StringUtils.h, StringUtils.cpp
- Threads.h, Threads.cpp
- Utlities.h, Utlities.cpp

Build commands
- devenv Test_HttpServer.vcxproj /rebuild debug

Maintenance History:
====================
ver 1.0 : 4/15/2013
- first release

*/

#include "../interfaces/IHttpServletMapping.h"
#include "HttpServerSupport.h"
#include "Sockets.h"
#include "Threads.h"
#include "BlockingQueue.h"
#include "SocketStream.h"
#include "Logger.h"
#include <mutex>

/////////////////////////////////////////////////////////////////////////
// A thread to handle each coming socket and execute servlets.
class RequestHandlerThread : public ThreadBase<DefaultTerminate> {
public:
    typedef std::string String;
    typedef std::vector<String> Vector;

    // Constructor with the socket queue, the url-socket mapping and the id of the thread.
    RequestHandlerThread(BlockingQueue<Socket*>& queue, IHttpServletMapping& mapping);
    virtual ~RequestHandlerThread(){}
    // Returns the socket handled by the thread.
    void closeCurrentSocket();
private:
    BlockingQueue<Socket*>& queue;
    IHttpServletMapping& mapping;
    Socket* pSocket;
    SocketInputStream* pInput;
    SocketOutputStream* pOutput;
    HttpServletRequestImpl* pRequest;
    HttpServletResponseImpl* pResponse;
    bool needCloseConnection; // decided by both request and response

    /************************* functions *******************************/
    // Run the thread.
    void run();
    // Handles one request.
    void handleOneRequest();
    // Returns the header contents. The caller should delete it.
    Vector* getHeaderContents();
    // Builds the request. Returns true if the request is built
    // successfully and should be passed into servlets.
	bool buildRequest(Vector& headerContents);
    // Parse something like "GET /index.html?a=b HTTP/1.1". It should be
    // the first line.
    bool analyzeFirstLine(String line);
    // Analyzes header names and values.
    bool analyzeHeaderNamesAndValues(Vector& line);
    // Gets an servlet and executes it.
    void executeServlet();
    // Splits the string according to the regular expression.
    //Vector regexSplit(String str, String regex);
};

/////////////////////////////////////////////////////////////////////////
// The HTTP runnable server.
class HttpServer : private ThreadBase<DefaultTerminate> {
public:
    // Constructor with the url-servlets mapping, the listened port and
    // the working thread count.
    explicit HttpServer(IHttpServletMapping& mapping, int port=80, int threadCount=5);

    // Desctructor.
    ~HttpServer();
    // Starts the server. It will try to bind the listened port. If
    // failed, it will throw an exception.
    void start();
    // Waits for the server to stop.
    void join();
    // Asks the server to stop. Use join() to wait for it.
    void stop();
    // Returns true if the server has been started.
    bool isStarted();
private:
    bool stopRequested;
    int port;
    SocketListener* pListener;
    BlockingQueue<Socket*> queue;
    IHttpServletMapping& mapping;
    std::vector<RequestHandlerThread*> threads;
    int threadCount;
    std::mutex lock;

    // Runs the thread.
    void run();
};
#endif
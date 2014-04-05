/////////////////////////////////////////////////////////////////////
//  HttpServer.cpp - provides classes to set up a HTTP server.     //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2012                                 //
//  Platform:      Windows 8                                       //
//  Application:   CSE687 Pr3, Spring 2013                         //
//  Author:        Sheng Wang                                      //
/////////////////////////////////////////////////////////////////////
/*
- update codes for merged doXXX functions such as doGet() and doPost().
- changed logging styles for new logging API.
- now it uses return value instead of exceptions for empty client stream.
*/

#include "HttpServer.h"
#include "Logger.h"
#include "StringUtils.h"


////////////////////////////////////////////////////////////////////////
// Function implementations of RequestHandlerThread

// Constructor with the socket queue, the url-socket mapping and the id of the thread.

RequestHandlerThread::RequestHandlerThread(BlockingQueue<Socket*>& queue, IHttpServletMapping& mapping, int id)
: queue(queue), mapping(mapping), pSocket(NULL), pInput(NULL), pOutput(NULL), pRequest(NULL), pResponse(NULL),
needCloseConnection(true), id(id) {
}

// Returns the socket handled by the thread.

Socket* RequestHandlerThread::getSocket() {
    return pSocket;
}

// Run the thread.

void RequestHandlerThread::run() {
    LOG(DEBUG) << "Starting a handler thread.";
    pSocket = queue.deQ();
    while (pSocket != NULL) {
        SocketSystem socketSystem;
        LOG(DEBUG) << "Got a socket from " << socketSystem.getRemoteIP(pSocket);

        // Get a socket from the queue
        pInput = new SocketInputStream(pSocket);
        pOutput = new SocketOutputStream(pSocket);
        handleOneRequest();
        delete pInput;
        delete pOutput;
        Socket* pTmp = pSocket; // prevent calling by others
        pSocket = NULL;
        delete pTmp;
        pSocket = queue.deQ();
    }
    LOG(DEBUG) << "Closing a handler thread.";
}

// Handles one request.

void RequestHandlerThread::handleOneRequest() {
    Vector* headerContents = NULL;
    try {
        while (!pSocket->error()) {
            pInput->setExpectedBytesLength(-1);
            pRequest = new HttpServletRequestImpl(*pInput);
            pResponse = new HttpServletResponseImpl(*pOutput);
            needCloseConnection = false;
            // TODO Read body for POST parameters
            headerContents = getHeaderContents();
            if (headerContents == NULL || headerContents->empty()) {
                LOG(TRACE) << "Got nothing from client socket.";
                needCloseConnection = true;
            }
            else {
                if (buildRequest(*headerContents)) {
                    if (pRequest->getMethod() == "GET"){
                        pInput->setExpectedBytesLength(0);
                        // Call services to handle the request
                        executeServlet();
                    }
                    else if (pRequest->getMethod() == "POST"){
                        // Set the length of readable bytes
                        if (!pRequest->getHeader("Content-Length").empty()) {
                            pInput->setExpectedBytesLength(std::atoi(pRequest->getHeader("Content-Length").c_str()));
                        }
                        // Call services to handle the request
                        executeServlet();
                    }
                    else{
                        LOG(WARNING) << "Unsupported HTTP method \"" << pRequest->getMethod() << "\".";
                        // 405 Method Not Allowed
                        pResponse->sendError(405);
                    }
                    // clear request body if the servlet did not use all of them
                    if (pInput->getExpectedBytesLength() > 0) {
                        LOG(TRACE) << "Clearing unused request body.";
                        pInput->ignore(pInput->getExpectedBytesLength());
                    }
                }
                else {
                    LOG(DEBUG) << "Skipped handling a request because of bad request.";
                    needCloseConnection = true;
                    pResponse->notifyOutputFinished();
                }
            }
            // Close the socket if needed
            if (needCloseConnection || !pResponse->isKeepAliveAllowed()) {
                LOG(DEBUG) << "Closing socket.";
                pSocket->disconnect();
            }
            else {
                LOG(TRACE) << "Will keep socket alive for next request.";
            }
            // Finished.
            delete pRequest;
            pRequest = NULL;
            delete pResponse;
            pResponse = NULL;
            if (headerContents != NULL) {
                delete headerContents;
                headerContents = NULL;
            }
        }
    }
    catch (std::exception& ex) {
        LOG(DEBUG) << "Clearing a socket because: " << +ex.what();
        if (pRequest != NULL) delete pRequest;
        if (pResponse != NULL) delete pResponse;
        if (headerContents != NULL) delete headerContents;

    }
}

// Returns the header contents. The caller should delete it. Returns NULL if the client sent nothing.

RequestHandlerThread::Vector* RequestHandlerThread::getHeaderContents() {
    Vector* contents = new Vector();
    String line;
    while (*pInput) {
        getline(*pInput, line);
        if (line.empty() || line == "\r") {
            // reading finished
            return contents;
        }
        contents->push_back(line);
    }
    // Should not be EOF.
    return NULL;
}

// Builds the request. Returns true if the request is built
// successfully and should be passed into servlets.

bool RequestHandlerThread::buildRequest(Vector& headerContents) {
    // Parse something like "GET /index.html?a=b HTTP/1.1". It should be
    // the first line.
    if (!analyzeFirstLine((headerContents)[0])) {
        return false;
    }
    // Analyzes header names and values.
    if (!analyzeHeaderNamesAndValues(headerContents)) {
        return false;
    }
    // TODO Check request url
    //String url=pRequest->getRequestUrl();
    //url=StringUtils::fixFilePath(url);
    //StringUtils::replaceAll(url, "\\", "/"); 
    //if(url.length()==0 || url[0]!='/'){
    //	// The url must begin with "/"
    //	pResponse->sendError(404);
    //	return false;
    //}
    //pRequest->setRequestUrl(url);
    // Finished
    return true;
}

// Parse something like "GET /index.html?a=b HTTP/1.1". It should be
// the first line.

bool RequestHandlerThread::analyzeFirstLine(String line) {
    int index = 0;
    int length = line.length();
    char c;
    // Parse method
    String method;
    c = line[index];
    while (c != ' '){
        method += c;
        index++;
        if (index == length){
            return false;
        }
        c = line[index];
    }
    pRequest->setMethod(method);
    // Parse URL
    String url;
    index++;
    if (index == length){
        return false;
    }
    c = line[index];
    while (c != ' '&& c != '?'){
        url += c;
        index++;
        if (index == length){
            return false;
        }
        c = line[index];
    }
    pRequest->setRequestUrl(url);
    // Parse query string
    String query;
    if (c == '?'){
        while (c != ' '){
            query += c;
            index++;
            if (index == length){
                return false;
            }
            c = line[index];
        }
    }
    pRequest->setQueryString(query);
    // TODO analyze parameters

    // Parse "HTTP/1.1"
    index++;
    if (index == length){
        return false;
    }
    String httpToken = line.substr(index, 8);
    if (httpToken != "HTTP/1.1"){
        return false;
    }
    return true;
}
// gcc does not support regex.
//bool RequestHandlerThread::analyzeFirstLine(String line) {
//    // Use regular expression to parse lines.
//    std::smatch match;
//    std::regex expression("^([A-Z]+)\\s+([^\\s\\?]+)(?:\\?(\\S+))?\\s+HTTP/1\\.1\\s$");
//    if (!std::regex_search(line, match, expression)) {
//        pResponse->sendError(400); // 400 Bad Request
//        return false;
//    }
//    pRequest->setMethod(match[1]);
//    pRequest->setRequestUrl(match[2]);
//    pRequest->setQueryString(match[3]);
//    // Parse params in queryString
//    Vector paramPairs = regexSplit(pRequest->getQueryString(), "&(?!(?:#|(?:\\w+;)))");
//    for (auto& param : paramPairs) {
//        size_t pos = param.find("=");
//        if (pos != String::npos) {
//            pRequest->addParameter(param.substr(0, pos), param.substr(pos + 1, param.length() - pos - 1));
//        }
//    }
//    return true;
//}

// Analyzes header names and values.

bool RequestHandlerThread::analyzeHeaderNamesAndValues(Vector& headerContents) {
    // Parse headers
    Vector::iterator itr = headerContents.begin() + 1;
    for (; itr != headerContents.end(); itr++) {
        // Try to find ":"
        int length = itr->length();
        int pos = itr->find_first_of(':');
        if (pos >= length - 1){
            pResponse->sendError(400); // 400 Bad Request
            return false;
        }
        String name = itr->substr(0, pos);
        String value = (*itr)[pos + 1] == ' ' ? itr->substr(pos + 2, length - pos - 2) : itr->substr(pos + 1, length - pos - 1);
        if ((!value.empty()) && value[value.length() - 1] == '\r'){
            value = value.substr(0, value.length() - 1);
        }
        // Add the header
        pRequest->addHeader(name, value);
    }
    // If the header "Connection" contains "keep-alive", tell response.
    if (pRequest->getHeader("Connection").find("keep-alive") != String::npos) {
        pResponse->setKeepAliveSupported(true);
    }
    return true;
}

//bool RequestHandlerThread::analyzeHeaderNamesAndValues(Vector& headerContents) {
//    // Parse headers
//    std::regex expression("^([\\w\\-]+):\\s*(.*?)\\s*$");
//    std::smatch match;
//    Vector::iterator itr = headerContents.begin() + 1;
//    for (; itr != headerContents.end(); itr++) {
//        // Try to match the header format.
//        if (!std::regex_search(*itr, match, expression)) {
//            pResponse->sendError(400); // 400 Bad Request
//            return false;
//        }
//        // Add the header
//        pRequest->addHeader(match[1], match[2]);
//    }
//    // If the header "Connection" contains "keep-alive", tell response.
//    if (pRequest->getHeader("Connection").find("keep-alive") != String::npos) {
//        pResponse->setKeepAliveSupported(true);
//    }
//    return true;
//}

// Gets an servlet and executes it.

void RequestHandlerThread::executeServlet() {
    LOG(DEBUG) << "Handling a request of url: " + pRequest->getRequestUrl();
    IHttpServlet* pServlet = mapping.createServlet(pRequest->getRequestUrl());
    if (pServlet != NULL) {
        String method = pRequest->getMethod();
        try {
            pServlet->doMethod(*pRequest, *pResponse);
            pResponse->notifyOutputFinished();
        }
        catch (IllegalOperationException& ex) {
            LOG(DEBUG) << "Got IllegalOperationException when executing servlets: " << ex.what();
            if (pResponse->isCommitted()) {
                // Cannot recover the response. Will close it shortly.
                needCloseConnection = true;
            }
            else {
                // Send error
                pResponse->reset();
                pResponse->sendError(500);
            }
        }
        catch (std::exception& ex) {
            LOG(DEBUG) << "Got exceptions when executing servlets: " << ex.what();
            if (pResponse->isCommitted()) {
                // Cannot recover the response. Will close it shortly.
                needCloseConnection = true;
            }
            else {
                // Send error
                pResponse->reset();
                pResponse->sendError(500);
            }
        }
        delete pServlet;
    }
    else {
        LOG(DEBUG) << "Got NULL servlet pointer";
        pResponse->sendError(404);
    }
}

// Splits the string according to the regular expression.

//RequestHandlerThread::Vector RequestHandlerThread::regexSplit(String str, String regex) {
//    std::smatch match;
//    std::regex expr(regex);
//    Vector ret;
//    while (std::regex_search(str, match, expr)) {
//        // Get the position of the token to split
//        size_t pos = match.position();
//        // Do splitting
//        ret.push_back(str.substr(0, pos));
//        str = str.substr(pos + 1, str.length() - pos - 1);
//    }
//    ret.push_back(str);
//    return ret;
//}

////////////////////////////////////////////////////////////////////////
// Function implementations of HttpServer

// Constructor with the url-servlets mapping, the listened port and
// the working thread count.

HttpServer::HttpServer(IHttpServletMapping& mapping, int port, int threadCount)
: port(port), pListener(NULL), mapping(mapping), threadCount(threadCount) {
}

// Desctructor.

HttpServer::~HttpServer() {
    if (pListener != NULL) {
        delete pListener;
    }
}

// Starts the server. It will try to bind the listened port. If
// failed, it will throw an exception.

void HttpServer::start() {
    if (pListener != NULL) {
        throw std::logic_error("HTTP server has been started");
    }
    if (port <= 0) {
        throw std::logic_error("Invalid HTTP server port");
    }
    try {
        pListener = new SocketListener(port);
    }
    catch (std::exception& ex) {
        throw std::logic_error(ex.what());
    }
    ThreadBase::start();
}

// Waits for the server to stop.

void HttpServer::join() {
    ThreadBase::join();
}

// Asks the server to stop. Use join() to wait for it.

void HttpServer::stop() {
    if (pListener != NULL) {
        pListener->stop();
        pListener = NULL;
    }
}

// Returns true if the server has been started.

bool HttpServer::isStarted() {
    return pListener != NULL;
}

// Runs the thread.

void HttpServer::run() {
    // Create threads to handling
    for (int i = 0; i < threadCount; i++) {
        threads.push_back(new RequestHandlerThread(queue, mapping, i));
        threads.back()->start();
    }
    LOG(INFO) << "HTTP server has started on port " << port;
    try {
        while (true) {
            // Get sockets and push them into the queue. The
            // RequestHandlerThread should delete the socket.
            Socket* pSocket = new Socket(pListener->waitForConnect());
            queue.enQ(pSocket);
        }
    }
    catch (std::exception&) {
        LOG(INFO) << "Closing HTTP server";
        // The connection is closed or something.
        // Close current sockets
        for (int i = 0; i < threadCount; i++) {
            Socket* pS = threads[i]->getSocket();
            if (pS != NULL && !pS->error()) {
                pS->disconnect();
            }
        }
        // Send empty pointers to the queue to stop theads.
        for (int i = 0; i < threadCount; i++) {
            queue.enQ(NULL);
        }
        // Waiting for threads
        for (int i = 0; i < threadCount; i++) {
            (*threads[i]).join();
            delete threads[i];
        }
        pListener = NULL;
    }
}

#ifdef TEXT_HTTPSERVER

#include "Logger.h"
using namespace std;

// A servlet for test

class HttpServletForTest : public DefaultHttpServlet {
public:
    // Do get method

    void doGet(IHttpServletRequest& request, IHttpServletResponse& response) {
        string url = request.getRequestUrl();
        if (url == "/throw_exception") {
            // throw an exception
            throw exception("The client asks to throw an exception.");
        } else if (url == "/send_back_params") {
            // send back parameters in the query string.
            response.setContentType("text/plain; charset=iso-8859-1");
            ostream& out = response.getOutputStream();
            map<string, vector < string>> pmap = request.getParameterMap();
            for (auto& pair : pmap) {
                out << "Name: " << pair.first << "\n";
                out << "Values: ";
                for (auto& val : pair.second) {
                    out << val << ", ";
                }
                out << endl;
            }
        } else if (url == "/no_content_length") {
            // avoid "keep-alive"
            response.setContentType("text/plain; charset=iso-8859-1");
            response.getOutputStream() << "Before flushed.\n";
            response.flushBuffer();
            response.getOutputStream() << "Already flushed.\n";
        } else if (url == "/do_nothing") {
            // do nothing
        } else {
            doMoreGet(request, response);
        }
    }

    // more situations for doGet()

    void doMoreGet(IHttpServletRequest& request, IHttpServletResponse& response) {
        string url = request.getRequestUrl();
        if (url == "/chunked") {
            response.setContentType("text/plain; charset=iso-8859-1");
            response.setHeader("Transfer-Encoding", "chunked");
            // final message is: "This is my chunked message.\nAnd my final message."
            ostream& out = response.getOutputStream();
            response.flushBuffer();
            out << "5\r\n";
            out << "This \r\n";
            out << "E\r\n";
            out << "is my chunked \r\n";
            out << "1F\r\n";
            out << "message.\nAnd my final message.\r\n";
            out << "0\r\n\r\n";
        } else if (url == "/") {
            // Write a index page.
            response.setContentType("text/html; charset=iso-8859-1");
            ostream& out = response.getOutputStream();
            out << "<!DOCTYPE html><html><head><title>Testing HttpServer</title></head>";
            out << "<body><ul>";
            out << "<li><a href=\"/\">this page</a></li>";
            out << "<li><a href=\"/do_nothing\">do nothing</a></li>";
            out << "<li><a href=\"/send_back_params?p1=v1&p2=v2&ppp\">send back params</a></li>";
            out << "<li><a href=\"/no_content_length\">no content length</a></li>";
            out << "<li><a href=\"/chunked\">chunked</a></li>";
            out << "<li><a href=\"/aaaaa\">404 error</a></li>";
            out << "</ul></body></html>";
        } else {
            response.sendError(404);
        }
    }

    // Do POST method

    void doPost(IHttpServletRequest& request, IHttpServletResponse& response) {
        string url = request.getRequestUrl();
        if (url == "/send_back_body") {
            // Send the body contents back directly.
            String line;
            istream& input = request.getInputStream();
            ostream& output = response.getOutputStream();
            while (input.good()) {
                getline(input, line);
                output << line << endl;
            }
        }
    }
};

// A mapping for test

class ServletMappingForTest : public IHttpServletMapping {
public:

    IHttpServlet* createServlet(std::string url) {
        // always returns the servlet for test.
        return new HttpServletForTest();
    }
};

void main() {
    std::cout << "Testing HttpServer" << std::endl;
    Logger::getLogger()->setLoggingLevel(0);
    ServletMappingForTest mapping;
    HttpServer server(mapping);
    server.start();
    // Now open a browser and visit 127.0.0.1:55555
    std::cout << "Now open a browser and visit 127.0.0.1:80\n";
    std::cout << "You can stop server by entering 0.\n";
    int num;
    std::cin>>num;
    while (num != 0) {
        std::cin>>num;
    }
    server.stop();
    server.join();
    /*std::string contents;
    contents+="GET /index.html?p1=v1&p2=v2&p3=&amp;v3&a4 HTTP/1.1\n";
    contents+="Host: localhost\n";
    contents+="Accept: text/plain\n";
    contents+="Accept-Charset: utf-8\n";
    contents+="Content-Length: 0\n";
    contents+="Connection: keep-alive\n";
    contents+="Accept-Language: en-US\n";
    contents+="User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:12.0) Gecko/20100101 Firefox/12.0\n";
    contents+="\n";*/
    Logger::dispose();
}


#endif
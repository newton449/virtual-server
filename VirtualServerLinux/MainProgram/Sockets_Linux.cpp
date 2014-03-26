/////////////////////////////////////////////////////////////////////
// Sockets.cpp - Provides basic network communication services     //
// ver 1.0                                                         //
// Language:    C++, Netbeans                                      //
// platform:    Kubuntu11.10                                       //
// Application: Spring 2012 DO Project 2                           //
// Author:      Yun Xing, Syracuse University, CST 4-282           //
//              yxing03@syr.edu                                    //
///////////////////////////////////////////////////////////////////////

#include "Sockets_Linux.h"
#include "Locks_Linux.h"
#include <sstream>
#include <sys/ioctl.h>
#include <fcntl.h>

#ifdef TRACING
#include "..\threads\locks.h"
#define TRACE(msg) sout << "\n  " << msg;
#else
#define TRACE(msg) ;
#endif

SocketSystem::SocketSystem() {

}

SocketSystem::~SocketSystem() {

}

std::string SocketSystem::getRemoteIP(Socket* pSock) {
    struct sockaddr name;
    socklen_t len = sizeof (name);
    int status = getpeername(pSock->s_, &name, &len);
    if (status == 0) {
        struct sockaddr_in* pRemote = reinterpret_cast<sockaddr_in*> (&name);
        return inet_ntoa(pRemote->sin_addr);
    }
    return "";
}

int SocketSystem::getRemotePort(Socket* pSock) {
    struct sockaddr name;
    socklen_t len = sizeof (name);
    int status = getpeername(pSock->s_, &name, &len);
    if (status == 0) {
        struct sockaddr_in* pRemote = reinterpret_cast<sockaddr_in*> (&name);
        return htons(pRemote->sin_port);
    }
    return -1;

}

std::string SocketSystem::getLocalIP() {
    hostent* local = gethostbyname("");
    return inet_ntoa(*(struct in_addr*) *local->h_addr_list);
}

int SocketSystem::getLocalPort(Socket* pSock) {
    struct sockaddr name;
    socklen_t len = sizeof (name);
    int status = getsockname(pSock->s_, &name, &len);
    if (status == 0) {
        struct sockaddr_in* pLocal = reinterpret_cast<sockaddr_in*> (&name);
        return htons(pLocal->sin_port);
    }
    return -1;
}

//
//----< constructor creates TCP Stream socket >----------------------

Socket::Socket() : SocketConnectionCount(0) {
    s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s_ == INVALID_SOCKET) {
        std::cout << "invalid socket in constructor" << std::endl;
        throw std::exception();
    }
}
//----< constructor creates connected TCP Stream socket >------------

Socket::Socket(const std::string& url, int port) : SocketConnectionCount(0) {
    s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s_ == INVALID_SOCKET) {
        std::cout << "invalid socket in constructor" << std::endl;
        throw std::exception();
    }
    this->connect(url, port);
}
//----< promotes WinSock SOCKET handle to Socket object >------------

Socket::Socket(SOCKET s) : s_(s), SocketConnectionCount(0) {
}

//----< destructor closes socket handle >----------------------------

Socket::~Socket() {
    TRACE("destroying socket");
    disconnect();
}

//----< assignment >-------------------------------------------------

Socket& Socket::operator =(SOCKET sock) {
    TRACE("\n  assigning from SOCKET");
    s_ = sock;
    SocketConnectionCount = 0;
    return *this;
}
//----< connects to IP address or network host >---------------------

bool Socket::connect(std::string url, int port, bool throwError) {

    sockaddr_in tcpAddr;
    tcpAddr.sin_family = AF_INET;
    tcpAddr.sin_addr.s_addr = inet_addr(url.c_str());
    tcpAddr.sin_port = htons(port);
    if (s_ == INVALID_SOCKET) {
        s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
    int err = ::connect(s_, (sockaddr*) & tcpAddr, sizeof (tcpAddr));

    std::string rip = ss_.getRemoteIP(this);
    int rport = ss_.getRemotePort(this);

    // error return from connect does not appear to be reliable

    if (err == SOCKET_ERROR || rport == -1) {
        if (throwError) {
            std::cout << "connet error" << std::endl;
            throw std::exception();
        }
        return false;
    }
    return true;
}
//
//----< disconnect socket >------------------------------------------

void Socket::disconnect() {
    shutdown(s_, SHUT_WR);
    close(s_);
    s_ = INVALID_SOCKET;
}

int Socket::bytesLeft() {
    int bytes;
    if (-1 == fcntl(s_, FIONREAD, &bytes)) {
        return 0;
    }
    return bytes;
}

//----< casts Socket to WinSock SOCKET handle >----------------------

Socket::operator SOCKET() {
    return s_;
}
//----< send blocks until all characters are sent >------------------

bool Socket::sendAll(const char* block, size_t len, bool throwError) {
    ssize_t bytesSent; // current number of bytes sent
    size_t blockIndx = 0; // place in buffer to send next
    size_t count = 0; // number of send failures

    const size_t sendRetries = 100;
    size_t blockLen = len;
    size_t bytesLeft = blockLen;
    while (bytesLeft > 0) {
        bytesSent = ::send(s_, &block[blockIndx], static_cast<int> (bytesLeft), 0);
        if (bytesSent == SOCKET_ERROR) {
            ++count;
            if (count == sendRetries) {
                if (throwError) {
                    std::cout << "send failed after 100 retries" << std::endl;
                    throw std::exception();
                } else
                    return false;
            }
            bytesSent = 0;
        }
        bytesLeft -= bytesSent;
        blockIndx += bytesSent;
    }
    return true;
}
//----< blocks until len characters have been sent >-----------------

bool Socket::recvAll(char* block, size_t len, bool throwError) {
    const size_t recvRetries = 100;
    ssize_t bytesRecvd, bytesLeft = len;
    size_t blockIndx = 0, count = 0;
    while (bytesLeft > 0) {
        bytesRecvd = ::recv(s_, &block[blockIndx], static_cast<int> (bytesLeft), 0);
        if (bytesRecvd == 0) {
            if (throwError) {
                std::cout << "remote connection closed" << std::endl;
                throw (std::exception());
            }
            return false;
        }
        if (bytesRecvd == SOCKET_ERROR) {
            ++count;
            if (count == recvRetries) {
                if (throwError) {
                    std::cout << "recv failed after 100 retries" << std::endl;
                    throw (std::exception());
                } else
                    return false;
            }
        }
        bytesLeft -= bytesRecvd;
        blockIndx += bytesRecvd;
    }
    return true;
}

//
//----< starts listener socket listening for connections >-----------

SocketListener::SocketListener(int port) //: InvalidSocketCount(0)
{
    tcpAddr.sin_family = AF_INET; // TCP/IP
    tcpAddr.sin_port = htons(port); // listening port
    tcpAddr.sin_addr.s_addr = INADDR_ANY;
    // listen over every network interface
    int err = bind(s_, (sockaddr*) & tcpAddr, sizeof (tcpAddr));

    if (err == SOCKET_ERROR) {
        std::cout << "binding error type:" << std::endl;
        throw std::exception();
    }

    /////////////////////////////////////////////////////////////////
    // listen for incoming connection requests

    int backLog = 10;
    err = listen(s_, backLog);

    if (err == SOCKET_ERROR) {
        std::cout << "listen mode error" << std::endl;
        throw std::exception();
    }
}
//----< destructor closes socket >-----------------------------------

SocketListener::~SocketListener() {
    try {
        TRACE("\n  destroying SocketListener");
        shutdown(s_, SHUT_RDWR);
        close(s_);
    } catch (...) {
        /* don't let exception propagate on shutdown */
    }
}
//----< blocks until a connection request has been received >--------

SOCKET SocketListener::waitForConnect() {
    //const long MaxCount = 20;
    InvalidSocketCount = 0;
    TRACE("listener waiting for connection request");
    socklen_t size = sizeof (tcpAddr);
    SOCKET toClient;
    do {
        toClient = accept(s_, (sockaddr*) & tcpAddr, &size);
        ++InvalidSocketCount;
        if (InvalidSocketCount >= 20) {
            std::cout << "invalid socket connection" << std::endl;
            throw std::exception();
        }
    } while (toClient == INVALID_SOCKET);
    TRACE("\n  connection establishted");
    return toClient;
}
//
//----< shuts down listerner >---------------------------------------

void SocketListener::stop() {
    TRACE("shutting down listener in SocketListerer");
    shutdown(s_, SHUT_RDWR);
    close(s_);
}

//
//----< test stub >--------------------------------------------------

#ifdef TEST_SOCKETS
#include <iostream>

void main() {
    try {
        SocketSystem su;
        std::string host = su.getHostName(), ip = su.getIpFromName(host), name = su.getNameFromIp(ip);
        SocketListener listener(2048);
        Socket sendr;
        if (!sendr.connect(name, 2048)) // can use ip addr, e.g., 127.0.0.1
            return;
        Socket recvr = listener.waitForConnect();
        // sending
        const char* msg1 = "this is a message";
        sendr.send(msg1, strlen(msg1) + 1);
        const char* msg2 = "and a final message";
        sendr.send(msg2, strlen(msg2) + 1);
        sendr.send("quit", strlen("quit") + 1);
        const int BufLen = 256;
        char buffer[BufLen];
        recvr.recv(buffer, strlen(msg1) + 1);
        recvr.recv(buffer, strlen(msg2) + 1);

        recvr.recv(buffer, strlen("quit") + 1);
        recvr.disconnect();
        sendr.disconnect();
        if (!sendr.connect(name, 2048)) {
            throw std::exception("\n  sender reconnect failed");
        }
        recvr = listener.waitForConnect();
        msg1 = "another message after reconnecting";
        std::cout << "\n  sender sending: " << msg1;
        sendr.send(msg1, strlen(msg1) + 1);
        recvr.recv(buffer, strlen(msg1) + 1);
        msg1 = "sending message back";
        recvr.send(msg1, strlen(msg1) + 1);
        recvr.send("quit", strlen("quit") + 1);
        // receiving
        sendr.recv(buffer, strlen(msg1) + 1);
        sendr.recv(buffer, strlen("quit") + 1);
        sendr.disconnect();
        recvr.disconnect();
    } catch (std::exception& e) {
        std::cout << "\n  " << e.what() << "\n\n";
    }
}

#endif

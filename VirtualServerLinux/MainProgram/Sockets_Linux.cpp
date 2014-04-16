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
#include <string.h>
#include <unistd.h>

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

// get ip address of network machine

std::string SocketSystem::getIpFromName(const std::string& name) {
    sockaddr_in tcpAddr;
    tcpAddr.sin_family = AF_INET;
    tcpAddr.sin_addr.s_addr = inet_addr(name.c_str());
    if (tcpAddr.sin_addr.s_addr == INADDR_NONE) {
        // name is not an ip address, so try to map name to address
        // via DNS

        hostent* remoteHost = gethostbyname(name.c_str());
        if (remoteHost == NULL) {
            throw SocketException("Failed to find IP for the name: " + name);
        }
        memcpy(
                &tcpAddr.sin_addr,
                remoteHost->h_addr_list[0],
                remoteHost->h_length
                );
    }
    char* ret = inet_ntoa(tcpAddr.sin_addr);
    if (ret == NULL) {
        throw SocketException("Failed to convert IP number to IP string.");
    } else {
        return ret;
    }
}

std::string SocketSystem::getLastErrorMessage() {
    return strerror(errno);
}

// constructor creates TCP Stream socket

Socket::Socket() {
    s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s_ == INVALID_SOCKET) {
        std::cout << "invalid socket in constructor" << std::endl;
        throw std::exception();
    }
}

//----< promotes WinSock SOCKET handle to Socket object >------------

Socket::Socket(SOCKET s) : s_(s) {
}

//----< destructor closes socket handle >----------------------------

Socket::~Socket() {
    TRACE("destroying socket");
    if (s_ != INVALID_SOCKET) {
        ::close(s_);
    }
}

//----< assignment >-------------------------------------------------

Socket& Socket::operator =(SOCKET sock) {
    TRACE("\n  assigning from SOCKET");
    s_ = sock;
    return *this;
}
//----< connects to IP address or network host >---------------------

void Socket::connect(std::string url, int port, size_t maxTries) {
    // get its ip if it is not an ip
    if (isalpha(url[0])) {
        url = ss_.getIpFromName(url);
    }

    // create socket if it invalid
    if (s_ == INVALID_SOCKET) {
        s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s_ == INVALID_SOCKET) {
            throw SocketException("Failed to create a socket: " + ss_.getLastErrorMessage());
        }
    }

    // create remote address in native API
    sockaddr_in tcpAddr;
    tcpAddr.sin_family = AF_INET;
    tcpAddr.sin_addr.s_addr = inet_addr(url.c_str());
    tcpAddr.sin_port = htons(port);

    int tryCount = 0;
    while (tryCount < maxTries) {
        ++tryCount;
        int err = ::connect(s_, (sockaddr*) & tcpAddr, sizeof (tcpAddr));

        // error return from connect does not appear to be reliable
        int rport = getRemotePort();
        if (err != SOCKET_ERROR && rport != -1) {
            return;
        }

        // wait for a while before retrying
        usleep(100 * 1000); //ignore errors
    }
    // failed to connect. throw an exception.
    throw SocketException(ss_.getLastErrorMessage());
}
//
//----< disconnect socket >------------------------------------------

void Socket::close() NOEXCEPT {
    // shutdown(s_, SHUT_WR);
    ::close(s_);
    s_ = INVALID_SOCKET;
}

void Socket::shutdownReceive() {
    if (SOCKET_ERROR == shutdown(s_, SHUT_RD)) {
        throw SocketException(ss_.getLastErrorMessage());
    }
}

void Socket::shutdownSend() {
    if (SOCKET_ERROR == shutdown(s_, SHUT_WR)) {
        throw SocketException(ss_.getLastErrorMessage());
    }
}

void Socket::shutdownBoth() {
    if (SOCKET_ERROR == shutdown(s_, SHUT_WR)) {
        throw SocketException(ss_.getLastErrorMessage());
    }
}


// send byte block 

int Socket::send(const char* block, size_t len) {
    int ret = ::send(s_, block, len, 0);
    if (SOCKET_ERROR != ret) {
        throw SocketException(ss_.getLastErrorMessage());
    }
    return ret;
}

// recieve byte block

int Socket::receive(char* block, size_t len) {
    int ret = ::recv(s_, block, len, 0);
    if (SOCKET_ERROR != ret) {
        throw SocketException(ss_.getLastErrorMessage());
    }
    return ret;
}

int Socket::getLeftBytesSize() {
    int bytes;
    if (-1 == fcntl(s_, FIONREAD, &bytes)) {
        // ignore errors
        return 0;
    }
    return bytes;
}

//----< casts Socket to WinSock SOCKET handle >----------------------

Socket::operator SOCKET() {
    return s_;
}

#define FATAL_SOCKET_ERROR(err) (err == EAGAIN || err == EWOULDBLOCK || err == EBADF || err == ECONNRESET || err == EDESTADDRREQ || err == EFAULT || err == EMSGSIZE || err == ENOTCONN || err == ENOTSOCK || err == EOPNOTSUPP)

//----< send blocks until all characters are sent >------------------

void Socket::sendAll(const char* block, size_t len, size_t maxTries) {
    size_t bytesSent; // current number of bytes sent
    size_t blockIndx = 0; // place in buffer to send next
    size_t count = 0; // number of send failures

    size_t blockLen = len;
    size_t bytesLeft = blockLen;
    while (bytesLeft > 0) {
        bytesSent = ::send(s_, &block[blockIndx], static_cast<int> (bytesLeft), 0);
        if (bytesSent == SOCKET_ERROR) {
            ++count;
            int err = errno;
            if (FATAL_SOCKET_ERROR(err) || count == maxTries) {
                // stop trying if it is a fatal error or it reach max tries
                throw SocketException("Failed to send data: " + ss_.getLastErrorMessage());
            }

            // wait for a while
            usleep(50 * 1000); //ignore errors
        } else {
            bytesLeft -= bytesSent;
            blockIndx += bytesSent;
        }
    }
}
//----< blocks until len characters have been sent >-----------------

// blocks until len characters have been sent

int Socket::receiveAll(char* block, size_t len, size_t maxTries) {
    size_t bytesRecvd, bytesLeft = len;
    size_t blockIndx = 0, count = 0;
    while (bytesLeft > 0) {
        bytesRecvd = ::recv(s_, &block[blockIndx], static_cast<int> (bytesLeft), 0);
        if (bytesRecvd == 0) {
            // the connection has been shutdowned gracefully. Return the actually received size.
            return len - bytesLeft;
        }
        if (bytesRecvd == SOCKET_ERROR) {
            ++count;
            int err = errno;
            if (FATAL_SOCKET_ERROR(err) || count == maxTries) {
                // stop trying if it is a fatal error or it reach max tries
                throw SocketException("Failed to receive data: " + ss_.getLastErrorMessage());
            }
            usleep(50 * 1000);
        } else {
            bytesLeft -= bytesRecvd;
            blockIndx += bytesRecvd;
        }
    }
    return len;
}

// set receive timeout in milliseconds

void Socket::setReceiveTimeout(int milliseconds) {
    int iResult;
    timeval time;
    time.tv_sec = milliseconds / 1000;
    time.tv_usec = 0;
    iResult = setsockopt(s_, SOL_SOCKET, SO_RCVTIMEO, (char *) &time, sizeof (time));
    if (iResult == SOCKET_ERROR) {
        throw SocketException(ss_.getLastErrorMessage());
    }
}

// get remote ip address

std::string Socket::getRemoteIP() {
    struct sockaddr name;
    socklen_t len = sizeof (name);
    int status = getpeername(s_, &name, &len);
    if (status != 0) {
        throw SocketException(ss_.getLastErrorMessage());
    }
    struct sockaddr_in* pRemote = reinterpret_cast<sockaddr_in*> (&name);
    return inet_ntoa(pRemote->sin_addr);
}

// get remote port

int Socket::getRemotePort() {
    struct sockaddr name;
    socklen_t len = sizeof (name);
    int status = getpeername(s_, &name, &len);
    if (status != 0) {
        throw SocketException(ss_.getLastErrorMessage());
    }
    struct sockaddr_in* pRemote = reinterpret_cast<sockaddr_in*> (&name);
    return htons(pRemote->sin_port);
}

// get local ip address

std::string Socket::getLocalIP() {
    struct sockaddr name;
    socklen_t len = sizeof (name);
    int status = getsockname(s_, &name, &len);
    if (status != 0) {
        throw SocketException(ss_.getLastErrorMessage());
    }
    struct sockaddr_in* pLocal = reinterpret_cast<sockaddr_in*> (&name);
    return inet_ntoa(pLocal->sin_addr);
}

// get local port

int Socket::getLocalPort() {
    struct sockaddr name;
    socklen_t len = sizeof (name);
    int status = getsockname(s_, &name, &len);
    if (status != 0) {
        throw SocketException(ss_.getLastErrorMessage());
    }
    struct sockaddr_in* pLocal = reinterpret_cast<sockaddr_in*> (&name);
    return htons(pLocal->sin_port);
    return -1;
}


//----< starts listener socket listening for connections >-----------

SocketListener::SocketListener(int port) //: InvalidSocketCount(0)
{
    tcpAddr.sin_family = AF_INET; // TCP/IP
    tcpAddr.sin_port = htons(port); // listening port
    tcpAddr.sin_addr.s_addr = INADDR_ANY;
    // listen over every network interface
    int err = bind(s_, (sockaddr*) & tcpAddr, sizeof (tcpAddr));
    if (err == SOCKET_ERROR) {
        throw SocketException("Failed to bind listener port: " + ss_.getLastErrorMessage());
    }

    /////////////////////////////////////////////////////////////////
    // listen for incoming connection requests

    int backLog = 10;
    err = listen(s_, backLog);
    if (err == SOCKET_ERROR) {
        throw SocketException("Failed to lisnter on port: " + ss_.getLastErrorMessage());
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

Socket SocketListener::waitForConnection() {
    const long MaxCount = 20;
    invalidSocketCount = 0;
    TRACE("listener waiting for connection request");
    socklen_t size = sizeof (tcpAddr);
    SOCKET toClient;
    while (INVALID_SOCKET == (toClient = accept(s_, (sockaddr*) & tcpAddr, &size))) {
        ++invalidSocketCount;
        if (invalidSocketCount >= 20)
            throw SocketException("Failed to accept a connection: " + ss_.getLastErrorMessage());
    }
    TRACE("connection establishted");
    return Socket(toClient);
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

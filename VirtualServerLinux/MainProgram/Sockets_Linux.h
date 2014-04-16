#ifndef SOCKETS_H
#define SOCKETS_H
/////////////////////////////////////////////////////////////////////
// Sockets.h   -  Provides basic network communication services    //
//                        sniffer results                          //
// ver 1.0                                                         //
// Language:    C++, Netbeans                                      //
// platform:    Kubuntu11.10                                       //
// Application: Spring 2012 DO Project 2                           //
// Author:      Yun Xing, Syracuse University, CST 4-282           //
//              yxing03@syr.edu  
// Resource: Jim Fawcett
///////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module provides network communication services, using 
  linux sockets.  Three classes are provided:

 

   Socket:
   -------
   Provides connect request, string read, and string write service.
   
   SocketListener:
   ---------------
   Provides connection handling.
   
   Public Interface:
   =================
   SocketListener listener(2048);             // create listener
   Socket recvr = listener.waitForConnect();  // start listener listening
   Socket sendr;                              // create sending socket
   sender.connect("\\localhost",2048);        // request a connection
   const char* msg = "this is a message"; 
   sender.send(msg,strlen(msg)+1);            // send terminating null
   sender.send("quit",strlen("quit")+1);      // send another msg

   char* buffer[1024];                        // receive buffer
   recvr.recv(buffer,strlen(msg)+1);          // copy data when available
   std::cout << "\n  recvd: " << buffer;
   recvr.recv(buffer,strlen("quit")+1);       // get more data
   std::cout << "\n  recvd: " << buffer;

   recvr.disconnect();                        // graceful shutdown
   sender.disconnect();                       // graceful shutdown
 */
//
/*
   Build Process:
   ==============
   Required Files:
     Sockets.h, Sockets.cpp

   Maintenance History:
   ====================
   
   ver 1.0 : 27 mar 12
   - first release
   
   ver 1.1 : 3/26/14 (by Sheng)
   - move get Remote/Local IP/Port functions from Socket to SocketSystem.
 */

#include <string>
#include <stdexcept>
#include<sys/types.h>
#include<sys/socket.h>
#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

// In the ISO C++11 Standard, the noexcept operator is introduced, but support
// for this feature is not yet present in Visual C++.
#ifndef NOEXCEPT
#ifdef WIN32
#define NOEXCEPT throw()
#else
#define NOEXCEPT noexcept(true)
#endif
#endif

typedef int SOCKET;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

/////////////////////////////////////////////////////////////////////
// SocketSystem class provides a few system services

class Socket;

class SocketException;

class SocketListener;

class SocketSystem {
public:
    SocketSystem();
    ~SocketSystem();
    //std::string getHostName();
    //std::string getNameFromIp(const std::string& ip);
    std::string getIpFromName(const std::string& name);
private:
    static long count;
    std::string getLastErrorMessage();

    friend class Socket;
    friend class SocketListener;
};

/////////////////////////////////////////////////////////////////////
// Socket class provides basic connect, read, and write operations

class Socket {
public:
    Socket();
    ~Socket();
    // Default copy constructor.
    //Socket(const Socket& sock);
    // Connect to a url and port. The url can be a domain or an IP. Use maxTries to assign max tries.
    // Throw SocketException if it fails to connect.
    void connect(std::string url, int port, size_t maxTries = 50);
    // Close the socket. Before calling this function, stream operations should be shutdowned.
    void close() NOEXCEPT;
    // Shutdown the receive operation. It cannot be read anymore.
    void shutdownReceive();
    // Shutdown the send operation. It cannot be writen anymore.
    void shutdownSend();
    // Shutdown both receive operation and send operation.
    void shutdownBoth();
    // Return true if the socket is valid.
    bool isValid();
    // Send a block data with its length. It will try only once. Some data may not be sent.
    int send(const char* block, size_t len);
    // Receive a block data with its length. It will try only once. It may not receive enough bytes.
    int receive(char* block, size_t len);
    // Return the size of the left (not used up) bytes in socket to receive.
    int getLeftBytesSize();
    // Send a block data with its length. It will try many times.
    void sendAll(const char* block, size_t len, size_t maxTries = 50);
    // Receive a block data with its length, and return the actually received size. It will try many
    // times to receive full size data. If the local socket shutdown receive operation or the remote
    // socket shutdown send operation, it will return the actuall received size. If errors occur, 
    // it will throw SocketException.
    int receiveAll(char* block, size_t len, size_t maxTries = 50);
    // set receive timeout in milliseconds
    void setReceiveTimeout(int milliseconds);
    // Return the remote IP.
    std::string getRemoteIP();
    // Return the remote port.
    int getRemotePort();
    // Return the local IP.
    std::string getLocalIP();
    // Return the local port.
    int getLocalPort();

private:
    Socket(const std::string& url, int port);
    Socket(SOCKET s);
    Socket& operator=(SOCKET sock);
    operator SOCKET();
    Socket& operator=(const Socket& sock);
    SOCKET s_;
    SocketSystem ss_;
    friend class SocketSystem;
    friend class SocketListener;
};

/////////////////////////////////////////////////////////////////////
// SocketListener class waits for connections, then delivers
// connected socket

class SocketListener {
public:
    // Construct an instance with the listening port
    SocketListener(int port);
    // Distructor
    ~SocketListener();
    // Wait for a connection. It will be blocked when waiting.
    Socket waitForConnection();
    // Stop listener.
    void stop();

    long getInvalidSocketCount();
private:
    sockaddr_in tcpAddr;
    Socket s_;
    SocketSystem ss_;
    volatile long invalidSocketCount;
};

inline bool Socket::isValid() {
    return (s_ != SOCKET_ERROR);
}

inline long SocketListener::getInvalidSocketCount() {
    return invalidSocketCount;
}


/////////////////////////////////////////////////////////////////////////
// An exception which is thrown when any socket error occurs.

class SocketException : public std::logic_error {
public:
    // Constructor with message.

    explicit SocketException(const std::string& what_arg)
    : std::logic_error(what_arg) {
    }
    // Constructor with message.

    explicit SocketException(const char* what_arg)
    : std::logic_error(what_arg) {
    }
    // Destructor.

    virtual ~SocketException() NOEXCEPT {
    }
};

#endif

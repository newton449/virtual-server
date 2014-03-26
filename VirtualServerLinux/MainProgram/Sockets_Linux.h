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
#include<sys/types.h>
#include<sys/socket.h>
#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

typedef int SOCKET;
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

/////////////////////////////////////////////////////////////////////
// SocketSystem class provides a few system services

class Socket;

class SocketSystem {
public:
    SocketSystem();
    ~SocketSystem();
    //std::string getHostName();
    //std::string getNameFromIp(const std::string& ip);
    //std::string getIpFromName(const std::string& name);
    std::string getRemoteIP(Socket* pSock);
    int getRemotePort(Socket* pSock);
    std::string getLocalIP();
    int getLocalPort(Socket* pSock);
    //std::string GetLastMsg(bool WantSocketMsg=true);
private:
    static long count;
};

/////////////////////////////////////////////////////////////////////
// Socket class provides basic connect, read, and write operations

class Socket {
public:
    Socket();
    Socket(const std::string& url, int port);
    Socket(SOCKET s);
    ~Socket();
    Socket& operator=(SOCKET sock);
    operator SOCKET();
    bool connect(std::string url, int port, bool throwError = false);
    void disconnect();

    bool error() {
        return (s_ == SOCKET_ERROR);
    }
    int bytesLeft();
    bool sendAll(const char* block, size_t len, bool throwError = false);
    bool recvAll(char* block, size_t len, bool throwError = false);
    long getSocketConnectionCount();

private:
    Socket(const Socket& sock);
    Socket& operator=(const Socket& sock);
    SOCKET s_;
    SocketSystem ss_;
    volatile long SocketConnectionCount;
    friend class SocketSystem;
};

inline long Socket::getSocketConnectionCount() {
    return SocketConnectionCount;
}

/////////////////////////////////////////////////////////////////////
// SocketListener class waits for connections, then delivers
// connected socket

class SocketListener {
public:
    SocketListener(int port);
    ~SocketListener();
    SOCKET waitForConnect();
    void stop();
    long getInvalidSocketCount();
private:
    sockaddr_in tcpAddr;
    Socket s_;
    volatile long InvalidSocketCount;
};

inline long SocketListener::getInvalidSocketCount() {
    return InvalidSocketCount;
}

#endif

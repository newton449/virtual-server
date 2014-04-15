#ifndef SOCKETS_H
#define SOCKETS_H
/////////////////////////////////////////////////////////////////////
// Sockets.h   -  Provides basic network communication services    //
// ver 3.0                                                         //
// Language:      Visual C++, 2005                                 //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP 2.0      //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module provides network communication services, using
   WinSock2, a nearly Berkley Sockets compliant implementation.
   Three classes are provided:

   SocketSystem:
   -------------
   provides WinSock loading, unloading and a few program wide services.
   A recent change has ensured that the WinSock library is only loaded
   once, no matter how many times you construct SocketSystem objects.
   So now, the Socket class has a SocketSystem instance so you don't
   have to do an explicit creation of a SocketSystem object before
   creating a Socket.

   Socket:
   -------
   Provides connect request and read/write services.

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
   sender.sendAll(msg,strlen(msg)+1);         // send msg and terminating null
   sender.sendAll("quit",strlen("quit")+1);   // send another msg

   char* buffer[1024];                        // receive buffer
   recvr.recvAll(buffer,strlen(msg)+1);       // copy data when available
   std::cout << "\n  recvd: " << buffer;
   recvr.recvA;;(buffer,strlen("quit")+1);    // get more data
   std::cout << "\n  recvd: " << buffer;

   sender.WriteLine("this is a line");        // will append newline
   std::string reply = recvr.ReadLine();      // removes newline

   recvr.disconnect();                        // graceful shutdown
   sender.disconnect();                       // graceful shutdown
   */
//
/*
   Build Process:
   ==============
   Required Files:
   Sockets.h, Sockets.cpp

   Compile Command:
   ================
   cl /EHsc /DTEST_SOCKETS Sockets.cpp wsock32.lib user32.lib

   Maintenance History:
   ====================
   ver 3.0 : 15 Apr 2012
   - changed send to sendAll -- breaking change
   - changed recv to recvAll -- breaking change
   - added ReadLine and WriteLine
   - added bytesLeft to avoid blocking call
   - now allow compiler generated copy and assignment
   ver 2.1 : 17 Apr 2010
   - added planned changes, below
   ver 2.0 : 13 Apr 2010
   - made copy constructor and standard assignment operator private.
   - these operations can be made to work, but you need to duplicate
   the SOCKET handle to make the SOCKET object reference counting
   work as expected.  Not implemented yet.
   ver 1.9 : 05 May 2009
   - fixed bug, found by Phil Pratt-Szeliga, in
   SocketListener::WaitForConnection() due to allowing a
   client handling thread to be created with an invalid socket.
   That was fixed in SocketListener::WaitForConnect().
   ver 1.8 : 04 Apr 08
   - discovered that WinSock connect function does not always return
   appropriate error message on failure to connect (this is a new
   bug in WinSock, I believe) so added a remote port check, which
   returns -1 on failure to connect.
   ver 1.7 : 27 Mar 08
   - added throwing exception in socket.connect(...)
   ver 1.6 : -1 May 07
   - Estepan Meliksetian reported a problem with disconnect preventing a reconnect.
   This has been fixed by setting the socket s_ to INVALID_SOCKET in the disconnect
   function, and testing for INVALID_SOCKET in the connect function.
   ver 1.5 : 05 Apr 07
   - removed redundant Winsock socket initialization from Socket copy ctor.
   Bug reported by Vishal Chowdhary.
   ver 1.4 : 01 Apr 07
   - removed some commented code
   ver 1.3 : 27 Mar 07
   - added SocketSystem members to Socket and SocketListener
   ver 1.2 : 18 Feb 07
   - cosmetic changes
   ver 1.0 : 11 Feb 07
   - first release, a major rewrite of an earlier socket demo

   Planned Changes:
   ================
   - Add reference counting by duplicating socket handle and change access
   of copy and assignment to public.

   */

#include <string>
#include <winsock2.h>


// In the ISO C++11 Standard, the noexcept operator is introduced, but support
// for this feature is not yet present in Visual C++.
#ifndef NOEXCEPT
#ifdef WIN32
#define NOEXCEPT throw()
#else
#define NOEXCEPT noexcept(true)
#endif
#endif

/////////////////////////////////////////////////////////////////////
// SocketSystem class loads and unloads WinSock library
// and provides a few system services

class Socket;

class SocketException;

class SocketListener;

class SocketSystem
{
public:
    SocketSystem();
    ~SocketSystem();
    std::string getHostName();
    std::string getNameFromIp(const std::string& ip);
    std::string getIpFromName(const std::string& name);
    std::string getLastErrorMessage(bool WantSocketMsg = true);
private:
    static long count;
};

/////////////////////////////////////////////////////////////////////
// Socket class provides basic connect, read, and write operations

class Socket
{
public:
    Socket();
    ~Socket();
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
    bool isValid() { return (s_ != INVALID_SOCKET); }
    // Send a block data with its length. It will try only once. Some data may not be sent.
    int send(const char* block, size_t len);
    // Receive a block data with its length. It will try only once. It may not receive enough bytes.
    int receive(char* block, size_t len);
    // Return the size of the left (not used up) bytes in socket to receive.
    int getLeftBytesSize();
    // Send a block data with its length. It will try many times.
    void sendAll(const char* block, size_t len, size_t maxTries = 50);
    // Receive a block data with its length. It will try many times.
    void receiveAll(char* block, size_t len, size_t maxTries = 50);
    // Write a line to socket. It will apppend a '\n' if the string is not end with '\n' or '\r'.
    void writeLine(const std::string& str);
    // Read a line from socket. It will remove last '\n' or '\r' in the line.
    std::string readLine();
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
    HANDLE getHandle() { return (HANDLE)s_; }
    SocketSystem& System() { return ss_; }

private:
    explicit Socket(SOCKET s);
    operator SOCKET () { return s_; };
    Socket& operator=(const Socket& sock);
    Socket& operator=(SOCKET sock);
    SOCKET s_;
    SocketSystem ss_;

    friend class SocketListener;
};

/////////////////////////////////////////////////////////////////////
// SocketListener class waits for connections, then delivers
// connected socket

class SocketListener
{
public:
    // Construct an instance with the listening port
    SocketListener(int port);
    // Distructor
    ~SocketListener();
    // Wait for a connection. It will be blocked when waiting.
    Socket waitForConnection();
    // Stop listener.
    void stop();
    // Return
    long getInvalidSocketCount();
private:
    SOCKADDR_IN tcpAddr;
    Socket s_;
    SocketSystem ss_;
    volatile long invalidSocketCount;
};

inline long SocketListener::getInvalidSocketCount()
{
    return invalidSocketCount;
}

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
// An exception which is thrown when any socket error occurs.
class SocketException : public std::logic_error{
public:
    // Constructor with message.
    explicit SocketException(const std::string& what_arg)
        : std::logic_error(what_arg){
        }
    // Constructor with message.
    explicit SocketException(const char* what_arg)
        : std::logic_error(what_arg){
        }
    // Destructor.
    virtual ~SocketException() NOEXCEPT{}
};

#endif

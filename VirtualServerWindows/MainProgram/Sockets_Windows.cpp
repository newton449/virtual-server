/////////////////////////////////////////////////////////////////////
// Sockets.cpp - Provides basic network communication services     //
// ver 3.0                                                         //
// Language:      Visual C++, 2005                                 //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP 2.0      //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include "Sockets.h"
#include "Locks.h"
#include <sstream>

#ifdef TRACING
#include "Locks.h"
#define TRACE(msg) sout << "\n  " << msg;
#else
#define TRACE(msg) ;
#endif

long SocketSystem::count = 0;

//----< convert integer to string >----------------------------------

std::string intToString(const int num)
{
    std::ostringstream out;
    out << num;
    return out.str();
}

// get socket error message string
std::string SocketSystem::getLastErrorMessage() {
    // ask system what type of error occurred
    DWORD errorCode = WSAGetLastError();
    return getErrorMessage(errorCode);
}

// get socket error message string
std::string SocketSystem::getErrorMessage(int errorCode) {
    // ask system what type of error occurred
    if (errorCode == 0)
        return "no error";

    // map errorCode into a system defined error string
    DWORD dwFlags =
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER;
    LPCVOID lpSource = NULL;
    DWORD dwMessageID = errorCode;
    DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
    LPSTR lpBuffer = NULL;
    DWORD nSize = 0;
    va_list *Arguments = NULL;

    // we SHOULD use FormatMessageA instead of FormatMessageM because we need char* instead of wchar_t*
    FormatMessageA(
        dwFlags, lpSource, dwMessageID, dwLanguageId,
        (LPSTR)&lpBuffer, nSize, Arguments
        );

    std::string _msg(lpBuffer);
    LocalFree(lpBuffer);
    return _msg;
}

// load WinSock Library
SocketSystem::SocketSystem()
{
    if (count == 0)
    {
        TRACE("loading wsock32 library");
        WORD wVersionRequested = MAKEWORD(1, 1); // requesting version 1.1
        WSAData wData;                          // startup data filled by WSAStartup
        int err = WSAStartup(wVersionRequested, &wData);
        // The WSAStartup function directly returns the extended error code in the return 
        // value for this function. A call to the WSAGetLastError function is not needed 
        // and should not be used.
        if (err != 0){
            throw SocketException("Failed to initialize socket system: " + getErrorMessage(err));
        }
    }
    InterlockedIncrement(&count);
}

// destructor unloads socket library
SocketSystem::~SocketSystem()
{
    try {
        if (InterlockedDecrement(&count) == 0)
        {
            TRACE("unloading wsock32 library");
            WSACleanup();
        }
    }
    catch (...) { /* don't allow exception to propagate on shutdown */ }
}

// get host name
std::string SocketSystem::getHostName()
{
    char buffer[256];
    if (gethostname(buffer, 256) != 0){
        throw SocketException("Failed to get host name: " + getLastErrorMessage());
    }
    return buffer;
}

// get ip address of network machine
std::string SocketSystem::getIpFromName(const std::string& name)
{
    hostent* remoteHost = 0;
    SOCKADDR_IN tcpAddr;
    tcpAddr.sin_family = AF_INET;
    tcpAddr.sin_addr.s_addr = inet_addr(name.c_str());
    if (tcpAddr.sin_addr.s_addr == INADDR_NONE)
    {
        // name is not an ip address, so try to map name to address via DNS
        hostent* remoteHost = gethostbyname(name.c_str());
        if (remoteHost == NULL){
            throw SocketException("Failed to find IP for the name: " + name);
        }
        CopyMemory(
            &tcpAddr.sin_addr,
            remoteHost->h_addr_list[0],
            remoteHost->h_length
            );
    }
    // convert IP number to IP string.
    char* ret = inet_ntoa(tcpAddr.sin_addr);
    if (ret == NULL){
        throw SocketException("Failed to convert IP number to IP string.");
    }
    else{
        return ret;
    }
}

// get network name of machine from ip address
std::string SocketSystem::getNameFromIp(const std::string& ip)
{
    struct in_addr ipaddr;
    ipaddr.s_addr = inet_addr(ip.c_str());
    struct hostent* host = gethostbyaddr((char*)&ipaddr, sizeof(in_addr), AF_INET);
    if (!host){
        throw SocketException("Failed to find host name by the IP :" + ip);
    }
    return host->h_name;
}

// constructor creates TCP Stream socket
Socket::Socket()
{
    s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s_ == INVALID_SOCKET){
        throw SocketException("Failed to create socket: " + ss_.getLastErrorMessage());
    }
}
//----< copy constructor >-------------------------------------------

//Socket::Socket(const Socket& sock)
//{
//    TRACE("copying socket");
//    DuplicateHandle(GetCurrentProcess(), (HANDLE)sock.s_, GetCurrentProcess(), (HANDLE*)&s_, 0, false, DUPLICATE_SAME_ACCESS);
//    //std::cout << "\n  source handle = " << sock.s_;
//    //std::cout << "\n  destin handle = " << s_;
//}
//----< promotes WinSock SOCKET handle to Socket object >------------

Socket::Socket(SOCKET s) : s_(s) {}

//----< destructor closes socket handle >----------------------------

Socket::~Socket()
{
    TRACE("destroying socket");
    if (s_ != INVALID_SOCKET){
        closesocket(s_);
    }
}

//----< assignment >-------------------------------------------------
Socket& Socket::operator=(const Socket& sock)
{
    if (this == &sock) return *this;
    TRACE("copying socket");
    DuplicateHandle(GetCurrentProcess(), (HANDLE)sock.s_, GetCurrentProcess(), (HANDLE*)&s_, 0, false, DUPLICATE_SAME_ACCESS);
    return *this;
}

//----< assignment >-------------------------------------------------
Socket& Socket::operator =(SOCKET sock)
{
    TRACE("assigning from SOCKET");
    s_ = sock;
    return *this;
}

// connect 
void Socket::connect(std::string url, int port, size_t maxTries)
{
    // get its ip if it is not an ip
    if (isalpha(url[0])){
        url = ss_.getIpFromName(url);
    }

    // create socket if it invalid
    if (s_ == INVALID_SOCKET)
    {
        s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s_ == INVALID_SOCKET){
            throw SocketException("Failed to create a socket: " + ss_.getLastErrorMessage());
        }
    }

    // create remote address in native API
    SOCKADDR_IN tcpAddr;
    tcpAddr.sin_family = AF_INET;
    tcpAddr.sin_addr.s_addr = inet_addr(url.c_str());
    tcpAddr.sin_port = htons(port);

    // try to connect
    size_t tryCount = 0;
    while (tryCount < maxTries)
    {
        ++tryCount;
        TRACE("attempt to connect #" + intToString(tryCount));
        int err = ::connect(s_, (sockaddr*)&tcpAddr, sizeof(tcpAddr));

        // check port
        int rport = getRemotePort();

        // error return from connect does not appear to be reliable
        if (err != SOCKET_ERROR  && rport != -1){
            return;
        }

        // wait for a while before retrying
        ::Sleep(100);
    }

    // failed to connect. throw an exception.
    throw SocketException(std::string("Failed to connect to \"") + url + ":" + intToString(port) + "\" because: " + ss_.getLastErrorMessage());
}

// disconnect socket 
void Socket::close()
{
    // do not report error
    if (isValid()){
        closesocket(s_);
        s_ = INVALID_SOCKET;
    }
}

void Socket::shutdownReceive(){
    if (SOCKET_ERROR == shutdown(s_, SD_RECEIVE)){
        throw SocketException("Failed to shutdown input stream: " + ss_.getLastErrorMessage());
    }
}

void Socket::shutdownSend(){
    if (SOCKET_ERROR == shutdown(s_, SD_SEND)){
        throw SocketException("Failed to shutdown output stream: " + ss_.getLastErrorMessage());
    }
}

void Socket::shutdownBoth(){
    if (SOCKET_ERROR == shutdown(s_, SD_BOTH)){
        throw SocketException("Failed to shutdown input and output stream: " + ss_.getLastErrorMessage());
    }
}

// send byte block 
int Socket::send(const char* block, size_t len)
{
    int ret = ::send(s_, block, len, 0);
    if (SOCKET_ERROR != ret){
        throw SocketException("Failed to send block: " + ss_.getLastErrorMessage());
    }
    return ret;
}

// recieve byte block
int Socket::receive(char* block, size_t len)
{
    int ret = ::recv(s_, block, len, 0);
    if (SOCKET_ERROR != ret){
        throw SocketException("Failed to receive block: " + ss_.getLastErrorMessage());
    }
    return ret;
}

// return number of bytes waiting
int Socket::getLeftBytesSize()
{
    unsigned long bytes;
    if (SOCKET_ERROR != ::ioctlsocket(s_, FIONREAD, &bytes)){
        throw SocketException("Failed to get left bytes size: " + ss_.getLastErrorMessage());
    }
    return bytes;
}

#define FATAL_SOCKET_ERROR(err) (err == WSAECONNRESET || err == WSAENETDOWN || err == WSAEFAULT || err == WSAENOTCONN || err == WSAENOTSOCK || err == WSAECONNABORTED)

// send blocks until all characters are sent
void Socket::sendAll(const char* block, size_t len, size_t maxTries)
{
    size_t bytesSent;       // current number of bytes sent
    size_t blockIndx = 0;   // place in buffer to send next
    size_t count = 0;       // number of send failures

    size_t blockLen = len;
    size_t bytesLeft = blockLen;
    while (bytesLeft > 0) {
        bytesSent = ::send(s_, &block[blockIndx], static_cast<int>(bytesLeft), 0);
        if (bytesSent == SOCKET_ERROR)
        {
            ++count;
            int err = WSAGetLastError();
            std::cout << err << "\t";
            if (FATAL_SOCKET_ERROR(err) || count == maxTries)
            {
                // stop trying if it is a fatal error or it reach max tries
                throw SocketException("Failed to send data: " + ss_.getLastErrorMessage());
            }
            Sleep(50);
        }
        else{
            bytesLeft -= bytesSent;
            blockIndx += bytesSent;
        }
    }
}

// blocks until len characters have been sent
int Socket::receiveAll(char* block, size_t len, size_t maxTries)
{
    size_t bytesRecvd, bytesLeft = len;
    size_t blockIndx = 0, count = 0;
    while (bytesLeft > 0) {
        bytesRecvd = ::recv(s_, &block[blockIndx], static_cast<int>(bytesLeft), 0);
        if (bytesRecvd == 0)
        {
            // the connection has been shutdowned gracefully. Return the actually received size.
            return len - bytesLeft;
        }
        if (bytesRecvd == SOCKET_ERROR) {
            ++count;
            int err = WSAGetLastError();
            if (FATAL_SOCKET_ERROR(err) || count == maxTries)
            {
                // stop trying if it is a fatal error or it reach max tries
                throw SocketException("Failed to receive data: " + ss_.getLastErrorMessage());
            }
            Sleep(50);
        }
        else{
            bytesLeft -= bytesRecvd;
            blockIndx += bytesRecvd;
        }
    }
    return len;
}
// write a line of text
void Socket::writeLine(const std::string& str)
{
    // appends newline if none at end of string
    if (str.empty()){
        sendAll("\n", 1);
        return;
    }
    char end = str[str.size() - 1];
    if (end != '\n' && end != '\r')
    {
        std::string temp = str;
        temp.append("\n");
        sendAll(temp.c_str(), temp.size(), true);
    }
    else{
        sendAll(str.c_str(), str.size(), true);
    }
}
// read a line of text
std::string Socket::readLine()
{
    // removes ending newline if present, else reads to end of buffer
    std::string temp;
    char block[1];
    while (true)
    {
        int size = receive(block, 1);
        if (size == 0){
            // the socket has been shutdown correctly.
            return temp;
        }
        // save all chars that are not newlines or carriage returns
        if (block[0] != '\n' && block[0] != '\r')
            temp += block[0];
        else
        {
            return temp;
        }
    }
}

// set receive timeout in milliseconds
void Socket::setReceiveTimeout(int milliseconds){
    int iResult;
    timeval time;
    time.tv_sec = milliseconds / 1000;
    time.tv_usec = milliseconds % 1000;
    iResult = setsockopt(s_, SOL_SOCKET, SO_RCVTIMEO, (char *)&time, sizeof(time));
    if (iResult == SOCKET_ERROR) {
        throw SocketException(ss_.getLastErrorMessage());
    }
}

// get remote ip address
std::string Socket::getRemoteIP()
{
    struct sockaddr name;
    int len = sizeof(name);
    int status = getpeername(s_, &name, &len);
    if (status != 0)
    {
        throw SocketException(ss_.getLastErrorMessage());
    }
    struct sockaddr_in* pRemote = reinterpret_cast<sockaddr_in*>(&name);
    return inet_ntoa(pRemote->sin_addr);
}

// get remote port
int Socket::getRemotePort()
{
    struct sockaddr name;
    int len = sizeof(name);
    int status = getpeername(s_, &name, &len);
    if (status != 0)
    {
        throw SocketException(ss_.getLastErrorMessage());
    }
    struct sockaddr_in* pRemote = reinterpret_cast<sockaddr_in*>(&name);
    return htons(pRemote->sin_port);
}

// get local ip address
std::string Socket::getLocalIP()
{
    struct sockaddr name;
    int len = sizeof(name);
    int status = getsockname(s_, &name, &len);
    if (status != 0)
    {
        throw SocketException(ss_.getLastErrorMessage());
    }
    struct sockaddr_in* pLocal = reinterpret_cast<sockaddr_in*>(&name);
    return inet_ntoa(pLocal->sin_addr);
}

// get local port
int Socket::getLocalPort()
{
    struct sockaddr name;
    int len = sizeof(name);
    int status = getsockname(s_, &name, &len);
    if (status != 0)
    {
        throw SocketException(ss_.getLastErrorMessage());
    }
    struct sockaddr_in* pLocal = reinterpret_cast<sockaddr_in*>(&name);
    return htons(pLocal->sin_port);
    return -1;
}

// starts listener socket listening for connections
SocketListener::SocketListener(int port) : invalidSocketCount(0)
{
    tcpAddr.sin_family = AF_INET;   // TCP/IP
    tcpAddr.sin_port = htons(port); // listening port
    tcpAddr.sin_addr.s_addr = INADDR_ANY;
    // listen over every network interface
    int err = bind(s_, (SOCKADDR*)&tcpAddr, sizeof(tcpAddr));
    if (err == SOCKET_ERROR)
    {
        throw SocketException("Failed to bind listener port: " + ss_.getLastErrorMessage());
    }

    /////////////////////////////////////////////////////////////////
    // listen for incoming connection requests

    int backLog = 10;
    err = listen(s_, backLog);
    if (err == SOCKET_ERROR){
        throw SocketException("Failed to lisnter on port: " + ss_.getLastErrorMessage());
    }
}

// destructor closes socket
SocketListener::~SocketListener()
{
    try {
        TRACE("destroying SocketListener");
        closesocket(s_);
    }
    catch (...) { /* don't let exception propagate on shutdown */ }
}

// blocks until a connection request has been received
Socket SocketListener::waitForConnection()
{
    const long MaxCount = 20;
    invalidSocketCount = 0;
    TRACE("listener waiting for connection request");
    int size = sizeof(tcpAddr);
    SOCKET toClient;
    while (INVALID_SOCKET == (toClient = accept(s_, (SOCKADDR*)&tcpAddr, &size))){
        ++invalidSocketCount;
        if (invalidSocketCount >= 20)
            throw SocketException("Failed to accept a connection: " + ss_.getLastErrorMessage());
    }
    TRACE("connection establishted");
    return Socket(toClient);
}
//
//----< shuts down listerner >---------------------------------------

void SocketListener::stop()
{
    TRACE("shutting down listener in SocketListerer");
    closesocket(s_);
}
//----< test stub >--------------------------------------------------

#ifdef TEST_SOCKETS
#include <iostream>

void main()
{
    /*
     * Note:
     * - No threads are used in this test stub, so it doesn't represent typical usage.
     * - Neither do we do any message framing.  So correct operation depends on lightly
     *   loaded receiver.
     * - We will provide a simple demo using threads and queues with message framing
     *   to show how that is done in another demo.
     */
    std::cout << "\n  Testing Socket, SocketListener, and SocketSystem classes";
    std::cout << "\n ==========================================================\n";
    try
    {
        SocketSystem su;
        std::string host = su.getHostName();
        std::cout << "\n  host machine name:           " << host.c_str();
        std::string ip = su.getIpFromName(host);
        std::cout << "\n  IP Address of machine:       " << ip.c_str();
        std::string name = su.getNameFromIp(ip);
        std::cout << "\n  DNS name of machine from ip: " << name.c_str() << '\n';

        std::cout << "\n  Client connecting to Server";
        std::cout << "\n -----------------------------";
        SocketListener listener(2048);
        Socket sendr;
        if(!sendr.connect("127.0.0.1",2048))  // this works too
            //if(!sendr.connect("Apocalypse",2048))  // can use ip addr, e.g., 127.0.0.1
        {
            std::cout << "\n connection failed\n\n";
            return;
        }
        Socket recvr = listener.waitForConnect();
        std::cout << "\n  remote ip is: " << recvr.System().getRemoteIP(&recvr);
        std::cout << ", remote port is: " << recvr.System().getRemotePort(&recvr);
        std::cout << "\n  local ip is:  " << recvr.System().getLocalIP();
        std::cout << ", local port is: " << recvr.System().getLocalPort(&recvr) << '\n';

        std::cout << "\n  sending from Client to Server";
        std::cout << "\n -------------------------------";

        // sending
        const char* msg1 = "this is a message";
        sendr.sendAll(msg1,strlen(msg1)+1);

        const char* msg2 = "and a final message";
        sendr.sendAll(msg2,strlen(msg2)+1);

        sendr.sendAll("quit",strlen("quit")+1);

        // receiving
        std::cout.flush();
        const int BufLen = 256;
        char buffer[BufLen];

        std::cout << "\n  " << recvr.bytesLeft() << " bytes ready for reading";
        recvr.recvAll(buffer,strlen(msg1)+1);
        std::cout << "\n  Server received: " << buffer;
        std::cout << "\n  " << recvr.bytesLeft() << " bytes ready for reading";

        recvr.recvAll(buffer,strlen(msg2)+1);
        std::cout << "\n  Server received: " << buffer;
        std::cout << "\n  " << recvr.bytesLeft() << " bytes ready for reading";

        recvr.recvAll(buffer,strlen("quit")+1);
        std::cout << "\n  Server received: " << buffer;
        std::cout << "\n  " << recvr.bytesLeft() << " bytes ready for reading";
        std::cout << "\n";

        std::cout << "\n  Breaking connection";
        recvr.disconnect();
        sendr.disconnect();

        // new connection

        std::cout << "\n  Establishing new connection\n";
        if(!sendr.connect("127.0.0.1",2048))
        {
            throw std::exception("\n  reconnect failed");
        }
        recvr = listener.waitForConnect();
        msg1 = "another message after reconnecting";
        std::cout << "\n  Client sending: " << msg1;
        sendr.WriteLine(msg1);
        std::string temp = recvr.ReadLine();
        std::cout << "\n  Server received: " << temp;
        std::cout << "\n";

        // demonstrating full duplex operation
        std::cout << "\n  sending from Server back to Client";
        std::cout << "\n ------------------------------------";

        // sending
        msg1 = "sending message back";
        std::cout << "\n  Server sending message: " << msg1;
        recvr.WriteLine(msg1);
        std::cout << "\n  Server sending message: " << "quit";
        recvr.WriteLine("quit");

        // receiving
        std::cout << "\n  Client received: " << sendr.ReadLine();
        std::cout << "\n  Client received: " << sendr.ReadLine();
        std::cout << "\n  Client received: " << sendr.ReadLine();
        std::cout << std::endl;

        // copy construction
        Socket sendrCopy = sendr;
        Socket recvrCopy = recvr;

        // copy construction
        std::cout << "\n  sending and recieving with socket copies";
        std::cout << "\n ------------------------------------------";

        sendrCopy.WriteLine("string from sendrCopy");
        // recieving with copy
        std::cout << "\n  recvrCopy received: " << recvrCopy.ReadLine();
        std::cout << std::endl;

        // socket assignment
        sendr = sendrCopy;
        recvr = recvrCopy;

        // sending from assigned socket
        std::cout << "\n  sending and recieving with assigned sockets";
        std::cout << "\n ---------------------------------------------";

        sendr.WriteLine("string from AssignedSendr");
        // recieving with copy
        std::cout << "\n  AssignedRecvr received: " << recvr.ReadLine();
        std::cout << std::endl;

        sendr.disconnect();
        recvr.disconnect();
    }
    catch(std::exception& e)
    {
        std::cout << "\n  " << e.what() << "\n\n";
    }
    std::cout << "\n\n";
}

#endif

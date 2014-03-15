#ifndef SOCKETSTREAM_H
#define SOCKETSTREAM_H

/////////////////////////////////////////////////////////////////////
//  SocketStream.h - wraps socket input and output into a istream  //
//          and an ostream.                                        //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2012                                 //
//  Platform:      Windows 8                                       //
//  Application:   CSE687 Pr3, Spring 2013                         //
//  Author:        Sheng Wang                                      //
/////////////////////////////////////////////////////////////////////
/*
Module Operations: 
==================
This module wraps socket input and output into a istream and an ostream.
It supports efficient large bytes input and output.
See the following classes.

Main Class:
- SocketInputStream : A class to wrap the socket input in an istream.
- SocketOutputStream : A class to wrap the socket output in an ostream.

Other Class:
- SocketBuffer : A class to wrap the socket I/O in a streambuf.

Public Interface:
=================
// We need a socket.
Socket socket=...
// Create instances
SocketInputStream input(&socket);
SocketOutputStream output(&socket);
// Read something
std::string token;
input>>token;
// write something
output>>"something";

==============
Required files (all)
- Sockets.h, Sockets.cpp
- SocketStream.h, SocketStream.cpp

Build commands
- devenv Test_SocketStream.vcxproj /rebuild debug

Maintenance History:
====================
ver 1.0 : 4/15/2013
- first release
ver 1.1 : 3/15/2014
- now caller can get expectedBytesLength to skip unread request body
*/

#include <istream>
#include <ostream>
#include "Sockets.h"

/////////////////////////////////////////////////////////////////////////
// A class to wrap the socket I/O in a streambuf.
class SocketBuffer : public std::streambuf
{
public:
    // Constructor with the socket.
    explicit SocketBuffer(Socket* pSocket);
    // Set length of expected bytes to be read from the socket. Set -1 to
    // keep reading until socket errors occurs. Default value is -1. When
	// reading, this value will decrease. Once it became zero, the buffer
	// will always return EOF, and then its state can be reset by this 
	// function.
    void setExpectedBytesLength(int length);
	// Returns length of expected bytes to be read from the socket. If
	// setExpectedBytesLength() has not been called, it will return -1.
	// If setExpectedBytesLength() has been called, it will return 
	// length ranged from the set value to zero. 
	int getExpectedBytesLength();
protected:
    /********************** overrided functions ************************/
    // Set buffer.
    std::streambuf* setbuf(char_type* s, std::streamsize n);
    // Put character on overflow.
    int_type overflow(int_type c);
    // batch output
    std::streamsize xsputn (const char* s, std::streamsize n);
    // Synchronize stream buffer.
    int sync();
    // Get character on underflow
    int_type underflow();
    // batch input
    std::streamsize xsgetn (char* s, std::streamsize n);
private:
    Socket* pSocket;
    const static size_t BUFFER_SIZE=8192;
    char inputBuffer_[BUFFER_SIZE];
    // The field "expectBytesLeft" should be controlled by
    // "Content-Length" header of HTTP. It stores the value of
    // "Content-Length", or stores -1 if no "Content-Length".
    int expectedBytesLength;
    int readSize;
};

/////////////////////////////////////////////////////////////////////////
// A class to wrap the socket input in an istream.
class SocketInputStream : private SocketBuffer, public std::istream
{
public:
    // Constructor with the socket.
    explicit SocketInputStream(Socket* pSocket);
	// Set length of expected bytes to be read from the socket. Set -1 to
	// keep reading until socket errors occurs. Default value is -1. When
	// reading, this value will decrease. Once it became zero, the stream
	// will always return EOF, and then its state can be reset by this 
	// function.
	void setExpectedBytesLength(int length);
	// Returns length of expected bytes to be read from the socket. If
	// setExpectedBytesLength() has not been called, it will return -1.
	// If setExpectedBytesLength() has been called, it will return 
	// length ranged from the set value to zero. 
	int getExpectedBytesLength();
};

/////////////////////////////////////////////////////////////////////////
// A class to wrap the socket output in an ostream.
class SocketOutputStream: private SocketBuffer, public std::ostream 
{
public:
    // Constructor with the socket.
    explicit SocketOutputStream(Socket* socket)
        : SocketBuffer(socket), std::ostream(this)
    {}
};

#endif
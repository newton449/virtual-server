/////////////////////////////////////////////////////////////////////
//  SocketStream.h - wraps socket input and output into a istream  //
//          and an ostream.                                        //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2012                                 //
//  Platform:      Windows 8                                       //
//  Application:   CSE687 Pr3, Spring 2013                         //
//  Author:        Sheng Wang                                      //
/////////////////////////////////////////////////////////////////////

#include <string.h>
#include <iostream>
#include "SocketStream.h"

////////////////////////////////////////////////////////////////////////
// Function implementations of SocketBuffer

// Constructor with the socket.
SocketBuffer::SocketBuffer(Socket* pSocket)
: pSocket(pSocket), expectedBytesLength(-1), readSize(0)
{}

// Set length of expected bytes to be read from the socket. Set -1 to
// keep reading until socket errors occurs. Default value is -1.
void SocketBuffer::setExpectedBytesLength(int length){
    expectedBytesLength = length;
}

int SocketBuffer::getExpectedBytesLength(){
    return expectedBytesLength;
}

// Set buffer.
std::streambuf* SocketBuffer::setbuf(char_type* s, std::streamsize n)
{
    std::cout << n << "  ";
    return this;
}

// Put character on overflow.
SocketBuffer::int_type SocketBuffer::overflow(int_type c)
{
    if (traits_type::eq_int_type(c, traits_type::eof())) {
        // It is just for check EOF.
        return (sync() == 0
            ? traits_type::not_eof(c)
            : traits_type::eof());
    }
    else {
        // Write one char to the socket
        char ch = (char)c;
        try{
            pSocket->sendAll(&ch, 1);
        }
        catch (std::exception&){
            return traits_type::eof();
        }
        return traits_type::not_eof(c);
    }
}

// batch output
std::streamsize SocketBuffer::xsputn(const char* s, std::streamsize n){
    if (n > 0){
        try{
            pSocket->sendAll(s, (size_t)n);
            return n;
        }
        catch (std::exception&){
            return 0;
        }
    }
    return 0;
}

// Synchronize stream buffer.
int SocketBuffer::sync()
{
    return pSocket->isValid() ? 0 : -1;
}

// Get character on underflow
SocketBuffer::int_type SocketBuffer::underflow()
{
    if (expectedBytesLength == 0){
        // No byte should be read even if there are available bytes.
        setg(inputBuffer_, inputBuffer_, inputBuffer_);
        return traits_type::eof();
    }
    if (gptr() == NULL || gptr() >= egptr()) {
        // Read one char from socket.
        // PENDING read more bytes
        readSize = BUFFER_SIZE;
        if (expectedBytesLength > 0 && expectedBytesLength < readSize){
            readSize = expectedBytesLength;
            int sockLeft = pSocket->getLeftBytesSize();
            if (sockLeft < readSize){
                readSize = sockLeft;
            }
            if (readSize == 0){
                readSize = 1;
            }
        }
        else{
            readSize = 1;
        }
        try{
            pSocket->receiveAll(inputBuffer_, readSize);
        }
        catch (std::exception&){
            // Errors occurred. Return EOF.
            // PENDING should we throw exception if expectBytesLeft>=0?
            return traits_type::eof();
        }
        if (expectedBytesLength > 0){
            // One byte will be comsumed. Decrease expectBytesLeft.
            expectedBytesLength -= readSize;
        }
        // Return the char.
        setg(inputBuffer_, inputBuffer_, inputBuffer_ + readSize);
        return traits_type::to_int_type(*inputBuffer_);
    }
    else {
        return traits_type::to_int_type(*inputBuffer_);
    }
}

// batch input
std::streamsize SocketBuffer::xsgetn(char* s, std::streamsize n){
    if (n > 0){
        // PENDING to be tested more and more
        if (expectedBytesLength >= 0 && expectedBytesLength < n){
            n = expectedBytesLength;
        }
        int pos = gptr() == NULL ? 0 : gptr() - inputBuffer_;
        int bufLeft = readSize - pos;
        if (n<bufLeft){
            // size wanted is smaller than buffered
            memcpy(s, inputBuffer_ + pos, (size_t)n);
            setg(inputBuffer_, inputBuffer_ + pos + n, inputBuffer_ + readSize);
            if (expectedBytesLength>0){
                expectedBytesLength -= (int)n;
            }
            return n;
        }
        else{
            // size wanted is larger than buffered
            readSize = 0;
            memcpy(s, inputBuffer_ + pos, bufLeft);
            try{
                pSocket->receiveAll(s + bufLeft, (int)n - bufLeft);
            }
            catch (std::exception&){
                // error. clear.
                setg(inputBuffer_, inputBuffer_, inputBuffer_);
                return 0;
            }
            setg(inputBuffer_, inputBuffer_, inputBuffer_);
            if (expectedBytesLength > 0){
                expectedBytesLength -= (int)n - bufLeft;
            }
            return n;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////
// Function implementations of SocketInputStream

// Constructor with the socket.
SocketInputStream::SocketInputStream(Socket* pSocket)
: SocketBuffer(pSocket), std::istream(this)
{}

// Set length of expected bytes to be read from the socket. Set -1 to
// keep reading until socket errors occurs. 
void SocketInputStream::setExpectedBytesLength(int length){
    SocketBuffer::setExpectedBytesLength(length);
    // Reset state if EOF reached
    if (eof()){
        clear();
    }
}

int SocketInputStream::getExpectedBytesLength(){
    return SocketBuffer::getExpectedBytesLength();
}

#ifdef TEXT_SOCKETSTREAM

#include <iostream>

using namespace std;

void assertTrue(bool b, std::string msg){
    if(!b){
        std::cout<<"Error: "<<msg<<"\n";
    }
}

void test1(SocketInputStream& in, SocketOutputStream& out){
    std::string line;
    char buf[11];
    // testing reading block
    out<<"eeeeefffff";
    out.flush();
    in.read(buf, 5);
    buf[5]=0;
    assertTrue(string(buf)=="eeeee", "#4");
    out<<"ggggghhhhh";
    out.flush();
    in.read(buf, 10);
    buf[10]=0;
    assertTrue(string(buf)=="fffffggggg", "#5");
    in.read(buf, 5);
    buf[5]=0;
    assertTrue(string(buf)=="hhhhh", "#6");
}

void test2(SocketInputStream& in, SocketOutputStream& out){
    std::string line;
    // testing reading char by char
    out<<"aaaaa\nbbbbb";
    out.flush();
    getline(in, line); // read chars from socket
    assertTrue(line=="aaaaa", "#1");
    out<<"ccccc\nddddd\n";
    out.flush();
    getline(in, line); // read chars from buffer and socket
    assertTrue(line=="bbbbbccccc", "#2");
    getline(in, line); // read chars from buffer
    assertTrue(line=="ddddd", "#3");
}

void test3(SocketInputStream& in, SocketOutputStream& out){
    std::string line;
    char buf[11];
    // mixed reading
    out<<"iiiii\njjjjj";
    out.flush();
    getline(in, line); // read chars from socket
    assertTrue(line=="iiiii", "#7");
    out<<"lllllmmmmm\n";
    out.flush();
    in.read(buf, 10);
    buf[10]=0;
    assertTrue(string(buf)=="jjjjjlllll", "#8");
    getline(in, line); // read chars from buffer
    assertTrue(line=="mmmmm", "#9");

    out<<"nnnnnooooo";
    out.flush();
    in.read(buf, 5);
    buf[5]=0;
    assertTrue(string(buf)=="nnnnn", "#10");
    out<<"ppppp\nqqqqq";
    out.flush();
    getline(in, line); // read chars from buffer and socket
    assertTrue(line=="oooooppppp", "#11");
    in.read(buf, 5);
    buf[5]=0;
    assertTrue(string(buf)=="qqqqq", "#12");
}

void test4(SocketInputStream& in, SocketOutputStream& out){
    std::string line;
    // test bytes control
    out<<"rrrrrsssss";
    in.setExpectedBytesLength(5);
    getline(in, line);
    assertTrue(line=="rrrrr", "#13");
    in.setExpectedBytesLength(3);
    getline(in, line);
    assertTrue(line=="sss", "#14");
    out<<"tttttuuuuu";
    in.setExpectedBytesLength(7);
    getline(in, line);
    assertTrue(line=="ssttttt", "#15");
}

void main(){
    std::cout << "  Testing SocketInputStream, SocketOutputStream\n";
    try
    {
        SocketListener listener(2048);
        Socket sendr;
        if(!sendr.connect("127.0.0.1",2048))
        {
            std::cout << " connection failed\n\n";
            return;
        }
        Socket recvr = listener.waitForConnect();

        SocketOutputStream out(&sendr);
        SocketInputStream in(&recvr);

        test1(in, out);
        test2(in, out);
        test3(in, out);
        test4(in, out);
        // TODO More test

        sendr.disconnect();
        // Try to receiving after disconnect.
        std::string line;
        in.setExpectedBytesLength(-1); // reread
        getline(in, line);
        while(in){
            std::cout<<"\t"<<line<<std::endl;
            if(line.empty()){
                break;
            }
            getline(in, line);
        }
        recvr.disconnect();
    }
    catch(std::exception& e)
    {
        std::cout << "\n  " << e.what() << "\n\n";
    }
}

#endif
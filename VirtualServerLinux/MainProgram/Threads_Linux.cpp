/////////////////////////////////////////////////////////////////////////
// Threads.cpp - Wraps Win32 threads, providing a simple interface     //
//               similar to the .Net Thread class                      //
// ver 1.0                                                         //
// Language:    C++, Netbeans                                      //
// platform:    Kubuntu11.10                                       //
// Application: Spring 2012 DO Project 2                           //
// Author:      Yun Xing, Syracuse University, CST 4-282           //
//              yxing03@syr.edu                                    //
// Resourcr: Jim Fawcett
///////////////////////////////////////////////////////////////////////

#ifdef TEST_THREADS

#include "Threads.h"
#include "locks.h"
#include <iostream>
#include <string>

/////////////////////////////////////////////////////////////////////////
// class testproc demonstrates how to provide application specific
//                processing for threads

class testproc : public Thread_Processing<testproc>
{
public:
  testproc(const testproc& tp) : _str(tp._str)
  {
    myCount = ++count;
    sout << locker << "\n  " << _str << unlocker;
  }
  testproc(const std::string& str) : _str(str)
  {
    myCount = ++count;
    sout << locker << "\n  " << _str << unlocker;
  }
  virtual void run()
  {
    for(int i=0; i<20; ++i)
    {
      sout << locker << " " << myCount << unlocker;
      ::Sleep(10);
    }
    sout.flush();
  }
  int myId() { return myCount; }
private:
  std::string _str;
  static int count;
  int myCount;
};

int testproc::count = 0;

//
//----< Test Stub >------------------------------------------------------

class globalLineFeed
{
public:
  ~globalLineFeed() { std::cout << "\n\n"; }
} globalInstance;

void main(int argc, char* argv[])
{
  std::cout << "\n  Testing Threads class "
            << "\n =======================\n";

  testproc tpStack("thread created on stack frame");
  thread threadOnStack(tpStack);
  sout << locker << "\n  Thread ID = " << threadOnStack.id() 
       << "\n  myCount = " << tpStack.myId() << unlocker;
  threadOnStack.setPriority(very_high);
  
  testproc tpHeap("thread created on heap");
  
  // terminating_thread must be created on heap
  // as it will call delete on itself
  // when thread processing finishes

  sout << "\n  testproc will be cloned by tthread";
  tthread* pThreadOnHeap 
    = new tthread(tpHeap);
  sout << locker << "\n  Thread ID = " << pThreadOnHeap->id() 
       << "\n  myCount = " << tpHeap.myId() << "\n\n" << unlocker;
  pThreadOnHeap->setPriority(very_low);
  HANDLE h = pThreadOnHeap->handle();

  // start threads

  threadOnStack.start();
  pThreadOnHeap->start();

  threadOnStack.wait();

  // don't use non-static members of terminating_thread after calling start
  // don't call delete on terminating_thread

  tthread::wait(h);
}

#endif

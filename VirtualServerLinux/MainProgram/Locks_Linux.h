#ifndef LOCKS_H
#define LOCKS_H
/////////////////////////////////////////////////////////////////////
//  locks.h       - classes supporting synchronization of shared   //
// ver 1.0                                                         //
// Language:    C++, Netbeans                                      //
// platform:    Kubuntu11.10                                       //
// Application: Spring 2012 DO Project 2                           //
// Author:      Yun Xing, Syracuse University, CST 4-282           //
//              yxing03@syr.edu      
// Resource: Jim Fawcett
///////////////////////////////////////////////////////////////////////
/*
    Module Operations
    =================
    This module provides local locking via LLock .

    Public Interface
    ================
    LLock l;                    // local lock that protects holder 
    l.lock();                   // set lock
    l.unlock();                 // unset lock
                                // Global lock protects holder of any GLock<1>
    

    sout << "a string";         // globally available synchronized output
    sout << locker << "a string" << 3.1415927 << myObject << unlocker;
                                // locker & unlocker are manipulators needed
                                // to protect a sequence of insertions
    
*/      
//
///////////////////////////////////////////////////////////////////////
//  Build Process                                                    //
///////////////////////////////////////////////////////////////////////
//  Required Files:                                                  //
//    locks.h, locks.cpp                                             //
//                                                                   //
//                                                                   //
///////////////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    
    ver 1.0 : 27 Mar 12
    - first release
*/
//
#define WIN32_LEAN_AND_MEAN
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>

/////////////////////////////////////////////////////////////////////
//  LLock - local locking class declaration

class LLock
{
  public:
    LLock();
    LLock(const LLock& ll);
    ~LLock();
    LLock& operator=(const LLock& ll);
    void lock();
    void unlock();

  private:
  pthread_mutex_t pmutex;
};

//----< constructor >------------------------------------------------

inline LLock::LLock() {  pthread_mutex_init(&pmutex,NULL); }

//----< copy constructor >-------------------------------------------

inline LLock::LLock(const LLock& ll)
{ 
   pthread_mutex_init(&pmutex,NULL);  // intentionally same as void ctor
}

//----< destructor >-------------------------------------------------

inline LLock::~LLock() { pthread_mutex_destroy(&pmutex);}

//----< assignment >-------------------------------------------------

inline LLock& LLock::operator =(const LLock& ll)
{
  return *this;  // do nothing
}

//----< set lock >---------------------------------------------------

inline void LLock::lock() { pthread_mutex_lock(&pmutex); } //pthread_mutex_lock

//----< unset lock >-------------------------------------------------

inline void LLock::unlock() { pthread_mutex_unlock(&pmutex);} //pthread_mutex_unlock

//


///////////////////////////////////////////////////////////////
//  class declaration for lockingPtr                         //
///////////////////////////////////////////////////////////////

template <class Obj, class Lock> class lockingPtr {

  public:
    lockingPtr(volatile Obj &obj, Lock &lck);
    ~lockingPtr();
    Obj& operator*();
    Obj* operator->();

  private:
    Obj* _pObj;
    Lock *_pLock;
    lockingPtr(const lockingPtr&);
    lockingPtr& operator=(const lockingPtr&);
};

//----< constructor takes object to lock and Mutex >-----------

template <class Obj, class Lock> inline
lockingPtr<Obj, Lock>::lockingPtr(volatile Obj &obj, Lock &lck) 
             : _pObj(const_cast<Obj*>(&obj)), _pLock(&lck) { 

#ifdef TEST_LOCKINGPTR
  
#endif

  lck.lock(); 
}

//----< destructor >-------------------------------------------

template <class Obj, class Lock> inline
lockingPtr<Obj, Lock>::~lockingPtr() { 
  
  _pLock->unlock(); 

#ifdef TEST_LOCKINGPTR
   cout << "\n  destroying a LockingPtr object - calls unlock()";
   cout.flush();
#endif
}

//

//----< get locked object >------------------------------------

template <class Obj, class Lock> inline
Obj& lockingPtr<Obj, Lock>::operator*() { 
  
#ifdef TEST_LOCKINGPTR
  cout << "\n accessing contents of locked object";
  cout.flush();
#endif

  return *_pObj; 
}

//----< get access to locked object's members >----------------

template <class Obj, class Lock> inline
Obj* lockingPtr<Obj, Lock>::operator->() { 

#ifdef TEST_LOCKINGPTR
  cout << "\n  accessing member of locked object";
  cout.flush();
#endif
  
  return _pObj; 
}

#endif

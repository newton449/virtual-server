/* 
 * File:   Threads.h
 * Author: penny
 *
 * Created on March 26, 2012, 1:44 PM
 */
#ifndef THREAD_H
#define THREAD_H
/////////////////////////////////////////////////////////////////////////
// Threads.h   -  Wraps Win32 threads, providing a simple interface    //
// ver 1.0                                                         //
// Language:    C++, Netbeans                                      //
// platform:    Kubuntu11.10                                       //
// Application: Spring 2012 DO Project 2                           //
// Author:      Yun Xing, Syracuse University, CST 4-282           //
//              yxing03@syr.edu    
// Resource: Jim Fawcett
///////////////////////////////////////////////////////////////////////

/*
 * Module Operations:
 * ==================
 * This module provides two thread classes, ThreadBase<default_thread> and
 * ThreadBase<terminating_thread>, and an abstract Thread_Processing class, 
 * that both wrap native posix threads.
 *
 *   ThreadBase<default_thread>     - may be created on either stack or heap
 *   - This thread type uses a pointer to its processing object, derived
 *     from Thread_Processing, so your application must not overwrite that
 *     object.
 *   - The module provides a typedef ThreadBase<default_thread> thread to
 *     provide a shorter alias for this common case.
 *
 *   ThreadBase<terminating_thread> - must be created on heap 
 *   - This thread type will call delete on itself when its thread
 *     processing has completed, so it must be created on the heap.
 *   - It makes a clone of its processing object, derived from 
 *     Thread_Processing object, so it does not matter whether the 
 *     original is overwritten.
 *   - This thread will delete its processing object when that
 *     processing is complete.
 *   - Don't use non-static member functions of this class after
 *     calling start, as its destruction is non-deterministic.
 *   The design of this class supports a "Fire and Forget" model.
 *   Threads and Thread_Processing objects reside on the heap, and
 *   destroy themselves as soon as their processing completes.
 *
 *   Thread_Processing - an abstract base class
 *   - Your application overrides this base to define application 
 *     specific thread processing:
 *       class MyProc : public Thread_Processing { ... }.
 *   - The class forces you to override two functions:
 *       MyProc* clone() { return new MyProc(*this); }
 *       void run() { // application specific code }
 *
 *  Note that assignment and copy operations are disabled for the ThreadBase
 *  classes, but are permitted for instances of the Thread_Processing class
 *  and its derived classes.
 */
//
/* Public Interface (see test stub for details):
 * =============================================
 *
 * // create thread on local stack
 *
 * class threadProc : public Thread_Processing { ... }
 *                            // create instance of thread_processing object
 * thread t(threadProc);      // create thread with clone of threadProc
 * t.start();                 // start thread running
 * t.suspend();               // suspend thread until resume()'d
 * t.resume();                // resume thread operation after suspend()'d
 * t.sleep(100);              // sleep for 100 millisecond
 * t.setPriority(very_high);  // set thread priority to highest level
 * t.wait();                  // caller waits for thread t to terminate
 *
 * // create self-destructing thread on heap
 * // - Note: after calling start(), you must not call non-static
 * //         members, as the thread will delete itself at some
 * //         non-deterministic time.
 *
 * ThreadBase<terminating_thread>* pTT 
 *   = new ThreadBase<terminating_thread>(threadProc);
 * HANDLE tHandle = pTT->handle();      // get handle for wait before starting
 * pTT->start();                                    // start thread running
 *   // do some processing, then:
 * ThreadBase<terminating_thread>::wait(tHandle);       // static wait for thread
 * 
 */
/* Build Process
 * =============
 * Required Files:
 * - Threads.h, Threads.cpp,  // always required
 * - Locks.h, Locks.cpp       // required for test stub and many apps
 *
 * Build Command:
 * - cl /EHcs /DTEST_THREADS threads.cpp locks.cpp
 *
 * Maintenance History:
 * ====================
 * ver 1.0 : 28 Mar 12
 * - first release
 */
//

#include <unistd.h>
#include <pthread.h>
#include <stdexcept>

#define __stdcall 
///////////////////////////////////////////////////////////////////
// Classes derived from IThread_Processing, indirectly through
// class Thread_Processing, define code that created thread executes.
// The derived processing class must have correct copy semantics.

struct IThread_Processing {
    virtual IThread_Processing* clone() = 0;
    virtual void run() = 0;
};

template<typename myDerived>
class Thread_Processing : public IThread_Processing {
public:

    virtual ~Thread_Processing() {
    }

    IThread_Processing* clone() {
        myDerived* pMyDerived = dynamic_cast<myDerived*> (this);
        if (pMyDerived == 0) {
            std::cout << "class must derive from Thread_Processing<DerivedType>" << std::endl;
            throw std::exception();
        }
        return new myDerived(*pMyDerived);
    }
};

/////////////////////////////////////////////////////////////
// Template parameter for thread class, determines 
// termination behavior
//

enum thread_type {
    DefaultTerminate, // no self destruction
    terminating_thread // will delete itself when thread is done
};

/////////////////////////////////////////////////////////////
// wrap most of the Win32 thread prioritites
//

enum thread_priority {
    very_low, low, normal, high, very_high
};

//
/////////////////////////////////////////////////////////////
// class ThreadBase<thread_type> wraps Win32 threads
//

template <thread_type type>
class ThreadBase {
public:
    ThreadBase();
    virtual ~ThreadBase();
    void start();
    unsigned long id();
    void sleep(long Millisecs);
    void suspend();
    void resume();
    thread_priority getPriority();
    void setPriority(thread_priority p);
    void endThread(unsigned int exit_code);
    void join();
private:
    IThread_Processing* pProc;
    pthread_t pthread;
    static void* __stdcall threadProc(void *pSelf);
    unsigned int _threadID;
    thread_priority _priority;
    // disable copy and assignment
    ThreadBase(const ThreadBase<type>& t);
    ThreadBase<type>& operator=(const ThreadBase<type>& t);
    virtual void run() = 0;
};

/////////////////////////////////////////////////////////////
// alias for default thread
//
typedef ThreadBase<DefaultTerminate> thread;
typedef ThreadBase<terminating_thread> tthread;

//
//----< new ThreadBase object holds copy of Thread_Processing object >-------
//
//  p.clone creates, on heap, a copy of class
//  derived from Thread_Processing object
//

template <thread_type type>
ThreadBase<type>::ThreadBase()
: _priority(normal) {

}

//----< destroy thread and its Thread_Processing object >----------------

template <thread_type type>
ThreadBase<type>::~ThreadBase() {
    pthread_exit(NULL);
    if (type == terminating_thread) {
        delete this; // delete clone of thread_processing object
    }
}
//----< return Win32 thread id >-----------------------------------------

template <thread_type type>
unsigned long ThreadBase<type>::id() {
    return _threadID;
}

//----< start Win32 thread running >-------------------------------------

template <thread_type type>
void ThreadBase<type>::start() //not creat in constructor but creat here
{
    pthread_create(&pthread, NULL, threadProc, (void*) this);

}
//----< Win32 thread processing wrapper for process object >-------------

template <thread_type type>
void* __stdcall ThreadBase<type>::threadProc(void *pSelf) {
    ThreadBase<type>* pBase = (ThreadBase<type>*)pSelf;
    pBase->run(); // child's synchronous call
    if (type == terminating_thread) {
        delete pBase; // must not access member data after calling start(),
    } // as time of destruction is non-deterministic
    return NULL;
}

//----< terminate thread >-----------------------------------------------
//
// It is usually a good idea to avoid calling this function, as it will
// abruptly terminate thread processing, not calling any cleanup code
// you may have put into Thread_Processing::run().

template <thread_type type>
void ThreadBase<type>::endThread(unsigned int exit_code) {
    pthread_exit(exit_code);
}

// TODO impl it

template <thread_type type>
void ThreadBase<type>::join() {
    pthread_join(pthread, NULL);
}

#endif



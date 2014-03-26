/* 
 * File:   BlockingQueue.h
 * Author: penny
 *
 * Created on March 26, 2012, 1:42 PM
 */
#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H
/////////////////////////////////////////////////////////////////////
//  blockingQueue.h - queue that blocks on deQ of empty queue    //
//  ver 1.0                                                        //
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
    This module provides a simple thread-safe blocking queue.  When a client thread attempts
    to deQ an empty queue, it will block until another thread enQs an
    item.  This prevents very high CPU utilization while a reading
    thread spin locks on an empty queue.

    Public Interface
    ================
    BlockingQueue<std::string> Q       // create blocking queue holding std::strings
    Q.enQ("an item");           // push onto queue
    std::string str = Q.deQ();  // pop from queue
    size_t s = Q.size();        // number of elements in queue
    Q.clear()                   // remove all contents from queue
*/      
//
///////////////////////////////////////////////////////////////////////
//  Build Process                                                    //
///////////////////////////////////////////////////////////////////////
//  Required Files:                                                  //
//    blockingQueue.h, blockingQueue.cpp                             //
//                                                                   //
//  Compiler Command:                                                //
//    cl /GX /DTEST_BLOCKINGQUEUE blockingQueue.cpp                  //
//                                                                   //
///////////////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    
    ver 1.0 : April 2 2012
 * -first release
    

*/
//
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <queue>
#include "Locks_Linux.h"

/////////////////////////////////////////////////////////////////////
//  BlockingQueue<T> class 

template <typename T>
class BlockingQueue
{
public:
  BlockingQueue();
  BlockingQueue(const BlockingQueue<T>& bq);
  ~BlockingQueue();
  BlockingQueue<T>& operator=(const BlockingQueue<T>& Q);
  void enQ(const T& t);
  T deQ();
  void clear();
  size_t size();
private:
  std::queue<T> _Q;
  LLock _l;
  pthread_mutex_t pmutex;
  pthread_cond_t pcond;
};
//----< constructor >------------------------------------------------

template <typename T>
BlockingQueue<T>::BlockingQueue()
{
    try{
    pthread_mutex_init(&pmutex,NULL);
    pthread_cond_init(&pcond,NULL);
    }
    catch(...)
    {
        std::cout<<"CreateEvent failed in BlockingQueue<T>::BlockingQueue()"<<std::endl;
    throw std::exception();
    }
}
//----< copy constructor >-------------------------------------------

template <typename T>
BlockingQueue<T>::BlockingQueue(const BlockingQueue<T>& bq) : _Q(bq._Q)
{
  try{
    pthread_mutex_init(&pmutex,NULL);
    pthread_cond_init(&pcond,NULL);
    }
    catch(...)
    {
    throw std::exception("CreateEvent failed in BlockingQueue<T>::BlockingQueue()");
    }
}
//----< destructor >-------------------------------------------------

template <typename T>
BlockingQueue<T>::~BlockingQueue() { 
    pthread_mutex_destroy(&pmutex);
    pthread_cond_destroy(&pcond);
}  

//----< assignment >-------------------------------------------------

template <typename T>
BlockingQueue<T>& BlockingQueue<T>::operator =(const BlockingQueue<T>& bq)
{
  if(this==&bq) return *this;
  _Q = bq._Q;
  pthread_mutex_lock(&pmutex);
  pthread_cond_signal(&pcond);
  pthread_mutex_unlock(&pmutex);
  return *this;
}
//
//----< enqueue >----------------------------------------------------

template <typename T>
void BlockingQueue<T>::enQ(const T& t)
{
  _l.lock();
  _Q.push(t);
  pthread_mutex_lock(&pmutex);
  pthread_cond_signal(&pcond);
  pthread_mutex_unlock(&pmutex);  //pthread_mutex_lock pthread_cond_signal pthread_mutex_unlock
  _l.unlock();
}
//----< dequeue >----------------------------------------------------

template <typename T>
T BlockingQueue<T>::deQ()
{
  T msg;
  while(true)
  {
    _l.lock();
    if(_Q.size() != 0)
    {
      msg = _Q.front();
      _Q.pop();
      _l.unlock();
      break;
    }
    //ResetEvent(_hEvent);  
    _l.unlock();
    pthread_mutex_lock(&pmutex);
  pthread_cond_wait(&pcond,&pmutex);
  pthread_mutex_unlock(&pmutex);  //pthread_mutex_lock , wait, unlock
  }
  return msg;
}
//
//----< purge queue >------------------------------------------------

template <typename T>
void BlockingQueue<T>::clear()
{ 
  while(_Q.size() > 0)
    _Q.pop();
}

//----< return number of elements in queue >-------------------------

template <typename T>
size_t BlockingQueue<T>::size() { return _Q.size(); }

#endif



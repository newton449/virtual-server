///////////////////////////////////////////////////////////////////////////////
//  ILogger.h - provide ways to log.                                         //
//  ver 0.9                                                                  //
//  Language:      Visual C++ 2013 & gcc 4.7.2                               //
//  Platform:      Windows 8       & Linux Debian 3.2 x86_x64                //
//  Application:   CSE775 Final Project, Spring 2014                         //
//  Author:        Sheng Wang, Qiuyong Yang, Bei Li                          //
///////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
Now ILogger uses easylogging++ for logging. It supports multi-threads and cross-dlls.

To log, use LOG(LEVEL) << "message". LEVEL can be TRACE, DEBUG, WARNNING, ERROR and FATAL.

In DLL, in order to use logger provided by MainProgram, do following:
// Get StoragePointer from MainProgram
el::base::type::StoragePointer p = (el::base::type::StoragePointer*)mainFactory->getObject("LoggingStorage");
// Set it to DLL's logging handler.
el::Helpers::setStorage(*p);

Note: remember to put "ILogger.cpp" in source files.

Required files (all)
==============
- ILogger.h, ILogger.cpp

Maintenance History:
====================
ver 0.9 : 4/18/2013
- first commented

*/
#pragma once

// We should always enable logging. However, we may disable it to detect memory leak.
#define ENABLE_LOGGING

// Enable logging operations when it is defined.
#ifdef ENABLE_LOGGING /*********** ENABLE_LOGGING **********/

// enable thread safe
#define _ELPP_THREAD_SAFE

// Do not put logs to "logs/myeasylog.log"
#define _ELPP_NO_DEFAULT_LOG_FILE

// We do not need VERBOSE logging.
#define _ELPP_DISABLE_VERBOSE_LOGS

// if debug is defined
#ifdef _DEBUG

// It will stop when assertion fails.
#define _ELPP_STOP_ON_FIRST_ASSERTION

// It will show errors of easylogging.
#define _ELPP_ENABLE_ERRORS

// Disable Crash Handling
#define _ELPP_DISABLE_DEFAULT_CRASH_HANDLING

#endif // _DEBUG

#include "easylogging++.h"

#else /*********** ENABLE_LOGGING **************/

// Usage an ostringstream for logging. It does nothing. For test only!
#include <sstream>
extern std::ostringstream NULL_STREAM;
#define LOG(LEVEL) NULL_STREAM

#endif /*********** ENABLE_LOGGING endif **********/


/**
 * Now ILogger uses easylogging++ for logging. It supports multi-threads and cross-dlls.
 * To log, use LOG(LEVEL) << "message". LEVEL can be TRACE, DEBUG, WARNNING, ERROR and FATAL.
 * To use it in a dll, remember to put "ILogger.cpp" in source files.
 */

#pragma once

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING

// enable thread safe
#define _ELPP_THREAD_SAFE

// Do not put logs to "logs/myeasylog.log"
#define _ELPP_NO_DEFAULT_LOG_FILE

// We do not need VERBOSE logging.
#define _ELPP_DISABLE_VERBOSE_LOGS

#ifdef _DEBUG

// It will stop when assertion fails.
#define _ELPP_STOP_ON_FIRST_ASSERTION

// It will show errors of easylogging.
#define _ELPP_ENABLE_ERRORS

// Disable Crash Handling
#define _ELPP_DISABLE_DEFAULT_CRASH_HANDLING

#endif

#include "easylogging++.h"

#else

#include <sstream>
extern std::ostringstream NULL_STREAM;
#define LOG(LEVEL) NULL_STREAM

#endif


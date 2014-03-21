/**
 * Now ILogger uses easylogging++ for logging. It supports multi-threads and cross-dlls.
 * To log, use LOG(LEVEL) << "message". LEVEL can be TRACE, DEBUG, WARNNING, ERROR and FATAL.
 * To use it in a dll, remember to put "ILogger.cpp" in source files.
 */

#pragma once

// enable thread safe
#define _ELPP_THREAD_SAFE

#include "easylogging++.h"


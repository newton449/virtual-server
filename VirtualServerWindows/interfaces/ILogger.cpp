#include "ILogger.h"

#ifdef ENABLE_LOGGING
// initialize easylogging++
_INITIALIZE_EASYLOGGINGPP
#else
// initialize fake logger
std::ostringstream NULL_STREAM;
#endif


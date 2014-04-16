#include "ILogger.h"

#ifdef ENABLE_LOGGING
_INITIALIZE_EASYLOGGINGPP
#else
std::ostringstream NULL_STREAM;
#endif


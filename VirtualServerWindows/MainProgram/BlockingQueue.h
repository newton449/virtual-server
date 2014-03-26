#pragma once

#ifdef WIN32
#include "BlockingQueue_Windows.h"
#else
#include "../../VirtualServerLinux/MainProgram/BlockingQueue_Linux.h"
#endif
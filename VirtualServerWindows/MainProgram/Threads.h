#pragma once

#ifdef WIN32
#include "Threads_Windows.h"
#else
#include "../../VirtualServerLinux/MainProgram/Threads_Linux.h"
#endif
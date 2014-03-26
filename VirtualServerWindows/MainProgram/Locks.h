#pragma once

#ifdef WIN32
#include "Locks_Windows.h"
#else
#include "../../VirtualServerLinux/MainProgram/Locks_Linux.h"
#endif
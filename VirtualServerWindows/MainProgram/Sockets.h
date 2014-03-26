#pragma once

#ifdef WIN32
#include "Sockets_Windows.h"
#else
#include "../../VirtualServerLinux/MainProgram/Sockets_Linux.h"
#endif
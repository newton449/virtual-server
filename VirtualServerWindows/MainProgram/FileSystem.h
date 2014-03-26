#pragma once

#ifdef WIN32
#include "FileSystem_Windows.h"
#else
#include "../../VirtualServerLinux/MainProgram/FileSystem_Linux.h"
#endif
#pragma once

#ifdef WIN32
#include "FileSystem_Windows.h"
#else
#include "../../VirtualServerLinux/MainProgram/FileSystem_Linux.h"
#endif

#ifdef WIN32
#define FILE_SEPARATOR "\\"
#define FILE_SEPARATOR_CHAR '\\'
#else
#define FILE_SEPARATOR "/"
#define FILE_SEPARATOR_CHAR '/'
#endif
#pragma once

#ifdef WIN32
#define FILE_SEPARATOR '\\'
#include "FileSystem_Windows.h"
#else
#define FILE_SEPARATOR "/"
#include "../../VirtualServerLinux/MainProgram/FileSystem_Linux.h"
#endif
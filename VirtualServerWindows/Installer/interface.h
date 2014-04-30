/* 
 * File:   interface.h
 * Author: kareny
 *
 * Created on April 29, 2014, 4:19 PM
 */

#ifndef INTERFACE_H
#define	INTERFACE_H

#ifdef WIN32
#include "..\MainProgram\FileSystem.h"
#include "chilkat-9.5.0-x86-vc12\include\CkZip.h"
#else
#include "../../VirtualServerWindows/MainProgram/FileSystem.h"
#include "../../VirtualServerLinux/Installer/chilkat-9.5.0-x86_64-linux-gcc/include/CkZip.h"
#endif

#endif	/* INTERFACE_H */


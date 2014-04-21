#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1278082062/HttpServletsImpl.o \
	${OBJECTDIR}/_ext/1278082062/ModuleObjectFactoryImpl.o \
	${OBJECTDIR}/_ext/1278082062/ServletFactoryImpl.o \
	${OBJECTDIR}/_ext/768354932/ILogger.o \
	${OBJECTDIR}/_ext/147134308/FileSystem_Linux.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../TestTarget/Installer/Installer_x64.so

../../TestTarget/Installer/Installer_x64.so: ${OBJECTFILES}
	${MKDIR} -p ../../TestTarget/Installer
	${LINK.cc} -o ../../TestTarget/Installer/Installer_x64.so ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/_ext/1278082062/HttpServletsImpl.o: ../../VirtualServerWindows/Installer/HttpServletsImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1278082062
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1278082062/HttpServletsImpl.o ../../VirtualServerWindows/Installer/HttpServletsImpl.cpp

${OBJECTDIR}/_ext/1278082062/ModuleObjectFactoryImpl.o: ../../VirtualServerWindows/Installer/ModuleObjectFactoryImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1278082062
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1278082062/ModuleObjectFactoryImpl.o ../../VirtualServerWindows/Installer/ModuleObjectFactoryImpl.cpp

${OBJECTDIR}/_ext/1278082062/ServletFactoryImpl.o: ../../VirtualServerWindows/Installer/ServletFactoryImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1278082062
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1278082062/ServletFactoryImpl.o ../../VirtualServerWindows/Installer/ServletFactoryImpl.cpp

${OBJECTDIR}/_ext/768354932/ILogger.o: ../../VirtualServerWindows/interfaces/ILogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/768354932
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/768354932/ILogger.o ../../VirtualServerWindows/interfaces/ILogger.cpp

${OBJECTDIR}/_ext/147134308/FileSystem_Linux.o: ../MainProgram/FileSystem_Linux.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/147134308
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/147134308/FileSystem_Linux.o ../MainProgram/FileSystem_Linux.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../TestTarget/Installer/Installer_x64.so

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

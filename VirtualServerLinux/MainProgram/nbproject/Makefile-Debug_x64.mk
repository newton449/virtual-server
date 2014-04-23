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
CND_CONF=Debug_x64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/832715153/ClientManagerImpl.o \
	${OBJECTDIR}/_ext/832715153/DefaultHttpServletMapping.o \
	${OBJECTDIR}/_ext/832715153/HttpServer.o \
	${OBJECTDIR}/_ext/832715153/HttpServerSupport.o \
	${OBJECTDIR}/_ext/832715153/HttpServletsImpl.o \
	${OBJECTDIR}/_ext/832715153/MainObjectFactoryImpl.o \
	${OBJECTDIR}/_ext/832715153/MainProgram.o \
	${OBJECTDIR}/_ext/832715153/ModuleManagerImpl.o \
	${OBJECTDIR}/_ext/832715153/SocketStream.o \
	${OBJECTDIR}/_ext/832715153/StringUtils.o \
	${OBJECTDIR}/_ext/832715153/Utilities.o \
	${OBJECTDIR}/_ext/832715153/tinyxml2.o \
	${OBJECTDIR}/_ext/768354932/ILogger.o \
	${OBJECTDIR}/BlockingQueue_Linux.o \
	${OBJECTDIR}/FileSystem_Linux.o \
	${OBJECTDIR}/Locks_Linux.o \
	${OBJECTDIR}/MainProgram_Linux.o \
	${OBJECTDIR}/ModuleManagerImpl_Linux.o \
	${OBJECTDIR}/Sockets_Linux.o \
	${OBJECTDIR}/Threads_Linux.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-ldl -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../../TestTarget/MainProgram/MainProgram_Linux_x64

../../TestTarget/MainProgram/MainProgram_Linux_x64: ${OBJECTFILES}
	${MKDIR} -p ../../TestTarget/MainProgram
	${LINK.cc} -o ../../TestTarget/MainProgram/MainProgram_Linux_x64 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/832715153/ClientManagerImpl.o: ../../VirtualServerWindows/MainProgram/ClientManagerImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/ClientManagerImpl.o ../../VirtualServerWindows/MainProgram/ClientManagerImpl.cpp

${OBJECTDIR}/_ext/832715153/DefaultHttpServletMapping.o: ../../VirtualServerWindows/MainProgram/DefaultHttpServletMapping.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/DefaultHttpServletMapping.o ../../VirtualServerWindows/MainProgram/DefaultHttpServletMapping.cpp

${OBJECTDIR}/_ext/832715153/HttpServer.o: ../../VirtualServerWindows/MainProgram/HttpServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/HttpServer.o ../../VirtualServerWindows/MainProgram/HttpServer.cpp

${OBJECTDIR}/_ext/832715153/HttpServerSupport.o: ../../VirtualServerWindows/MainProgram/HttpServerSupport.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/HttpServerSupport.o ../../VirtualServerWindows/MainProgram/HttpServerSupport.cpp

${OBJECTDIR}/_ext/832715153/HttpServletsImpl.o: ../../VirtualServerWindows/MainProgram/HttpServletsImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/HttpServletsImpl.o ../../VirtualServerWindows/MainProgram/HttpServletsImpl.cpp

${OBJECTDIR}/_ext/832715153/MainObjectFactoryImpl.o: ../../VirtualServerWindows/MainProgram/MainObjectFactoryImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/MainObjectFactoryImpl.o ../../VirtualServerWindows/MainProgram/MainObjectFactoryImpl.cpp

${OBJECTDIR}/_ext/832715153/MainProgram.o: ../../VirtualServerWindows/MainProgram/MainProgram.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/MainProgram.o ../../VirtualServerWindows/MainProgram/MainProgram.cpp

${OBJECTDIR}/_ext/832715153/ModuleManagerImpl.o: ../../VirtualServerWindows/MainProgram/ModuleManagerImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/ModuleManagerImpl.o ../../VirtualServerWindows/MainProgram/ModuleManagerImpl.cpp

${OBJECTDIR}/_ext/832715153/SocketStream.o: ../../VirtualServerWindows/MainProgram/SocketStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/SocketStream.o ../../VirtualServerWindows/MainProgram/SocketStream.cpp

${OBJECTDIR}/_ext/832715153/StringUtils.o: ../../VirtualServerWindows/MainProgram/StringUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/StringUtils.o ../../VirtualServerWindows/MainProgram/StringUtils.cpp

${OBJECTDIR}/_ext/832715153/Utilities.o: ../../VirtualServerWindows/MainProgram/Utilities.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/Utilities.o ../../VirtualServerWindows/MainProgram/Utilities.cpp

${OBJECTDIR}/_ext/832715153/tinyxml2.o: ../../VirtualServerWindows/MainProgram/tinyxml2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/832715153
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/832715153/tinyxml2.o ../../VirtualServerWindows/MainProgram/tinyxml2.cpp

${OBJECTDIR}/_ext/768354932/ILogger.o: ../../VirtualServerWindows/interfaces/ILogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/768354932
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/768354932/ILogger.o ../../VirtualServerWindows/interfaces/ILogger.cpp

${OBJECTDIR}/BlockingQueue_Linux.o: BlockingQueue_Linux.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BlockingQueue_Linux.o BlockingQueue_Linux.cpp

${OBJECTDIR}/FileSystem_Linux.o: FileSystem_Linux.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileSystem_Linux.o FileSystem_Linux.cpp

${OBJECTDIR}/Locks_Linux.o: Locks_Linux.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Locks_Linux.o Locks_Linux.cpp

${OBJECTDIR}/MainProgram_Linux.o: MainProgram_Linux.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MainProgram_Linux.o MainProgram_Linux.cpp

${OBJECTDIR}/ModuleManagerImpl_Linux.o: ModuleManagerImpl_Linux.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ModuleManagerImpl_Linux.o ModuleManagerImpl_Linux.cpp

${OBJECTDIR}/Sockets_Linux.o: Sockets_Linux.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sockets_Linux.o Sockets_Linux.cpp

${OBJECTDIR}/Threads_Linux.o: Threads_Linux.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Werror -DMAIN_PROGRAM -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Threads_Linux.o Threads_Linux.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../../TestTarget/MainProgram/MainProgram_Linux_x64

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

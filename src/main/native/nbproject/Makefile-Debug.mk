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
CND_PLATFORM=MinGW_TDM-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/DAQmx.o \
	${OBJECTDIR}/src/NativeUtils.o


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
LDLIBSOPTIONS=-L/C/Windows/System32 -lnicaiu

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/jni_DAQmx.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/jni_DAQmx.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	gcc -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/jni_DAQmx.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared

${OBJECTDIR}/src/DAQmx.o: src/DAQmx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -I../../../target/header -I/C/Program\ Files/Java/jdk1.7.0_55/include -I/C/Program\ Files/Java/jdk1.7.0_55/include/win32 -I/C/Program\ Files\ \(x86\)/National\ Instruments/Shared/ExternalCompilerSupport/C/include  -o ${OBJECTDIR}/src/DAQmx.o src/DAQmx.cpp

${OBJECTDIR}/src/NativeUtils.o: src/NativeUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -I../../../target/header -I/C/Program\ Files/Java/jdk1.7.0_55/include -I/C/Program\ Files/Java/jdk1.7.0_55/include/win32 -I/C/Program\ Files\ \(x86\)/National\ Instruments/Shared/ExternalCompilerSupport/C/include  -o ${OBJECTDIR}/src/NativeUtils.o src/NativeUtils.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/jni_DAQmx.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

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
CND_PLATFORM=Cygwin_4.x-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/DAQmx.o \
	${OBJECTDIR}/src/NativeUtils.o \
	${OBJECTDIR}/src/analog/Acq-IntClk.o \
	${OBJECTDIR}/src/analog/ContGen-IntClk.o \
	${OBJECTDIR}/src/edu/sju/ee/ni/daqmx/DAQmxTaskHandle.o \
	${OBJECTDIR}/src/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libDataAcquisitionNative.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libDataAcquisitionNative.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libDataAcquisitionNative.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared

${OBJECTDIR}/src/DAQmx.o: src/DAQmx.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DAQmx.o src/DAQmx.cpp

${OBJECTDIR}/src/NativeUtils.o: src/NativeUtils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/NativeUtils.o src/NativeUtils.cpp

${OBJECTDIR}/src/analog/Acq-IntClk.o: src/analog/Acq-IntClk.c 
	${MKDIR} -p ${OBJECTDIR}/src/analog
	${RM} $@.d
	$(COMPILE.c) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/analog/Acq-IntClk.o src/analog/Acq-IntClk.c

${OBJECTDIR}/src/analog/ContGen-IntClk.o: src/analog/ContGen-IntClk.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/analog
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/analog/ContGen-IntClk.o src/analog/ContGen-IntClk.cpp

${OBJECTDIR}/src/edu/sju/ee/ni/daqmx/DAQmxTaskHandle.o: src/edu/sju/ee/ni/daqmx/DAQmxTaskHandle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/edu/sju/ee/ni/daqmx
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/edu/sju/ee/ni/daqmx/DAQmxTaskHandle.o src/edu/sju/ee/ni/daqmx/DAQmxTaskHandle.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libDataAcquisitionNative.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

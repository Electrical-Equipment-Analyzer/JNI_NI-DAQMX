/* 
 * File:   TaskHandle.h
 * Author: Leo
 *
 * Created on 2013年11月24日, 下午 8:55
 */

#ifndef TASKHANDLE_H
#define	TASKHANDLE_H

#include <NIDAQmx.h>
//#include "edu_sju_ee_ni_daqmx_TaskHandle.h"

class DAQmxTaskHandle {
public:
    DAQmxTaskHandle(const char taskName[]);
    //    DAQmxCreateAIVoltageChan(const char physicalChannel[], const char nameToAssignToChannel[], int32 terminalConfig, float64 minVal, float64 maxVal, int32 units, const char customScaleName[]);
    int test();
private:
    TaskHandle _taskHandle;
};

#endif	/* TASKHANDLE_H */


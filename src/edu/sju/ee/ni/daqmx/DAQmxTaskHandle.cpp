/* 
 * File:   TaskHandle.cpp
 * Author: Leo
 * 
 * Created on 2013年11月24日, 下午 8:55
 */

#include <stdio.h>
#include "DAQmxTaskHandle.h"

DAQmxTaskHandle::DAQmxTaskHandle(const char taskName[]) {
    _taskHandle = 0;
//    errorCheck(DAQmxCreateTask("", &_taskHandle));
    printf("%X\n", sizeof (_taskHandle));
    printf("create\n");
}

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

int DAQmxTaskHandle::test() {
    int32 error = 0;
    //	TaskHandle  taskHandle=0;
    int32 read;
    float64 data[1000];
    char errBuff[2048] = {'\0'};

    /*********************************************/
    // DAQmx Configure Code
    /*********************************************/
//    DAQmxErrChk(DAQmxCreateTask("", &_taskHandle));
    printf("%X\n", sizeof (_taskHandle));
    printf("%X\n", _taskHandle);
    DAQmxErrChk(DAQmxCreateAIVoltageChan(_taskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(_taskHandle, "", 10000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, 1000));

    /*********************************************/
    // DAQmx Start Code
    /*********************************************/
    DAQmxErrChk(DAQmxStartTask(_taskHandle));

    /*********************************************/
    // DAQmx Read Code
    /*********************************************/
    DAQmxErrChk(DAQmxReadAnalogF64(_taskHandle, 1000, 10.0, DAQmx_Val_GroupByChannel, data, 1000, &read, NULL));

    printf("Acquired %d points\n", read);
    fflush(stdout);

Error:
    if (DAQmxFailed(error))
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
    if (_taskHandle != 0) {
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        DAQmxStopTask(_taskHandle);
        DAQmxClearTask(_taskHandle);
    }
    if (DAQmxFailed(error))
        printf("DAQmx Error: %s\n", errBuff);
    printf("End of program, press Enter key to quit\n");
    fflush(stdout);
//    getchar();
    return 0;
}
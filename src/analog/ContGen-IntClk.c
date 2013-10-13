/*********************************************************************
 *
 * ANSI C Example program:
 *    ContGen-IntClk.c
 *
 * Example Category:
 *    AO
 *
 * Description:
 *    This example demonstrates how to output a continuous periodic
 *    waveform using an internal sample clock.
 *
 * Instructions for Running:
 *    1. Select the Physical Channel to correspond to where your
 *       signal is output on the DAQ device.
 *    2. Enter the Minimum and Maximum Voltage Ranges.
 *    3. Enter the desired rate for the generation. The onboard sample
 *       clock will operate at this rate.
 *    4. Select the desired waveform type.
 *    5. The rest of the parameters in the Waveform Information
 *       section will affect the way the waveform is created, before
 *       it's sent to the analog output of the board. Select the
 *       number of samples per cycle and the total number of cycles to
 *       be used as waveform data.
 *
 * Steps:
 *    1. Create a task.
 *    2. Create an Analog Output Voltage channel.
 *    3. Define the update Rate for the Voltage generation.
 *       Additionally, define the sample mode to be continuous.
 *    4. Write the waveform to the output buffer.
 *    5. Call the Start function.
 *    6. Wait until the user presses the Stop button.
 *    7. Call the Clear Task function to clear the Task.
 *    8. Display an error if any.
 *
 * I/O Connections Overview:
 *    Make sure your signal output terminal matches the Physical
 *    Channel I/O Control. For further connection information, refer
 *    to your hardware reference manual.
 *
 *********************************************************************/
#include <cstdlib>
#include <NIDAQmx.h>
#include <stdio.h>
#include <math.h>
#include "../../header/edu_sju_ee98_ni_daqmx_analog_ContGenIntClk.h"

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

#define PI	3.1415926535

int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData);

struct data {
    TaskHandle taskHandle = 0;
};


JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_analog_ContGenIntClk_construct
  (JNIEnv *env, jobject obj){
    struct data *ptr = (struct data *)malloc(sizeof(*ptr));
}


JNIEXPORT jint JNICALL Java_edu_sju_ee98_ni_daqmx_analog_ContGenIntClk_contGenIntClk
(JNIEnv *env, jobject obj, jstring physicalChannel, jdouble minVoltage, jdouble maxVoltage, jdouble rate, jlong length, jdoubleArray data) {

    int32 error = 0;
    taskHandle = 0;
    //	float64     data[1000];
    char errBuff[2048] = {'\0'};
    int i = 0;


    /*********************************************/
    // DAQmx Configure Code
    /*********************************************/
    DAQmxErrChk(DAQmxCreateTask("", &taskHandle));
    DAQmxErrChk(DAQmxCreateAOVoltageChan(taskHandle, (*env)->GetStringUTFChars(env, physicalChannel, 0), "", minVoltage, maxVoltage, DAQmx_Val_Volts, NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(taskHandle, "", rate, DAQmx_Val_Rising, DAQmx_Val_ContSamps, length));

    DAQmxErrChk(DAQmxRegisterDoneEvent(taskHandle, 0, DoneCallback, NULL));

    /*********************************************/
    // DAQmx Write Code
    /*********************************************/
    DAQmxErrChk(DAQmxWriteAnalogF64(taskHandle, length, 0, 10.0, DAQmx_Val_GroupByChannel, (*env)->GetDoubleArrayElements(env, data, JNI_FALSE), NULL, NULL));

    return 0;
Error:
    if (DAQmxFailed(error))
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
    if (taskHandle != 0) {
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }
    if (DAQmxFailed(error))
        printf("DAQmx Error: %s\n", errBuff);
    return 0;
}

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_analog_ContGenIntClk_start
(JNIEnv *env, jobject obj) {

    int32 error = 0;
    char errBuff[2048] = {'\0'};
    /*********************************************/
    // DAQmx Start Code
    /*********************************************/
    DAQmxErrChk(DAQmxStartTask(taskHandle));
    return;
Error:
    if (DAQmxFailed(error))
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
    if (taskHandle != 0) {
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }
    if (DAQmxFailed(error))
        printf("DAQmx Error: %s\n", errBuff);
    return;
}

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_analog_ContGenIntClk_stop
(JNIEnv *env, jobject obj) {

    int32 error = 0;
    char errBuff[2048] = {'\0'};
Error:
    if (DAQmxFailed(error))
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
    if (taskHandle != 0) {
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        DAQmxStopTask(taskHandle);
        DAQmxClearTask(taskHandle);
    }
    if (DAQmxFailed(error))
        printf("DAQmx Error: %s\n", errBuff);
    return;
}

int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData) {
    int32 error = 0;
    char errBuff[2048] = {'\0'};

    // Check to see if an error stopped the task.
    DAQmxErrChk(status);

Error:
    if (DAQmxFailed(error)) {
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        DAQmxClearTask(taskHandle);
        printf("DAQmx Error: %s\n", errBuff);
    }
    return 0;
}

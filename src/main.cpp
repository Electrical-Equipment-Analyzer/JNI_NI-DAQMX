/*********************************************************************
 *
 * ANSI C Example program:
 *    Acq-IntClk.c
 *
 * Example Category:
 *    AI
 *
 * Description:
 *    This example demonstrates how to acquire a finite amount of data
 *    using the DAQ device's internal clock.
 *
 * Instructions for Running:
 *    1. Select the physical channel to correspond to where your
 *       signal is input on the DAQ device.
 *    2. Enter the minimum and maximum voltages.
 *    Note: For better accuracy try to match the input range to the
 *          expected voltage level of the measured signal.
 *    3. Select the number of samples to acquire.
 *    4. Set the rate of the acquisition.
 *    Note: The rate should be AT LEAST twice as fast as the maximum
 *          frequency component of the signal being acquired.
 *
 * Steps:
 *    1. Create a task.
 *    2. Create an analog input voltage channel.
 *    3. Set the rate for the sample clock. Additionally, define the
 *       sample mode to be finite and set the number of samples to be
 *       acquired per channel.
 *    4. Call the Start function to start the acquisition.
 *    5. Read all of the waveform data.
 *    6. Call the Clear Task function to clear the task.
 *    7. Display an error if any.
 *
 * I/O Connections Overview:
 *    Make sure your signal input terminal matches the Physical
 *    Channel I/O Control. For further connection information, refer
 *    to your hardware reference manual.
 *
 *********************************************************************/

#include <windows.h>
#include <stdio.h>
//#include <NIDAQmx.h>
#include "edu/sju/ee/ni/daqmx/DAQmxTaskHandle.h"

#include "edu_sju_ee_ni_daqmx_TaskHandle.h"

JNIEXPORT jlong JNICALL Java_edu_sju_ee_ni_daqmx_TaskHandle_nTaskHandle(JNIEnv *env, jobject obj, jstring taskName) {
    DAQmxTaskHandle taskHandle("");
    DAQmxTaskHandle *ptrTaskHandle = &taskHandle;
    printf("%X\n", ptrTaskHandle);
    fflush(stdout);
//    ((DAQmxTaskHandle *) ptrTaskHandle)->test();
    return (jlong) ptrTaskHandle;
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_TaskHandle_nfinalize(JNIEnv *env, jobject obj, jlong nativeStruct) {
    printf("delete\n");
    free((DAQmxTaskHandle *) nativeStruct);
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_TaskHandle_test(JNIEnv *env, jobject obj, jlong nativeStruct) {
    ((DAQmxTaskHandle *) nativeStruct)->test();

}

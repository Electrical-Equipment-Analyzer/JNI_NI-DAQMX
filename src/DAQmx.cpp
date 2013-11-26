
#include <windows.h>
#include <stdio.h>
#include <NIDAQmx.h>
#include "edu_sju_ee_ni_daqmx_DAQmx.h"
#include "NativeUtils.h"

int32 CVICALLBACK TEveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
int32 CVICALLBACK TDoneCallback(TaskHandle taskHandle, int32 status, void *callbackData);

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_construct(JNIEnv *env, jobject obj) {
    struct daq *daq_struct = (struct daq *) malloc(sizeof (*daq_struct));
    (env)->SetLongField(obj, (env)->GetFieldID((env)->GetObjectClass(obj), "nativeStruct", "J"), (jlong) daq_struct);
    daq_struct->taskHandle = 0;
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_destruct(JNIEnv *env, jobject obj) {
    printf("native destruct\n");
    struct daq *daq_struct = getStruct(env, obj);
    daq_struct->taskHandle = 0;
    free(daq_struct);
}

JNIEXPORT jboolean JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_isAlive(JNIEnv *env, jobject obj) {
    return (getStruct(env, obj)->taskHandle != 0);
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_createTask(JNIEnv *env, jobject obj, jstring taskName) {
    errorCheck(env, obj, DAQmxCreateTask(toChars(env, taskName), &getStruct(env, obj)->taskHandle));
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_startTask(JNIEnv *env, jobject obj) {
    errorCheck(env, obj, DAQmxStartTask(getStruct(env, obj)->taskHandle));
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_stopTask(JNIEnv *env, jobject obj) {
    errorCheck(env, obj, DAQmxStopTask(getStruct(env, obj)->taskHandle));
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_clearTask(JNIEnv *env, jobject obj) {
    errorCheck(env, obj, DAQmxClearTask(getStruct(env, obj)->taskHandle));
}

JNIEXPORT jstring JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_getNthTaskDevice(JNIEnv *env, jobject obj, jint index) {
    char device[256];
    errorCheck(env, obj, DAQmxGetNthTaskDevice(getStruct(env, obj)->taskHandle, index, device, 256));
    return env->NewStringUTF(device);
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_registerEveryNSamplesEvent(JNIEnv *env, jobject obj, jint everyNsamplesEventType, jint nSamples, jint options) {
    errorCheck(env, obj, DAQmxRegisterEveryNSamplesEvent(getStruct(env, obj)->taskHandle, everyNsamplesEventType, nSamples, options, TEveryNCallback, NULL));
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_registerDoneEvent(JNIEnv *env, jobject obj, jint options) {
    errorCheck(env, obj, DAQmxRegisterDoneEvent(getStruct(env, obj)->taskHandle, options, TDoneCallback, NULL));
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_createAIVoltageChan
(JNIEnv *env, jobject obj, jstring physicalChannel, jstring nameToAssignToChannel, jint terminalConfig, jdouble minVal, jdouble maxVal, jint units, jstring customScaleName) {
    errorCheck(env, obj, DAQmxCreateAIVoltageChan(getStruct(env, obj)->taskHandle, toChars(env, physicalChannel), toChars(env, nameToAssignToChannel), terminalConfig, minVal, maxVal, units, toChars(env, customScaleName)));
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_createAOVoltageChan
(JNIEnv *env, jobject obj, jstring physicalChannel, jstring nameToAssignToChannel, jdouble minVal, jdouble maxVal, jint units, jstring customScaleName) {
    errorCheck(env, obj, DAQmxCreateAOVoltageChan(getStruct(env, obj)->taskHandle, toChars(env, physicalChannel), toChars(env, nameToAssignToChannel), minVal, maxVal, units, toChars(env, customScaleName)));
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_cfgDigEdgeStartTrig(JNIEnv *env, jobject obj, jstring triggerSource, jint triggerEdge) {
    errorCheck(env, obj, DAQmxCfgDigEdgeStartTrig(getStruct(env, obj)->taskHandle, toChars(env, triggerSource), triggerEdge));
}

JNIEXPORT jint JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_readAnalogF64
(JNIEnv *env, jobject obj, jint numSampsPerChan, jdouble timeout, jboolean fillMode, jdoubleArray readArray, jint arraySizeInSamps, jobject reserved) {
    int32 read;
    float64 data[arraySizeInSamps];
    errorCheck(env, obj, DAQmxReadAnalogF64(getStruct(env, obj)->taskHandle, numSampsPerChan, timeout, fillMode, data, arraySizeInSamps, &read, NULL));
    env->SetDoubleArrayRegion(readArray, 0, arraySizeInSamps, (const jdouble*) data);
    return read;
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_writeAnalogF64(JNIEnv *env, jobject obj, jint numSampsPerChan, jboolean autoStart, jdouble timeout, jboolean dataLayout, jdoubleArray writeArray) {
    errorCheck(env, obj, DAQmxWriteAnalogF64(getStruct(env, obj)->taskHandle, numSampsPerChan, autoStart, timeout, dataLayout, env->GetDoubleArrayElements(writeArray, JNI_FALSE), NULL, NULL));
}

JNIEXPORT jint JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_getDevProductCategory(JNIEnv *env, jobject obj, jstring device) {
    int32 productCategory;
    errorCheck(env, obj, DAQmxGetDevProductCategory(toChars(env, device), &productCategory));
    return productCategory;
}

JNIEXPORT jint JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_getTaskNumDevices(JNIEnv *env, jobject obj) {
    uInt32 numDevices;
    errorCheck(env, obj, DAQmxGetTaskNumDevices(getStruct(env, obj)->taskHandle, &numDevices));
    return numDevices;
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_cfgSampClkTiming
(JNIEnv *env, jobject obj, jstring source, jdouble rate, jint activeEdge, jint sampleMode, jlong sampsPerChan) {
    errorCheck(env, obj, DAQmxCfgSampClkTiming(getStruct(env, obj)->taskHandle, toChars(env, source), rate, activeEdge, sampleMode, sampsPerChan));
}

//******************************************************************************

#include <math.h>
#include <string.h>

static TaskHandle AItaskHandle = 0, AOtaskHandle = 0;

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_test(JNIEnv *env, jobject obj) {
    struct daq *daq_struct = getStruct(env, obj);

    int32 error = 0;
    char errBuff[2048] = {'\0'};
    char trigName[256];
    float64 AOdata[1000];
    float64 phase = 0.0;

    /*********************************************/
    // DAQmx Configure Code
    /*********************************************/

    DAQmxErrChk(DAQmxCreateTask("", &AItaskHandle));
    DAQmxErrChk(DAQmxCreateAIVoltageChan(AItaskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(AItaskHandle, "", 10000.0, DAQmx_Val_Rising, DAQmx_Val_ContSamps, 1000));

    //    DAQmxErrChk(GetTerminalNameWithDevPrefix(AItaskHandle, "ai/StartTrigger", trigName));

    DAQmxErrChk(DAQmxCreateTask("", &AOtaskHandle));
    DAQmxErrChk(DAQmxCreateAOVoltageChan(AOtaskHandle, "Dev1/ao0", "", -10.0, 10.0, DAQmx_Val_Volts, NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(AOtaskHandle, "", 5000.0, DAQmx_Val_Rising, DAQmx_Val_ContSamps, 1000));

    DAQmxErrChk(DAQmxCfgDigEdgeStartTrig(AOtaskHandle, trigName, DAQmx_Val_Rising));

    DAQmxErrChk(DAQmxRegisterEveryNSamplesEvent(AItaskHandle, DAQmx_Val_Acquired_Into_Buffer, 1000, 0, TEveryNCallback, NULL));
    DAQmxErrChk(DAQmxRegisterDoneEvent(AItaskHandle, 0, TDoneCallback, NULL));

    //    GenSineWave(1000, 2.0, 100.0 / 1000, &phase, AOdata);

    DAQmxErrChk(DAQmxWriteAnalogF64(AOtaskHandle, 1000, FALSE, 10.0, DAQmx_Val_GroupByChannel, AOdata, NULL, NULL));

    /*********************************************/
    // DAQmx Start Code
    /*********************************************/
    DAQmxErrChk(DAQmxStartTask(AOtaskHandle));
    DAQmxErrChk(DAQmxStartTask(AItaskHandle));

    printf("Acquiring samples continuously. Press Enter to interrupt\n");
    printf("\nRead:\tAI\tTotal:\tAI\n");
    getchar();

Error:
    if (DAQmxFailed(error))
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
    if (AItaskHandle) {
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        DAQmxStopTask(AItaskHandle);
        DAQmxClearTask(AItaskHandle);
        AItaskHandle = 0;
    }
    if (AOtaskHandle) {
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        DAQmxStopTask(AOtaskHandle);
        DAQmxClearTask(AOtaskHandle);
        AOtaskHandle = 0;
    }
    if (DAQmxFailed(error))
        printf("DAQmx Error: %s\n", errBuff);
    printf("End of program, press Enter key to quit\n");
    fflush(stdout);
    //	getchar();
    return;
}

int32 CVICALLBACK TEveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData) {
    int32 error = 0;
    char errBuff[2048] = {'\0'};
    static int totalAI = 0;
    int32 readAI;
    float64 AIdata[1000];

    /*********************************************/
    // DAQmx Read Code
    /*********************************************/
    DAQmxErrChk(DAQmxReadAnalogF64(taskHandle, 1000, 10.0, DAQmx_Val_GroupByChannel, AIdata, 1000, &readAI, NULL));

    printf("\t%d\t\t%d\t\t%f\t\t", readAI, totalAI += readAI, AIdata[0]);
    int i;
    for (i = 0; i < 1000; i++) {
        printf("%f\t", AIdata[i]);
    }
    printf("\n");
    fflush(stdout);

Error:
    if (DAQmxFailed(error)) {
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        /*********************************************/
        // DAQmx Stop Code
        /*********************************************/
        if (taskHandle) {
            DAQmxStopTask(taskHandle);
            DAQmxClearTask(taskHandle);
            taskHandle = 0;
        }
        printf("DAQmx Error: %s\n", errBuff);
        fflush(stdout);
    }
    return 0;
}

int32 CVICALLBACK TDoneCallback(TaskHandle taskHandle, int32 status, void *callbackData) {
    int32 error = 0;
    char errBuff[2048] = {'\0'};

    // Check to see if an error stopped the task.
    DAQmxErrChk(status);

Error:
    if (DAQmxFailed(error)) {
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        if (taskHandle) {
            DAQmxStopTask(taskHandle);
            DAQmxClearTask(taskHandle);
            taskHandle = 0;
        }
        DAQmxClearTask(taskHandle);
        printf("DAQmx Error: %s\n", errBuff);
        fflush(stdout);
    }
    return 0;
}




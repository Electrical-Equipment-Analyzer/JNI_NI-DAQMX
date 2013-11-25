
#include <windows.h>
#include <stdio.h>
#include <NIDAQmx.h>
#include "edu_sju_ee98_ni_daqmx_DAQmx.h"
#include "NativeUtils.h"

struct daq {
    TaskHandle taskHandle;
};

struct daq * getStruct(JNIEnv *env, jobject obj) {
    return (struct daq *) ((env)->GetLongField(obj, (env)->GetFieldID((env)->GetObjectClass(obj), "nativeStruct", "J")));
}

void errorCheck(JNIEnv *env, jobject obj, int32 error) {
    if (DAQmxFailed(error)) {
        char errBuff[2048] = {'\0'};
        DAQmxGetExtendedErrorInfo(errBuff, 2048);
        (env)->ThrowNew((env)->FindClass("java/lang/Exception"), errBuff);
        printf("DAQmx Error: %s\n", errBuff);
    }
}

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_nDAQmx(JNIEnv *env, jobject obj, jstring st) {
    struct daq *ptr = (struct daq *) malloc(sizeof (*ptr));
    (env)->SetLongField(obj, (env)->GetFieldID((env)->GetObjectClass(obj), "nativeStruct", "J"), (jlong) ptr);

    ptr->taskHandle = 0;
    errorCheck(env, obj, DAQmxCreateTask("", &ptr->taskHandle));
}

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_nfinalize(JNIEnv *env, jobject obj) {
    printf("end of process\n");
    struct daq *daq_struct = getStruct(env, obj);
    free(daq_struct);
}

JNIEXPORT jboolean JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_isAlive(JNIEnv *env, jobject obj) {
    return (getStruct(env, obj)->taskHandle != 0);
}

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_createAIVoltageChan
(JNIEnv *env, jobject obj, jstring physicalChannel, jstring nameToAssignToChannel, jint terminalConfig, jdouble minVal, jdouble maxVal, jint units, jstring customScaleName) {
    errorCheck(env, obj, DAQmxCreateAIVoltageChan(getStruct(env, obj)->taskHandle, toChars(env, physicalChannel), toChars(env, nameToAssignToChannel), terminalConfig, minVal, maxVal, units, toChars(env, customScaleName)));
}

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_cfgSampClkTiming
(JNIEnv *env, jobject obj, jstring source, jdouble rate, jint activeEdge, jint sampleMode, jlong sampsPerChan) {
    errorCheck(env, obj, DAQmxCfgSampClkTiming(getStruct(env, obj)->taskHandle, toChars(env, source), rate, activeEdge, sampleMode, sampsPerChan));
}

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_startTask(JNIEnv *env, jobject obj) {
    errorCheck(env, obj, DAQmxStartTask(getStruct(env, obj)->taskHandle));
}

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_stopTask(JNIEnv *env, jobject obj) {
    errorCheck(env, obj, DAQmxStopTask(getStruct(env, obj)->taskHandle));
}

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_clearTask(JNIEnv *env, jobject obj) {
    errorCheck(env, obj, DAQmxClearTask(getStruct(env, obj)->taskHandle));
}

JNIEXPORT jint JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_readAnalogF64
(JNIEnv *env, jobject obj, jint numSampsPerChan, jdouble timeout, jboolean fillMode, jdoubleArray readArray, jint arraySizeInSamps, jobject reserved) {
    int32 read;
    float64 data[arraySizeInSamps];
    errorCheck(env, obj, DAQmxReadAnalogF64(getStruct(env, obj)->taskHandle, numSampsPerChan, timeout, fillMode, data, arraySizeInSamps, &read, NULL));
    env->SetDoubleArrayRegion(readArray, 0, arraySizeInSamps, (const jdouble*) data);
    return read;
}

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_test(JNIEnv *env, jobject obj) {
    struct daq *daq_struct = getStruct(env, obj);


    int32 error = 0;
    //	TaskHandle  taskHandle=0;
    int32 read;
    float64 data[1000];
    char errBuff[2048] = {'\0'};

    /*********************************************/
    // DAQmx Configure Code
    /*********************************************/
    //    DAQmxErrChk(DAQmxCreateTask("", &ptr->taskHandle));
    //    DAQmxErrChk(DAQmxCreateAIVoltageChan(daq_struct->taskHandle, "Dev1/ai1", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL));
    //    DAQmxErrChk(DAQmxCfgSampClkTiming(daq_struct->taskHandle, "", 10000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, 1000));

    /*********************************************/
    // DAQmx Start Code
    /*********************************************/
    //    DAQmxErrChk(DAQmxStartTask(daq_struct->taskHandle));

    /*********************************************/
    // DAQmx Read Code
    /*********************************************/
    //    DAQmxErrChk(DAQmxReadAnalogF64(daq_struct->taskHandle, 1000, 10.0, DAQmx_Val_GroupByChannel, data, 1000, &read, NULL));

    printf("Acquired %d points\n", read);
    //    int i;
    //    for (i = 0; i < 1000; i++) {
    //        printf("%f\t", data[i]);
    //    }
    //    printf("\n");
    fflush(stdout);

Error:
    if (DAQmxFailed(error))
        DAQmxGetExtendedErrorInfo(errBuff, 2048);

    if (DAQmxFailed(error))
        printf("DAQmx Error: %s\n", errBuff);
    printf("End of program, press Enter key to quit\n");
    fflush(stdout);
    //    getchar();
    return;
}


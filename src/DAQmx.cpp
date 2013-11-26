
#include <windows.h>
#include <stdio.h>
#include <NIDAQmx.h>
#include "edu_sju_ee_ni_daqmx_DAQmx.h"
#include "NativeUtils.h"

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

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_createAIVoltageChan
(JNIEnv *env, jobject obj, jstring physicalChannel, jstring nameToAssignToChannel, jint terminalConfig, jdouble minVal, jdouble maxVal, jint units, jstring customScaleName) {
    errorCheck(env, obj, DAQmxCreateAIVoltageChan(getStruct(env, obj)->taskHandle, toChars(env, physicalChannel), toChars(env, nameToAssignToChannel), terminalConfig, minVal, maxVal, units, toChars(env, customScaleName)));
}

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_cfgSampClkTiming
(JNIEnv *env, jobject obj, jstring source, jdouble rate, jint activeEdge, jint sampleMode, jlong sampsPerChan) {
    errorCheck(env, obj, DAQmxCfgSampClkTiming(getStruct(env, obj)->taskHandle, toChars(env, source), rate, activeEdge, sampleMode, sampsPerChan));
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

JNIEXPORT jint JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_readAnalogF64
(JNIEnv *env, jobject obj, jint numSampsPerChan, jdouble timeout, jboolean fillMode, jdoubleArray readArray, jint arraySizeInSamps, jobject reserved) {
    int32 read;
    float64 data[arraySizeInSamps];
    errorCheck(env, obj, DAQmxReadAnalogF64(getStruct(env, obj)->taskHandle, numSampsPerChan, timeout, fillMode, data, arraySizeInSamps, &read, NULL));
    env->SetDoubleArrayRegion(readArray, 0, arraySizeInSamps, (const jdouble*) data);
    return read;
}

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

JNIEXPORT void JNICALL Java_edu_sju_ee_ni_daqmx_DAQmx_test(JNIEnv *env, jobject obj) {
    struct daq *daq_struct = getStruct(env, obj);

    fflush(stdout);
    return;
}



#include <jni.h>
#include <stdio.h>
#include <NIDAQmx.h>
#include "../header/edu_sju_ee98_ni_daqmx_DAQmx.h"

JNIEXPORT void JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_print(JNIEnv *env, jobject obj) {
    printf("Hello \n");
    // Get a class reference for this object
    jclass thisClass = (*env)->GetObjectClass(env, obj);

    // Get the Method ID for method "callback", which takes no arg and return void
    jmethodID midCallBack = (*env)->GetMethodID(env, thisClass, "callback", "()V");
    if (NULL == midCallBack) return;
    printf("In C, call back Java's callback()\n");
    // Call back the method (which returns void), baed on the Method ID
    (*env)->CallVoidMethod(env, obj, midCallBack);
    return;
}

JNIEXPORT jdoubleArray JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_acqIntClk(JNIEnv *env, jobject obj) {
    int i;
    int length = 1000;
    float64 data[length];
    acqIntClk(data);
    jdoubleArray doubleArray = (*env)->NewDoubleArray(env, length);
    (*env)->SetDoubleArrayRegion(env, doubleArray, 0, length, (const jdouble*) data);
    return doubleArray;
}

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

int acqIntClk(float64 *data) {
    int32 error = 0;
    TaskHandle taskHandle = 0;
    int32 read;
    //    float64 data[1000];
    char errBuff[2048] = {'\0'};

    /*********************************************/
    // DAQmx Configure Code
    /*********************************************/
    DAQmxErrChk(DAQmxCreateTask("", &taskHandle));
    DAQmxErrChk(DAQmxCreateAIVoltageChan(taskHandle, "Dev1/ai0", "", DAQmx_Val_Cfg_Default, -10.0, 10.0, DAQmx_Val_Volts, NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(taskHandle, "", 10000.0, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, 1000));

    /*********************************************/
    // DAQmx Start Code
    /*********************************************/
    DAQmxErrChk(DAQmxStartTask(taskHandle));

    /*********************************************/
    // DAQmx Read Code
    /*********************************************/
    DAQmxErrChk(DAQmxReadAnalogF64(taskHandle, 1000, 10.0, DAQmx_Val_GroupByChannel, data, 1000, &read, NULL));

    printf("Acquired %d points\n", read);

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
    //    printf("End of program, press Enter key to quit\n");
    //    getchar();
    return 0;
}


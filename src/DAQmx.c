
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

//JNIEXPORT jdoubleArray JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_acqIntClk(JNIEnv *env, jobject obj) {
//    int i;
//    int length = 1000;
//    float64 data[length];
//    acqIntClk(data, -10.0, 10.0, 10000.0, 1000);
//    jdoubleArray doubleArray = (*env)->NewDoubleArray(env, length);
//    (*env)->SetDoubleArrayRegion(env, doubleArray, 0, length, (const jdouble*) data);
//    return doubleArray;
//}

JNIEXPORT jdoubleArray JNICALL Java_edu_sju_ee98_ni_daqmx_DAQmx_acqIntClk
(JNIEnv *env, jobject obj, jstring jPhysicalChannel, jdouble minVoltage, jdouble maxVoltage, jdouble rate, jlong length) {
    const char *physicalChannel = (*env)->GetStringUTFChars(env, jPhysicalChannel, 0);
    printf("Physical Channel : %s\n", physicalChannel);
    printf("length %d points\n", length);
    float64 data[length];
    acqIntClk(data, physicalChannel, minVoltage, maxVoltage, rate, length);
    jdoubleArray doubleArray = (*env)->NewDoubleArray(env, length);
    (*env)->SetDoubleArrayRegion(env, doubleArray, 0, length, (const jdouble*) data);
    return doubleArray;
}


#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

int acqIntClk(float64 *data, const char physicalChannel[], float64 minVal, float64 maxVal, float64 rate, uInt64 sampsPerChanToAcquire) {
    int32 error = 0;
    TaskHandle taskHandle = 0;
    int32 read;
    //    float64 data[1000];
    char errBuff[2048] = {'\0'};

    /*********************************************/
    // DAQmx Configure Code
    /*********************************************/
    DAQmxErrChk(DAQmxCreateTask("", &taskHandle));
    DAQmxErrChk(DAQmxCreateAIVoltageChan(taskHandle, physicalChannel, "", DAQmx_Val_Cfg_Default, minVal, maxVal, DAQmx_Val_Volts, NULL));
    DAQmxErrChk(DAQmxCfgSampClkTiming(taskHandle, "", rate, DAQmx_Val_Rising, DAQmx_Val_FiniteSamps, sampsPerChanToAcquire));

    /*********************************************/
    // DAQmx Start Code
    /*********************************************/
    DAQmxErrChk(DAQmxStartTask(taskHandle));

    /*********************************************/
    // DAQmx Read Code
    /*********************************************/
    DAQmxErrChk(DAQmxReadAnalogF64(taskHandle, sampsPerChanToAcquire, 10.0, DAQmx_Val_GroupByChannel, data, sampsPerChanToAcquire, &read, NULL));

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


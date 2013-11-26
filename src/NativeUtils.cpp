

#include <windows.h>
#include <jni.h>
#include <NIDAQmx.h>
#include "NativeUtils.h"

const char * toChars(JNIEnv *env, jstring string) {
    return (string == NULL ? NULL : env->GetStringUTFChars(string, NULL));
}

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
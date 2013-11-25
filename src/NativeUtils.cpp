

#include <windows.h>
#include <jni.h>
#include "NativeUtils.h"

const char * toChars(JNIEnv *env, jstring string) {
    return (string == NULL ? NULL : env->GetStringUTFChars(string, NULL));
}

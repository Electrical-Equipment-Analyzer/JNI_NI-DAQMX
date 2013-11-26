/* 
 * File:   NativeUtils.h
 * Author: Leo
 *
 * Created on 2013年11月25日, 下午 11:31
 */

#ifndef NATIVEUTILS_H
#define	NATIVEUTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

    struct daq {
        TaskHandle taskHandle;
    };

    const char * toChars(JNIEnv *, jstring);
    struct daq * getStruct(JNIEnv *, jobject);
    void errorCheck(JNIEnv *, jobject, int32);

#ifdef	__cplusplus
}
#endif

#endif	/* NATIVEUTILS_H */


#pragma once
#include "str_tools.h"
#include <string>
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class indi_whc_webandcv_Java2Cpp */

#ifndef _Included_indi_whc_webandcv_Java2Cpp
#define _Included_indi_whc_webandcv_Java2Cpp
#ifdef __cplusplus
extern "C" {
#endif
	/*
	* Class:     indi_whc_webandcv_Java2Cpp
	* Method:    SystemInit
	* Signature: ()I
	*/
	JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SystemInit
		(JNIEnv *, jclass);

	/*
	* Class:     indi_whc_webandcv_Java2Cpp
	* Method:    SetDeviceSerialNum
	* Signature: (Ljava/lang/String;)I
	*/
	JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SetDeviceSerialNum
		(JNIEnv *, jclass, jstring);

	/*
	* Class:     indi_whc_webandcv_Java2Cpp
	* Method:    SetRelayNum
	* Signature: (I)I
	*/
	JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SetRelayNum
		(JNIEnv *, jclass, jint);

	/*
	* Class:     indi_whc_webandcv_Java2Cpp
	* Method:    OpenRelay
	* Signature: (II)I
	*/
	JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_OpenRelay
		(JNIEnv *, jclass, jint, jint);

	/*
	* Class:     indi_whc_webandcv_Java2Cpp
	* Method:    CloseRelay
	* Signature: (II)I
	*/
	JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_CloseRelay
		(JNIEnv *, jclass, jint, jint);

	/*
	* Class:     indi_whc_webandcv_Java2Cpp
	* Method:    FindDevice
	* Signature: ()I
	*/
	JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_FindDevice
		(JNIEnv *, jclass);

	/*
	* Class:     indi_whc_webandcv_Java2Cpp
	* Method:    SelectDevice
	* Signature: (I)I
	*/
	JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SelectDevice
		(JNIEnv *, jclass, jint);
	/*
	* Class:     indi_whc_webandcv_Java2Cpp
	* Method:    CloseDevice
	* Signature: (I)I
	*/
	JNIEXPORT void JNICALL Java_indi_whc_webandcv_Java2Cpp_CloseDevice
		(JNIEnv *, jclass, jint);

#ifdef __cplusplus
}
#endif
#endif

// JNITest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "indi_whc_webandcv_Java2Cpp.h"
#include <iostream>
using namespace std;

int main()
{
	return 0;
}

JNIEXPORT void JNICALL Java_indi_whc_webandcv_Java2Cpp_GetDeviceSerialNum
(JNIEnv *, jclass)
{
	cout << "1111" << endl;
}
JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_GetRelayNum
(JNIEnv *, jclass)
{
	return 1;
}
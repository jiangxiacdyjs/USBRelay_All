// USBRelay.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "usb_relay_device.h"
#include "str_tools.h"
#include <string>
#include <iostream>
#include "USBRelayDll.h"

using namespace std;

struct usb_relay_device_info *DeviceList;
std::map<std::wstring, struct usb_relay_device_info*> m_mapIndexToDevice;

std::map<int, std::wstring> mapNumToSeria;
int state = 0;//0--主界面 1--输入设备序列号 2--输入继电器序号
string inputbuffer;//输入寄存

int result;
int hd;
string Open_Close;//打开，关闭状态


JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SystemInit
(JNIEnv *, jclass)
{
	return usb_relay_init();
	cout << "SystemInit" << endl;

}
JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SetDeviceSerialNum
(JNIEnv *env, jclass, jstring SerialNum)
{
	cout << "|               请输入设备序列号                 |" << endl;
	//getline(cin, inputbuffer);
	//strcpy_s(serial_number, inputbuffer.c_str());
	const char *serial_number = env ->GetStringUTFChars(SerialNum,NULL);	 	
	hd = usb_relay_device_open_with_serial_number(serial_number, strlen(serial_number));
	cout << serial_number << endl;
	return hd;
}

JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SetRelayNum
(JNIEnv *, jclass, jint relay)
{
	cout << "|           请输入需要操作的继电器序号           |" << endl;
	//getline(cin, inputbuffer);
	//int relay_index;
	//relay_index = atoi(inputbuffer.c_str());
	return relay;
}
JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_OpenRelay
(JNIEnv *, jclass, jint hd, jint relay_index)
{
	if ((relay_index > 0) && (relay_index < 255))
	{
		result = usb_relay_device_open_one_relay_channel(hd, relay_index);
		if (result == 0)
			cout << "|        已打开" << relay_index << "号继电器           |" << endl;
		else
			cout << "|                   操作失败                      |" << endl;
	}
	else if (relay_index == 255)
	{
		result = usb_relay_device_open_all_relay_channel(hd);
		if (result == 0)
			cout << "|               已打开全部继电器                 |" << endl;
		else
			cout << "|                   操作失败                    |" << endl;
	}
	else
	{
		cout << "|       继电器序号必须是0-255之间的整数          |" << endl;
		cout << "|                   请重新输入..                 |" << endl;
		result = 1;
	}
	return result;
}

JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_CloseRelay
(JNIEnv *, jclass, jint hd, jint relay_index)
{
	if ((relay_index > 0) && (relay_index < 255))
	{
		result = usb_relay_device_close_one_relay_channel(hd, relay_index);
		if (result == 0)
			cout << "|        已关闭" << relay_index << "号继电器           |" << endl;
		else
			cout << "|                   操作失败                      |" << endl;
	}
	else if (relay_index == 255)
	{
		result = usb_relay_device_close_all_relay_channel(hd);
		if (result == 0)
			cout << "|               已关闭全部继电器                 |" << endl;
		else
			cout << "|                   操作失败                    |" << endl;
	}
	else
	{
		cout << "|       继电器序号必须是0-255之间的整数          |" << endl;
		cout << "|                   请重新输入..                 |" << endl;
		result = 1;
	}
	return result;
}

JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_FindDevice
(JNIEnv *, jclass)
{
	int cur_device_num = 0;
	
	if (DeviceList)
	{
		usb_relay_device_free_enumerate(DeviceList);
		DeviceList = NULL;
	}
	DeviceList = usb_relay_device_enumerate();
	if (DeviceList)
	{
		struct usb_relay_device_info *cur_device = DeviceList;
		while (cur_device)
		{
			cur_device_num++;
			m_mapIndexToDevice[Ansi2WChar((char*)(cur_device->serial_number))] = cur_device;
			mapNumToSeria[cur_device_num] = Ansi2WChar((char*)(cur_device->serial_number));
			wcout << "已找到设备" << cur_device_num << "   设备号：" << mapNumToSeria[cur_device_num] << endl;
			cur_device = cur_device->next;
		}
		return cur_device_num;
	}
	else
	{
		cout << "|                    未找到设备                     |" << endl;
		return 0;
	}
}

JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SelectDevice
(JNIEnv *, jclass, jint device)
{
	cout << "|                      请选择设备：                       |" << endl;
	//getline(cin, inputbuffer);
	//int device_index = atoi(inputbuffer.c_str());
	wstring SerialNum = mapNumToSeria[device];
	wcout << SerialNum << endl;
	hd = usb_relay_device_open(m_mapIndexToDevice[mapNumToSeria[device]]);
	return hd;
}

JNIEXPORT void JNICALL Java_indi_whc_webandcv_Java2Cpp_CloseDevice
(JNIEnv *, jclass, jint device_h)
{
	 usb_relay_device_close(device_h);
}
// USBRelay.cpp : �������̨Ӧ�ó������ڵ㡣
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
int state = 0;//0--������ 1--�����豸���к� 2--����̵������
string inputbuffer;//����Ĵ�

int result;
int hd;
string Open_Close;//�򿪣��ر�״̬


JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SystemInit
(JNIEnv *, jclass)
{
	return usb_relay_init();
	cout << "SystemInit" << endl;

}
JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SetDeviceSerialNum
(JNIEnv *env, jclass, jstring SerialNum)
{
	cout << "|               �������豸���к�                 |" << endl;
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
	cout << "|           ��������Ҫ�����ļ̵������           |" << endl;
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
			cout << "|        �Ѵ�" << relay_index << "�ż̵���           |" << endl;
		else
			cout << "|                   ����ʧ��                      |" << endl;
	}
	else if (relay_index == 255)
	{
		result = usb_relay_device_open_all_relay_channel(hd);
		if (result == 0)
			cout << "|               �Ѵ�ȫ���̵���                 |" << endl;
		else
			cout << "|                   ����ʧ��                    |" << endl;
	}
	else
	{
		cout << "|       �̵�����ű�����0-255֮�������          |" << endl;
		cout << "|                   ����������..                 |" << endl;
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
			cout << "|        �ѹر�" << relay_index << "�ż̵���           |" << endl;
		else
			cout << "|                   ����ʧ��                      |" << endl;
	}
	else if (relay_index == 255)
	{
		result = usb_relay_device_close_all_relay_channel(hd);
		if (result == 0)
			cout << "|               �ѹر�ȫ���̵���                 |" << endl;
		else
			cout << "|                   ����ʧ��                    |" << endl;
	}
	else
	{
		cout << "|       �̵�����ű�����0-255֮�������          |" << endl;
		cout << "|                   ����������..                 |" << endl;
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
			wcout << "���ҵ��豸" << cur_device_num << "   �豸�ţ�" << mapNumToSeria[cur_device_num] << endl;
			cur_device = cur_device->next;
		}
		return cur_device_num;
	}
	else
	{
		cout << "|                    δ�ҵ��豸                     |" << endl;
		return 0;
	}
}

JNIEXPORT jint JNICALL Java_indi_whc_webandcv_Java2Cpp_SelectDevice
(JNIEnv *, jclass, jint device)
{
	cout << "|                      ��ѡ���豸��                       |" << endl;
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
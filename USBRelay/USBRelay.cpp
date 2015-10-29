// USBRelay.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "usb_relay_device.h"
#include "str_tools.h"
#include <string>
#include <iostream>
#include "USBRelay.h"

using namespace std;

struct usb_relay_device_info *DeviceList;
std::map<std::wstring, struct usb_relay_device_info*> m_mapIndexToDevice;

std::map<int, std::wstring> mapNumToSeria;
int state=0;//0--������ 1--�����豸���к� 2--����̵������
string inputbuffer;//����Ĵ���

int result;
int hd;
string Open_Close;//�򿪣��ر�״̬

int _tmain()
{
	usb_relay_init();
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
		
			cout << "|                      ��ѡ���豸��                       |" << endl;
			getline(cin, inputbuffer);
			int device_index = atoi(inputbuffer.c_str());
			wstring SerialNum = mapNumToSeria[device_index];
			wcout << SerialNum << endl;
			hd = usb_relay_device_open(m_mapIndexToDevice[mapNumToSeria[device_index]]);
		}
		else
		{
			cout << "|                    δ�ҵ��豸                     |" << endl;
		}
	return 0;
}
void GetDeviceSerialNum()
{
	cout<<"|               �������豸���к�                 |"<<endl;
	getline(cin,inputbuffer);
	char serial_number[10];
	strcpy_s(serial_number,inputbuffer.c_str());
	hd = usb_relay_device_open_with_serial_number(serial_number, strlen(serial_number));
	state=2;
}

int GetRelayNum()
{
	cout<<"|           ��������Ҫ�����ļ̵������           |"<<endl;
	getline(cin,inputbuffer);
	int relay_index;
	relay_index = atoi(inputbuffer.c_str());
	return relay_index;
}
void OpenRelay(int relay_index)
{
	if ((relay_index > 0) && (relay_index < 255) )
	{
		result = usb_relay_device_open_one_relay_channel(hd, relay_index);
		if(result==0)
			cout<<"|        �Ѵ�"<<relay_index<<"�ż̵���           |"<<endl;
		else
		cout<<"|                   ����ʧ��                      |"<<endl;
		state=0;
	}
	else if (relay_index == 255)
	{
		result = usb_relay_device_open_all_relay_channel(hd);
		if(result==0)
			cout<<"|               �Ѵ�ȫ���̵���                 |"<<endl;
		else
		cout<<"|                   ����ʧ��                    |"<<endl;
		state=0;
	}
	else
	{
		cout<<"|       �̵�����ű�����0-255֮�������          |"<<endl;
		cout<<"|                   ����������..                 |"<<endl;
		result =  1;
		state=2;
	}
}

void CloseRelay(int relay_index)
{
	if ((relay_index > 0) && (relay_index < 255) )
	{
		result = usb_relay_device_close_one_relay_channel(hd, relay_index);
		if(result==0)
			cout<<"|        �ѹر�"<<relay_index<<"�ż̵���           |"<<endl;
		else
		cout<<"|                   ����ʧ��                      |"<<endl;
		state=0;
	}
	else if (relay_index == 255)
	{
		result = usb_relay_device_close_all_relay_channel(hd);
		if(result==0)
			cout<<"|               �ѹر�ȫ���̵���                 |"<<endl;
		else
		cout<<"|                   ����ʧ��                    |"<<endl;
		state=0;
	}
	else
	{
		cout<<"|       �̵�����ű�����0-255֮�������          |"<<endl;
		cout<<"|                   ����������..                 |"<<endl;
		result =  1;
		state=2;
	}
}
wstring FindDevice()
{
	int cur_device_num=0;
	if (DeviceList)
	{
		usb_relay_device_free_enumerate(DeviceList);
		DeviceList = NULL;
	}
	DeviceList = usb_relay_device_enumerate();
	if (DeviceList)
	{
		struct usb_relay_device_info *cur_device = DeviceList;
		cout<<"|                    ���ҵ������豸                      |"<<endl;
		while (cur_device)
		{
			cur_device_num++;
			m_mapIndexToDevice[Ansi2WChar((char*)(cur_device->serial_number))] = cur_device;
			mapNumToSeria[cur_device_num]= Ansi2WChar((char*)(cur_device->serial_number));
			cur_device = cur_device->next;
			cout<<"�豸"<<cur_device_num<<"���к� ��"<<cur_device->serial_number<<endl;	
		}
		cout<<"|                      ��ѡ���豸��                       |"<<endl;
		getline(cin,inputbuffer);
		int device_index = atoi(inputbuffer.c_str());
		return mapNumToSeria[device_index];
	}
	else
	{
		cout<<"|                    δ�ҵ��豸                     |"<<endl;
		state=0;
		return L"FFFFFF";
	}
	
}
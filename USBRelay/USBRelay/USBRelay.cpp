// USBRelay.cpp : 定义控制台应用程序的入口点。
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
int state=0;//0--主界面 1--输入设备序列号 2--输入继电器序号
string inputbuffer;//输入寄存器

int result;
int hd;
string Open_Close;//打开，关闭状态

int _tmain()
{
	usb_relay_init();
	while(true)
	{
		if(state==0)
		{
			cout<<"|*************************************************|"<<endl;
			cout<<"|                    USBRelay                     |"<<endl;
			cout<<"|                  Version 1.0                    |"<<endl;
			cout<<"|    操作方法： 输入 1   查找设备                 |"<<endl;
			cout<<"|               输入 2   打开设备                 |"<<endl;
			cout<<"|               输入 3   关闭设备                 |"<<endl;
			cout<<"|               输入 4   退出                     |"<<endl;
			cout<<"|                  回车键完成                     |"<<endl;
			cout<<"|*************************************************|"<<endl;
			getline(cin,inputbuffer);
			Open_Close = inputbuffer;
			state=1;
		}
		if(Open_Close=="1")
		{
			wstring SerialNum = FindDevice();
			string b(SerialNum.begin(),SerialNum.end());
			char serial_number[10];
			strcpy_s(serial_number,b.c_str());
			hd = usb_relay_device_open_with_serial_number(serial_number, strlen(serial_number));
		}
		else if(Open_Close=="2"||Open_Close=="3")
		{
			if(state==1)
			{
				GetDeviceSerialNum();
			}
			if(state==2)
			{
				int relay_index=GetRelayNum();
				if(Open_Close=="2")
				{
					OpenRelay(relay_index);
				}
				else
				{
					CloseRelay(relay_index);
				}
			}
		}
		else if(Open_Close=="4")
		{
			break;
		}
		else
		{
			if(state==0)
			{
				cout<<"|           请输入1-4之间的整数来完成对应的功能              |"<<endl;
				state=0;
			}
		}
	}
	return 0;
}
void GetDeviceSerialNum()
{
	cout<<"|               请输入设备序列号                 |"<<endl;
	getline(cin,inputbuffer);
	char serial_number[10];
	strcpy_s(serial_number,inputbuffer.c_str());
	hd = usb_relay_device_open_with_serial_number(serial_number, strlen(serial_number));
	state=2;
}

int GetRelayNum()
{
	cout<<"|           请输入需要操作的继电器序号           |"<<endl;
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
			cout<<"|        已打开"<<relay_index<<"号继电器           |"<<endl;
		else
		{cout<<"|                   操作失败                      |"<<endl;
		state=0;}
	}
	else if (relay_index == 255)
	{
		result = usb_relay_device_open_all_relay_channel(hd);
		if(result==0)
			cout<<"|               已打开全部继电器                 |"<<endl;
		else
		{cout<<"|                   操作失败                    |"<<endl;
		state=0;}
	}
	else
	{
		cout<<"|       继电器序号必须是0-255之间的整数          |"<<endl;
		cout<<"|                   请重新输入..                 |"<<endl;
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
			cout<<"|        已关闭"<<relay_index<<"号继电器           |"<<endl;
		else
		{cout<<"|                   操作失败                      |"<<endl;
		state=0;}
	}
	else if (relay_index == 255)
	{
		result = usb_relay_device_close_all_relay_channel(hd);
		if(result==0)
			cout<<"|               已关闭全部继电器                 |"<<endl;
		else
		{cout<<"|                   操作失败                    |"<<endl;
		state=0;}
	}
	else
	{
		cout<<"|       继电器序号必须是0-255之间的整数          |"<<endl;
		cout<<"|                   请重新输入..                 |"<<endl;
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
		cout<<"|                    已找到以下设备                      |"<<endl;
		while (cur_device)
		{
			cur_device_num++;
			m_mapIndexToDevice[Ansi2WChar((char*)(cur_device->serial_number))] = cur_device;
			mapNumToSeria[cur_device_num]= Ansi2WChar((char*)(cur_device->serial_number));
			cur_device = cur_device->next;
			cout<<"设备"<<cur_device_num<<"序列号 ："<<cur_device->serial_number<<endl;	
		}
		cout<<"|                      请选择设备：                       |"<<endl;
		getline(cin,inputbuffer);
		int device_index = atoi(inputbuffer.c_str());
		return mapNumToSeria[device_index];
	}
	else
	{
		cout<<"|                    未找到设备                     |"<<endl;
		state=0;
		return L"FFFFFF";
	}
	
}
#pragma once
#include "str_tools.h"
#include <string>
using namespace std;
//struct usb_relay_device_info;
//struct usb_relay_device_info *m_pDeviceList;

void GetDeviceSerialNum();
int GetRelayNum();
void OpenRelay(int relay_index);
void CloseRelay(int relay_index);
wstring FindDevice();
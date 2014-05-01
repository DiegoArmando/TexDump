#include "hot_key_listener.h"
#include "message.h"
#include "manager.h"
#include <qclipboard.h>
#include <string>
#include <qapplication.h>
#include <thread>
#include <chrono>


void hot_key_listener::run() {
	RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_SHIFT, 0x43);
	MSG msg = { 0 };
	start_ = true;
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		if (start_ == false)
			break;

		if (msg.message != WM_HOTKEY)
			continue;

		int key_count = 5;

		INPUT* input = new INPUT[key_count];
		
		for (int i = 0; i < key_count; i++)
		{
			input[i].type = INPUT_KEYBOARD;
		}
		input[0].ki.wVk = VK_SHIFT;
		input[0].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		input[0].ki.wScan = MapVirtualKey(VK_SHIFT, MAPVK_VK_TO_VSC);
		input[1].ki.wVk = VK_CONTROL;
		input[1].ki.dwFlags = KEYEVENTF_SCANCODE;
		input[1].ki.wScan = MapVirtualKey(VK_CONTROL, MAPVK_VK_TO_VSC);
		input[2].ki.wVk = 0x43;
		input[2].ki.dwFlags = KEYEVENTF_SCANCODE;
		input[2].ki.wScan = MapVirtualKey(0x43, MAPVK_VK_TO_VSC);
		input[3].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
		input[3].ki.wVk = input[0].ki.wVk;
		input[3].ki.wScan = input[0].ki.wScan;
		input[4].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
		input[4].ki.wVk = input[1].ki.wVk;
		input[4].ki.wScan = input[1].ki.wScan;
		short a = GetKeyState(VK_SHIFT);
		if (!SendInput(key_count, (LPINPUT)input, sizeof(INPUT)))
		{
			//ERROR
			//words words words
		}
		short b = GetKeyState(VK_SHIFT);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::string text = QApplication::clipboard()->text().toStdString();
		Manager::getInstance()->send_hot_key_pressed(QApplication::clipboard()->text().toStdString());
	}
}

void hot_key_listener::stop() {
	start_ = false;
}

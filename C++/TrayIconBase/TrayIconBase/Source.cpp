/*Vinson Liu
This code creates a an icon in the system tray that when double clicked opens a message
box, and closes with a right click*/

#include <Windows.h>	/*windows api: needed for general Window's windows*/
#include <shellapi.h>	/*includes structs and methods needed for tray icons*/
#include "resource.h"	/*includes custome images for icons*/

#define WM_ICON (WM_USER+1)
const char window_class_name[] = "myWindowClass";

/*defines behavior for messages
if this method returns 0, the program will exit the message loop and end*/
LRESULT CALLBACK WindowProcedure(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam){
  switch (message){
    case WM_ICON: /*if it was an event on our icon*/
      switch (lParam){
        case WM_LBUTTONDBLCLK:
          MessageBox(NULL, "This is only a message box but we can change it to a window we make",
            "Title", MB_OK);
          return 1;
          break;
        case WM_RBUTTONUP:
          DestroyWindow(window_handle);
          break;
        default: /*because we've entered a new switch statement we need a new default*/
          return DefWindowProc(window_handle, message, wParam, lParam);
      }
    case WM_CLOSE:
      DestroyWindow(window_handle);
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(window_handle, message, wParam, lParam);
  }
  return 0;
}

/*main function of program*/
int WINAPI WinMain(HINSTANCE handle_instance, HINSTANCE handle_previous_instance,
  char* cmdline_arg, int num_cmdline_arg){
  WNDCLASSEX hidden_window = { 0 };
  HWND handle_window;
  MSG message;

  /*Register window class, i.e. define the properties of a window we want*/
  hidden_window.cbSize = sizeof(WNDCLASSEX);//hidden_window);
  hidden_window.style = 0;
  hidden_window.lpfnWndProc = WindowProcedure;	
    /*pointer to which procedure method handles this window's messages(events)*/
  hidden_window.cbClsExtra = 0;
  hidden_window.hInstance = handle_instance;
  hidden_window.hIcon = LoadIcon(handle_instance, MAKEINTRESOURCE(IDI_ICON1));
  hidden_window.hCursor = LoadCursor(NULL, IDC_ARROW);
  hidden_window.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  hidden_window.lpszMenuName = NULL;
  hidden_window.lpszClassName = window_class_name;
  hidden_window.hIconSm = LoadIcon(handle_instance, MAKEINTRESOURCE(IDI_ICON1));

  if (!RegisterClassEx(&hidden_window)){
	  MessageBox(NULL, "Window Regestration Failed!", "ERROR!",
		  MB_ICONEXCLAMATION | MB_OK);
	  return 0;
  }

  /*create the window*/
  handle_window = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    window_class_name,
    "The title of my window",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
    NULL, NULL, handle_instance, NULL);

  if (handle_window == NULL){
    MessageBox(NULL, "Window Creation Failed!", "Error!",
      MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  NOTIFYICONDATA icon_data;

  icon_data.cbSize = sizeof(icon_data);
  icon_data.hWnd = handle_window;
  icon_data.uID = 100;
  icon_data.uVersion = NOTIFYICON_VERSION;
  icon_data.uCallbackMessage = WM_ICON;
  icon_data.hIcon = LoadIcon(handle_instance, MAKEINTRESOURCE(IDI_ICON1));
  strcpy_s(icon_data.szTip, "TexDump");
  icon_data.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;

  Shell_NotifyIcon(NIM_ADD, &icon_data);

  /*constantly checks for messages*/
  while (GetMessage(&message, NULL, 0, 0) > 0){
    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  return message.wParam;
}

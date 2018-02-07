// Hook.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include<Windows.h>
HHOOK g_hMouse = NULL;
HHOOK g_hKeyboard = NULL;
#pragma data_seg("MySec")
//要在新建的节中放置变量的话，该变量必须是已经经过初始化了的
HWND g_hWnd = NULL;//保存从SetHook传递进来的主窗口句柄，用来发送WM_CLOSE信息
#pragma data_seg()//必须以#pragma data_seg()结束,表示新节的结束。

#pragma comment(linker,"/section:.MySec,RWS")
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	return 1;//返回非0表示已经处理该消息
}
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == VK_F2)
	{
		SendMessage(g_hWnd, WM_CLOSE, wParam, lParam);
		UnhookWindowsHookEx(g_hMouse);
		UnhookWindowsHookEx(g_hKeyboard);
	}
	return CallNextHookEx(g_hKeyboard,nCode,wParam,lParam);
}
VOID SetHook(HWND hWnd)
{
	g_hWnd = hWnd;
	g_hMouse=SetWindowsHookEx(WH_MOUSE, MouseProc, GetModuleHandle("Hook"), 0);//通过 GetModuleHandle("Hook")获取当前dll模块的句柄
	g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, GetModuleHandle("Hook"), 0);

}

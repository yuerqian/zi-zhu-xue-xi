// Hook.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include<Windows.h>
HHOOK g_hMouse = NULL;
HHOOK g_hKeyboard = NULL;
#pragma data_seg("MySec")
//Ҫ���½��Ľ��з��ñ����Ļ����ñ����������Ѿ�������ʼ���˵�
HWND g_hWnd = NULL;//�����SetHook���ݽ����������ھ������������WM_CLOSE��Ϣ
#pragma data_seg()//������#pragma data_seg()����,��ʾ�½ڵĽ�����

#pragma comment(linker,"/section:.MySec,RWS")
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	return 1;//���ط�0��ʾ�Ѿ��������Ϣ
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
	g_hMouse=SetWindowsHookEx(WH_MOUSE, MouseProc, GetModuleHandle("Hook"), 0);//ͨ�� GetModuleHandle("Hook")��ȡ��ǰdllģ��ľ��
	g_hKeyboard = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, GetModuleHandle("Hook"), 0);

}

// dll.cpp : 定义 DLL 应用程序的导出函数。
//


#include "stdafx.h"
#define DLL1_API _declspec(dllexport)
#include"dll.h"
int  add(int a, int b)
{
	return a + b;
}
int  subtract(int a, int b)
{
	return a - b;

}
void  Point::output(int x, int y)
{
	HWND hwnd = GetForegroundWindow();
	HDC hdc = GetDC(hwnd);
    TCHAR buf[20];
	memset(buf, 0, 20);
	wsprintf(buf, __TEXT("x=%d,y=%d"), x, y);
	TextOut(hdc, 0, 0, buf, wcslen(buf));
	ReleaseDC(hwnd,hdc);
}
void Point::test()
{

}
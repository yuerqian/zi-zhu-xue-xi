// 枚举进程.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<Windows.h>
#include<TlHelp32.h>
#include<stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	PROCESSENTRY32 processentry = { 0 };//用来保存进程信息
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//创建快照，堆，模块，线程，进程的快照
	if (hProcessSnap == INVALID_HANDLE_VALUE) return -1;
	processentry.dwSize = sizeof(PROCESSENTRY32);//设置PROCESSENTRY32结构大小
	//通过快照句柄查找系统中的所有进程
	BOOL bRet=Process32First(hProcessSnap, &processentry);//根据快照句柄，查找系统的第一个进程并保存到第二个参数中
	while (bRet)//如果查找到了就查找下一个进程
	{
		printf("ProcessID:%d(%s)\n", processentry.th32ProcessID, processentry.szExeFile);//显示进程ID和名称
		bRet = Process32Next(hProcessSnap, &processentry);//不断查找进程
	}
	CloseHandle(hProcessSnap);
	system("pause");
	return 0;
}


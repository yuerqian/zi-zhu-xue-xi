// 枚举进程3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<Windows.h>
//#include<stdlib.h>
#include<WtsApi32.h>


#pragma comment(lib,"WtsApi32.lib")//导入动态链接库



int _tmain(int argc, _TCHAR* argv[])
{
	DWORD i;
	char* szServerName = "DESKTOP-C1L7LG1";//电脑的名称
	PWTS_PROCESS_INFOA pWtspi;//终端服务的进程信息
	DWORD dwCount;//有多少个进程
	HANDLE hWtsServer=WTSOpenServer(szServerName);//打开电脑，即是将电脑当成服务器
	//枚举进程
	if (!WTSEnumerateProcesses(hWtsServer, 0, 1, &pWtspi, &dwCount))//1.被枚举的电脑名，2.保留，必须是0,3.版本，必须是1,4.所有进程的信息，5.进程个数
	{
		printf("Error!");
		return -1;
	}

	for (i = 0; i < dwCount; i++)
	{
		printf("ProcessID:%d (%s)\n", pWtspi[i].ProcessId, pWtspi[i].pProcessName);
	}
	WTSCloseServer(hWtsServer);//关闭进程
	system("pause");
	return 0;
}


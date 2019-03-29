// 枚举进程2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<Windows.h>
#include<Psapi.h>
void DebugPrivilege();


int _tmain(int argc, _TCHAR* argv[])
{
	//DebugPrivilege();//不调用获取权限函数，将会有部分进程无法打开。事实上调用这个函数也有部分进程无法打开（这个函数没有用？）
	DWORD ProcessID[1024];
	HMODULE hModule[100];
	DWORD cdNeeded;
	DWORD processcount;//计算进程个数
	//枚举所有进程
	if (!EnumProcesses(ProcessID, 1024, &cdNeeded))//第一个参数是枚举了多少个（存放进程的数组），第二参数是枚举的大小，第三个参数是实际进程有多少个（需要除以每个进程所占的大小（DWORD)）
	{
		printf("Faild\n");
		return -1;
	}
	processcount = cdNeeded / sizeof(DWORD);
	printf("当前一共有%d个进程\n",processcount);
	for (DWORD i = 0; i < processcount; i++)
	{
		//printf("ProcessID:%d\n", ProcessID[i]);//显示进程ID
	    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,ProcessID[i]);//需要提升当前进程的权限,第一个参数是访问权限，第二个参数表示所得到的进程句柄是否可以被继承，第三个参数是进程ID
		if (hProcess)
		{
			printf("ProcessID:%d打开成功\n", ProcessID[i]);
			//获取进程的所有模块
			if (EnumProcessModules(hProcess, hModule, sizeof(hModule), &cdNeeded))//1.打开的进程，2.存放模块的数组，3.大小，5.模块个数（需要除以每个模块所占大小HMODULE)
			{
				for (int j = 0; j < (cdNeeded / (sizeof(HMODULE))); j++)
				{
					TCHAR szModname[MAX_PATH];
					if (GetModuleFileNameEx(hProcess, hModule[j], szModname, sizeof(szModname)))//获取所有模块文件名
					{
						printf("\t%d %S (0x%08x)\n", j, szModname, hModule[j]);//注意Unicode编码中%S要用大写，否则用wprintf
					}

				}
			}

		}
		else{
			printf("ProcessID:%d打开失败\n", ProcessID[i]);
		}
		CloseHandle(hProcess);
	}
	system("pause");
	return 0;
}
//提升权限
void DebugPrivilege()
{
	HANDLE hToken = NULL;
	//打开当前进程的访问令牌
	int hRet = OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);

	if (hRet)
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		//取得描述权限的LUID
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		//调整访问令牌的权限
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

		CloseHandle(hToken);
	}
}

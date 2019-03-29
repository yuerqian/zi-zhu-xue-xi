// 枚举进程4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<Windows.h>
#include<NTSecAPI.h>
#include<queue>
using namespace std;

//定义函数指针
typedef DWORD(WINAPI *ZWQUERYSYSTEMINFORMATION)(DWORD, PVOID, DWORD, PDWORD);
//进程信息代号
#define SystemProcessesAndThreadsInformation 5
//进程信息结构
typedef struct _SYSTEM_PROCESS_INFORMATION{
	ULONG          NextEntryDelta;          //构成结构序列的偏移量；    
    ULONG          ThreadCount;             //线程数目；    
    ULONG          Reserved1[6];               
    LARGE_INTEGER  CreateTime;              //创建时间；    
    LARGE_INTEGER  UserTime;                //用户模式(Ring 3)的CPU时间；    
    LARGE_INTEGER  KernelTime;              //内核模式(Ring 0)的CPU时间；    
    UNICODE_STRING ProcessName;             //进程名称；   UNICODE_STRING在另一个头文件里 #include<NTSecAPI.h>
   // KPRIORITY      BasePriority;            //进程优先权；    
    HANDLE         ProcessId;               //进程标识符；    
    HANDLE         InheritedFromProcessId;  //父进程的标识符；    
    ULONG          HandleCount;             //句柄数目；    
    ULONG          Reserved2[2];    
   // VM_COUNTERS    VmCounters;              //虚拟存储器的结构；    
    IO_COUNTERS    IoCounters;              //IO计数结构；    
  //  SYSTEM_THREADS Threads[1];              //进程相关线程的结构数组；    
}SYSTEM_PROCESS_INFORMATION,*PSYSTEM_PROCESS_INFORMATION;

int _tmain(int argc, _TCHAR* argv[])
{
	//ntdll.dll在内核里
	HMODULE hNtdll=GetModuleHandle("ntdll.dll");//获取一个应用程序或动态链接库的模块句柄,必须是已经加载到当前程序中dll或可执行文件
	if (!hNtdll)
	{
		cout << "Error" << endl;
		return -1;
	}
	ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtdll, "ZwQuerySystemInformation");//获取dll里面的函数
	ULONG cdBuffer = 0x10000;
	LPVOID pBuffer = NULL;
	pBuffer = malloc(cdBuffer);//动态分配内存
	if (pBuffer == NULL)
	{
		cout << "Malloc Error!" << endl;
		return -2;
	}
	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation,pBuffer,cdBuffer, NULL);//查询进程信息,1.定义查询什么信息，2.动态分配的内存，3大小，4没有用到的参数，为NULL
    //将pBuffer转成进程信息结构类型  进程信息结构 pInfo=(进程信息结构）pBuffer
	PSYSTEM_PROCESS_INFORMATION pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuffer;

	while (true)
	{
		printf("ProcessID:%d (%s)\n", pInfo->ProcessId, pInfo->ProcessName.Buffer);
		if (pInfo->NextEntryDelta==0)
			break;
		pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);
	}
	free(pBuffer);
	system("pause");
	return 0;
}


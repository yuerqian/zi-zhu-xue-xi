// ö�ٽ���4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<Windows.h>
#include<NTSecAPI.h>
#include<queue>
using namespace std;

//���庯��ָ��
typedef DWORD(WINAPI *ZWQUERYSYSTEMINFORMATION)(DWORD, PVOID, DWORD, PDWORD);
//������Ϣ����
#define SystemProcessesAndThreadsInformation 5
//������Ϣ�ṹ
typedef struct _SYSTEM_PROCESS_INFORMATION{
	ULONG          NextEntryDelta;          //���ɽṹ���е�ƫ������    
    ULONG          ThreadCount;             //�߳���Ŀ��    
    ULONG          Reserved1[6];               
    LARGE_INTEGER  CreateTime;              //����ʱ�䣻    
    LARGE_INTEGER  UserTime;                //�û�ģʽ(Ring 3)��CPUʱ�䣻    
    LARGE_INTEGER  KernelTime;              //�ں�ģʽ(Ring 0)��CPUʱ�䣻    
    UNICODE_STRING ProcessName;             //�������ƣ�   UNICODE_STRING����һ��ͷ�ļ��� #include<NTSecAPI.h>
   // KPRIORITY      BasePriority;            //��������Ȩ��    
    HANDLE         ProcessId;               //���̱�ʶ����    
    HANDLE         InheritedFromProcessId;  //�����̵ı�ʶ����    
    ULONG          HandleCount;             //�����Ŀ��    
    ULONG          Reserved2[2];    
   // VM_COUNTERS    VmCounters;              //����洢���Ľṹ��    
    IO_COUNTERS    IoCounters;              //IO�����ṹ��    
  //  SYSTEM_THREADS Threads[1];              //��������̵߳Ľṹ���飻    
}SYSTEM_PROCESS_INFORMATION,*PSYSTEM_PROCESS_INFORMATION;

int _tmain(int argc, _TCHAR* argv[])
{
	//ntdll.dll���ں���
	HMODULE hNtdll=GetModuleHandle("ntdll.dll");//��ȡһ��Ӧ�ó����̬���ӿ��ģ����,�������Ѿ����ص���ǰ������dll���ִ���ļ�
	if (!hNtdll)
	{
		cout << "Error" << endl;
		return -1;
	}
	ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(hNtdll, "ZwQuerySystemInformation");//��ȡdll����ĺ���
	ULONG cdBuffer = 0x10000;
	LPVOID pBuffer = NULL;
	pBuffer = malloc(cdBuffer);//��̬�����ڴ�
	if (pBuffer == NULL)
	{
		cout << "Malloc Error!" << endl;
		return -2;
	}
	ZwQuerySystemInformation(SystemProcessesAndThreadsInformation,pBuffer,cdBuffer, NULL);//��ѯ������Ϣ,1.�����ѯʲô��Ϣ��2.��̬������ڴ棬3��С��4û���õ��Ĳ�����ΪNULL
    //��pBufferת�ɽ�����Ϣ�ṹ����  ������Ϣ�ṹ pInfo=(������Ϣ�ṹ��pBuffer
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


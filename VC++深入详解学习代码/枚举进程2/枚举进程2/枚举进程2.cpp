// ö�ٽ���2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<Windows.h>
#include<Psapi.h>
void DebugPrivilege();


int _tmain(int argc, _TCHAR* argv[])
{
	//DebugPrivilege();//�����û�ȡȨ�޺����������в��ֽ����޷��򿪡���ʵ�ϵ����������Ҳ�в��ֽ����޷��򿪣��������û���ã���
	DWORD ProcessID[1024];
	HMODULE hModule[100];
	DWORD cdNeeded;
	DWORD processcount;//������̸���
	//ö�����н���
	if (!EnumProcesses(ProcessID, 1024, &cdNeeded))//��һ��������ö���˶��ٸ�����Ž��̵����飩���ڶ�������ö�ٵĴ�С��������������ʵ�ʽ����ж��ٸ�����Ҫ����ÿ��������ռ�Ĵ�С��DWORD)��
	{
		printf("Faild\n");
		return -1;
	}
	processcount = cdNeeded / sizeof(DWORD);
	printf("��ǰһ����%d������\n",processcount);
	for (DWORD i = 0; i < processcount; i++)
	{
		//printf("ProcessID:%d\n", ProcessID[i]);//��ʾ����ID
	    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,ProcessID[i]);//��Ҫ������ǰ���̵�Ȩ��,��һ�������Ƿ���Ȩ�ޣ��ڶ���������ʾ���õ��Ľ��̾���Ƿ���Ա��̳У������������ǽ���ID
		if (hProcess)
		{
			printf("ProcessID:%d�򿪳ɹ�\n", ProcessID[i]);
			//��ȡ���̵�����ģ��
			if (EnumProcessModules(hProcess, hModule, sizeof(hModule), &cdNeeded))//1.�򿪵Ľ��̣�2.���ģ������飬3.��С��5.ģ���������Ҫ����ÿ��ģ����ռ��СHMODULE)
			{
				for (int j = 0; j < (cdNeeded / (sizeof(HMODULE))); j++)
				{
					TCHAR szModname[MAX_PATH];
					if (GetModuleFileNameEx(hProcess, hModule[j], szModname, sizeof(szModname)))//��ȡ����ģ���ļ���
					{
						printf("\t%d %S (0x%08x)\n", j, szModname, hModule[j]);//ע��Unicode������%SҪ�ô�д��������wprintf
					}

				}
			}

		}
		else{
			printf("ProcessID:%d��ʧ��\n", ProcessID[i]);
		}
		CloseHandle(hProcess);
	}
	system("pause");
	return 0;
}
//����Ȩ��
void DebugPrivilege()
{
	HANDLE hToken = NULL;
	//�򿪵�ǰ���̵ķ�������
	int hRet = OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken);

	if (hRet)
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		//ȡ������Ȩ�޵�LUID
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		//�����������Ƶ�Ȩ��
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

		CloseHandle(hToken);
	}
}

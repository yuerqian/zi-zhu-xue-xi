// ö�ٽ���3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<Windows.h>
//#include<stdlib.h>
#include<WtsApi32.h>


#pragma comment(lib,"WtsApi32.lib")//���붯̬���ӿ�



int _tmain(int argc, _TCHAR* argv[])
{
	DWORD i;
	char* szServerName = "DESKTOP-C1L7LG1";//���Ե�����
	PWTS_PROCESS_INFOA pWtspi;//�ն˷���Ľ�����Ϣ
	DWORD dwCount;//�ж��ٸ�����
	HANDLE hWtsServer=WTSOpenServer(szServerName);//�򿪵��ԣ����ǽ����Ե��ɷ�����
	//ö�ٽ���
	if (!WTSEnumerateProcesses(hWtsServer, 0, 1, &pWtspi, &dwCount))//1.��ö�ٵĵ�������2.������������0,3.�汾��������1,4.���н��̵���Ϣ��5.���̸���
	{
		printf("Error!");
		return -1;
	}

	for (i = 0; i < dwCount; i++)
	{
		printf("ProcessID:%d (%s)\n", pWtspi[i].ProcessId, pWtspi[i].pProcessName);
	}
	WTSCloseServer(hWtsServer);//�رս���
	system("pause");
	return 0;
}


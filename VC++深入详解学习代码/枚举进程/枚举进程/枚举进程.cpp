// ö�ٽ���.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<Windows.h>
#include<TlHelp32.h>
#include<stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	PROCESSENTRY32 processentry = { 0 };//�������������Ϣ
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//�������գ��ѣ�ģ�飬�̣߳����̵Ŀ���
	if (hProcessSnap == INVALID_HANDLE_VALUE) return -1;
	processentry.dwSize = sizeof(PROCESSENTRY32);//����PROCESSENTRY32�ṹ��С
	//ͨ�����վ������ϵͳ�е����н���
	BOOL bRet=Process32First(hProcessSnap, &processentry);//���ݿ��վ��������ϵͳ�ĵ�һ�����̲����浽�ڶ���������
	while (bRet)//������ҵ��˾Ͳ�����һ������
	{
		printf("ProcessID:%d(%s)\n", processentry.th32ProcessID, processentry.szExeFile);//��ʾ����ID������
		bRet = Process32Next(hProcessSnap, &processentry);//���ϲ��ҽ���
	}
	CloseHandle(hProcessSnap);
	system("pause");
	return 0;
}


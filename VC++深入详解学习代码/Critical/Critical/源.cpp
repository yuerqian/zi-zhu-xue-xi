#include<Windows.h>
#include<iostream>
#include<tchar.h>
using namespace std;
DWORD WINAPI Fun1Proc(LPVOID lpParam);
DWORD WINAPI Fun2Proc(LPVOID lpParam);
int tickets = 100;
CRITICAL_SECTION g_csA;
CRITICAL_SECTION g_csB;
void main()
{
	HANDLE hThread1;
	HANDLE hThread2;

	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	InitializeCriticalSection(&g_csA);
	InitializeCriticalSection(&g_csB);
	Sleep(4000);
	DeleteCriticalSection(&g_csA);
	DeleteCriticalSection(&g_csB);
	system("pause");
}
DWORD WINAPI Fun1Proc(LPVOID lpParam)
{
	while (TRUE)
	{
		EnterCriticalSection(&g_csA);
		Sleep(1);
		EnterCriticalSection(&g_csB);
		if (tickets > 0)
		{
			Sleep(1);
			cout << "Thread1 sell ticket:" << tickets-- << endl;
			LeaveCriticalSection(&g_csA);
			LeaveCriticalSection(&g_csB);
		}
		else
		{
			LeaveCriticalSection(&g_csA);
			LeaveCriticalSection(&g_csB);
			break;
		}

	}
	return 0;
}
DWORD WINAPI Fun2Proc(LPVOID lpParam)
{
	while (TRUE)
	{
		EnterCriticalSection(&g_csB);
		Sleep(1);
		EnterCriticalSection(&g_csA);
		if (tickets > 0)
		{
			Sleep(1);
			cout << "Thread2 sell ticket:" << tickets-- << endl;
			LeaveCriticalSection(&g_csA);
			LeaveCriticalSection(&g_csB);
		}
		else
		{
			LeaveCriticalSection(&g_csA);
			LeaveCriticalSection(&g_csB);
			break;
		}
	}
	return 0;
}
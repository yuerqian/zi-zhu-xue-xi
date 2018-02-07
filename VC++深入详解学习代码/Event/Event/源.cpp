#include<Windows.h>
#include<iostream>
#include<tchar.h>
using namespace std;
DWORD WINAPI Fun1Proc(LPVOID lpParam);
DWORD WINAPI Fun2Proc(LPVOID lpParam);
int tickets = 100;
HANDLE g_hEvent;
void main()
{
	HANDLE hThread1;
	HANDLE hThread2;
	g_hEvent=CreateEvent(NULL, FALSE, FALSE, _T("tickets"));
	if (g_hEvent)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			cout << "only one instance can run" << endl;
			return;
		}
	}
	SetEvent(g_hEvent);
	hThread1=CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	hThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	Sleep(4000);
	system("pause");
}
DWORD WINAPI Fun1Proc(LPVOID lpParam)
{
	while (TRUE)
	{
		WaitForSingleObject(g_hEvent, INFINITE);
		if (tickets > 0)
		{
			Sleep(1);
			cout << "Thread1 sell ticket:" << tickets-- << endl;
			SetEvent(g_hEvent);
			
		}
		else
		{
			SetEvent(g_hEvent);
			break;
		}

	}
	return 0;
}
DWORD WINAPI Fun2Proc(LPVOID lpParam)
{
	while (TRUE)
	{
		WaitForSingleObject(g_hEvent, INFINITE);
		if (tickets > 0)
		{
			Sleep(1);
			cout << "Thread2 sell ticket:" << tickets-- << endl;
			SetEvent(g_hEvent);
		}
		else
		{
			SetEvent(g_hEvent);
			break;
		}
	}
	return 0;
}
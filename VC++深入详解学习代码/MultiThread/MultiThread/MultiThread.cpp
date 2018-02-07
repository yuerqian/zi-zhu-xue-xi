#include<Windows.h>
#include<iostream>
using namespace std;
DWORD WINAPI Function1Thread(LPVOID lpPagrameter);
DWORD WINAPI Function2Thread(LPVOID lpPagrameter);
int i = 0;
int ticket = 100;
HANDLE hMutex;
void main()
{
	HANDLE NewThread1=NULL;
	HANDLE NewThread2 = NULL;
	NewThread1 = CreateThread(NULL, 0, Function1Thread, NULL, 0, NULL);
	NewThread2 = CreateThread(NULL, 0, Function2Thread, NULL, 0, NULL);
	CloseHandle(NewThread1);
	CloseHandle(NewThread2);

	hMutex = CreateMutex(NULL, FALSE, "ticket");
	if (hMutex)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			cout << "only on instance can run" << endl;
			return;
		}
	}
	
	//Sleep(10);
	/*while (ii++ < 1000)
	{
		cout << "main Thread Is Running" << endl;
	}*/
	Sleep(4000);
	system("pause");
}
DWORD WINAPI Function1Thread(LPVOID lpParameter)
{
	//while (i++ < 1000)
	//{
	//	cout << "ÄãºÃ" << endl;
	//}
	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (ticket > 0)
		{
			Sleep(1);
			cout << "thread1 sell ticket:" << ticket-- << endl;
		}
		else
			break;
		ReleaseMutex(hMutex);
	}
	return 0;
}
DWORD WINAPI Function2Thread(LPVOID lpParameter)
{
	while (1)
	{
		WaitForSingleObject(hMutex, INFINITE);
		if (ticket > 0)
		{
			Sleep(1);
			cout << "thread2 sell ticket:" << ticket-- << endl;
		}
		else
			break;
		ReleaseMutex(hMutex);
	}
	return 0;
}
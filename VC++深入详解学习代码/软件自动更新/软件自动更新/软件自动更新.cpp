// 软件自动更新.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Shlwapi.h>
#pragma comment(lib, "WS2_32")  // 链接到WS2_32.lib

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (::WSAStartup(sockVersion, &wsaData) != 0)
	{
		::WSACleanup();
		return FALSE;
	}
	SOCKET sClient;
	int ret;
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		return FALSE;
	}
	
	// set Recv and Send time out
	int TimeOut = 8000; // 设置发送超时8秒
	if (setsockopt(sClient, SOL_SOCKET, SO_SNDTIMEO, (char *)&TimeOut, sizeof(TimeOut)) == SOCKET_ERROR)
	{
		closesocket(sClient);
		return FALSE;
	}


	if (setsockopt(sClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&TimeOut, sizeof(TimeOut)) == SOCKET_ERROR)
	{
		closesocket(sClient);
		return FALSE;
	}

	unsigned long ul = 1;
	ret = ioctlsocket(sClient, FIONBIO, (unsigned long *)&ul);
	if (ret == SOCKET_ERROR)
	{
		closesocket(sClient);
		return FALSE;
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(80);
	struct hostent *pURL = gethostbyname("www.yanxin8.com");
	//const char* ip = "115.28.9.132";
	//server.sin_addr.s_addr = inet_addr(ip);
	server.sin_addr.s_addr = *((unsigned long*)pURL->h_addr);
	if (server.sin_addr.s_addr == INADDR_NONE)
	{
		closesocket(sClient);
		return FALSE;
	}
	BOOL bConnRe = FALSE;
	if (connect(sClient, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		struct timeval timeout_val;
		fd_set set;
		FD_ZERO(&set);
		FD_SET(sClient, &set);
		timeout_val.tv_sec = 1;
		timeout_val.tv_usec = 0;
		if (select(0, NULL, &set, NULL, &timeout_val) > 0)
		{
			bConnRe = TRUE;
		}
		else
			bConnRe = FALSE;
	}
	else
		bConnRe = TRUE;

	if (!bConnRe)
	{
		closesocket(sClient);
		return FALSE;
	}

	int nRecv = 0;
	///version.txt
	char *request = "GET /version.txt HTTP/1.0\r\nHost:www.yanxin8.com\r\nConnection: Close\r\n\r\n";
	ret = send(sClient, request, strlen(request), 0);
	Sleep(300);

	char buf[2000] = { 0 };
	nRecv = ::recv(sClient, buf, 2000, 0);
	if (nRecv > 0){
		string str(buf);
		//strstr(buf, "noteCard=");
		int pos1 = str.find("noteCard=");
		if (pos1 != -1){
			pos1 += 9;
			int pos2 = str.find(";", pos1);
			verstr = str.substr(pos1, pos2 - pos1);
			return true;
		}
	}
	return 0;
}


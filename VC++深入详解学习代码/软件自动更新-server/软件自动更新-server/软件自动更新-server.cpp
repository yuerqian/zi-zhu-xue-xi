// 软件自动更新-server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Shlwapi.h>
#pragma comment(lib, "WS2_32")  // 链接到WS2_32.lib


int _tmain(int argc, _TCHAR* argv[])
{
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
	return 0;
}


#include<WinSock2.h>
#include<stdio.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
void main()
{
	WORD wVersionReq;
	wVersionReq = MAKEWORD(1, 1);
	WSADATA WsadataClient;
	if (WSAStartup(wVersionReq, &WsadataClient) != 0)
	{
		return;
	}
	if (LOBYTE(WsadataClient.wVersion) != 1 || HIBYTE(WsadataClient.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	if (connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(addrSrv)) == SOCKET_ERROR)
	{
		WSACleanup();
		return;
	}

	char recvBuf[100];
	char sendBuf[100];
	while (1)
	{
		memset(recvBuf, 0, 100);
		
		recv(sockClient, recvBuf, 100, 0);
		printf("service:%s\n", recvBuf);
		printf("input data:");
		/*scanf_s("%s",sendBuf, 100);*/
		gets_s(sendBuf,100);
		send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
		


	}
	closesocket(sockClient);
	WSACleanup();
	system("pause");


}
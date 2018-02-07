#include<WinSock2.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")
void main()
{
	WORD wVersionReq;
	wVersionReq = MAKEWORD(1, 1);
	WSADATA Wsadata;
	if (WSAStartup(wVersionReq, &Wsadata))
	{
		WSACleanup();
		return;
	}
	if (LOBYTE(Wsadata.wVersion) != 1 || HIBYTE(Wsadata.wVersion)!=1)
	{
		WSACleanup();
		return;
	}
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in addrSrv;
	addrSrv.sin_addr.S_un.S_addr = INADDR_ANY;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(80);
	if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		WSACleanup();
		return;
	}
	char recvBuf[100];
	char sendBuf[100];
	char tempBuf[100];
	sockaddr_in addrClient;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
		if (recvBuf[0] == 'q')
		{
			sendto(sockSrv, "q", strlen("q") + 1, 0, (SOCKADDR*)&addrClient, len);
			printf("Chat End\n");
			break;
		}
		sprintf_s(tempBuf, "%s say:%s", inet_ntoa(addrClient.sin_addr), recvBuf);
		printf("%s\n", tempBuf);
		printf("Please input data:\n");
		gets_s(sendBuf);
		sendto(sockSrv, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrClient, len);
	}
	closesocket(sockSrv);
	WSACleanup();
	system("pause");
	int a = 0;
	scanf_s("%d", a);
}

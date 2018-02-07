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
	if (LOBYTE(Wsadata.wVersion) != 1 || HIBYTE(Wsadata.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.10.246");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(80);
	char sendBuf[100];
	char recvBuf[100];
	char tempBuf[100];
	SOCKADDR_IN addrRecvSrv;
	int len = sizeof(SOCKADDR);
	while (1)
	{
		printf("Please input data:\n");
		scanf_s("%s",sendBuf,100);//gets_s(sendBuf);
		sendto(sockClient, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
		recvfrom(sockClient, recvBuf, 100, 0, (SOCKADDR*)&addrRecvSrv, &len);
		if (recvBuf[0] == 'q')
		{
			sendto(sockClient, "q", strlen("q") + 1, 0, (SOCKADDR*)&addrSrv, len);
			printf("Chat End\n");
			break;
		}
		sprintf_s(tempBuf, "%s say: %s", inet_ntoa(addrRecvSrv.sin_addr), recvBuf);
		printf("%s\n", tempBuf);

	}
	closesocket(sockClient);
	WSACleanup();
	system("pause");
}

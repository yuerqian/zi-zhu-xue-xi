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
	addrSrv.sin_port = htons(6000);
	if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		WSACleanup();
		return;
	}
	char recvBuf[100];
	sockaddr_in recvAddr;
	int len = sizeof(recvAddr);
	recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&recvAddr, &len);
	printf("Client:%s\n", recvBuf);
	closesocket(sockSrv);
	WSACleanup();
	system("pause");
	int a=0;
	scanf_s("%d", a);

}
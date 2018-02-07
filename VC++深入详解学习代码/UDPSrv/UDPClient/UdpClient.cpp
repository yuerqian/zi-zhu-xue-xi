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
	SOCKET sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	sendto(sockClient, "hallo", strlen("hallo")+1, 0, (SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	closesocket(sockClient);
	WSACleanup();
	system("pause");



}
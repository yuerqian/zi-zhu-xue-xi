#include<WinSock2.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")
void main()
{
	WORD VersionSrv;
	VersionSrv = MAKEWORD(1, 1);
	WSADATA wsadataSrv;
	if (WSAStartup(VersionSrv, &wsadataSrv) != 0)
	{
		return;
	}
	if (LOBYTE(wsadataSrv.wVersion) != 1 || HIBYTE(wsadataSrv.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); /*htonl(inet_addr("192.168.0.0"));*/
	addrSrv.sin_port = htons(6000);
	if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(addrSrv)) == SOCKET_ERROR)
	{
		WSACleanup();
		return;
	}
	if (listen(sockSrv, 5) != 0)
	{
		return;
	}
	sockaddr_in addrClient;
	int len = sizeof(addrClient);
	SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
	while (1)
	{
		
		char sendBuf[100];
		char recvBuf[100];
		printf("input data:");
		/*scanf_s("%s",sendBuf, 100);*/
		gets_s(sendBuf,100);
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		/*sprintf(sendBuf, "Welcome %s to http://www.sunxin.org", inet_ntoa(addrClient.sin_addr));
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);*/

		recv(sockConn, recvBuf, 100, 0);
		printf("%s sya:%s\n", inet_ntoa(addrClient.sin_addr), recvBuf);
		//sprintf(sendBuf, "Welcome %s to http://www.sunxin.org", inet_ntoa(addrClient.sin_addr));
		/*closesocket(sockConn);*/

	}
	WSACleanup();
	closesocket(sockSrv);

}
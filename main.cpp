#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<WinSock2.h>
#pragma comment(lib,"WS2_32.lib")
using namespace std;

int main()
{

	WSAData wsaData;
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (Result < 0)
	{
		cout << "Error : " << GetLastError() << '\n';
		exit(-1);
	}

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(SOCKADDR_IN));

	ServerAddr.sin_family = PF_INET;
	ServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_port = htons(54987);

	int Status = connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (Status == SOCKET_ERROR)
	{
		cout << "ERROR : " << GetLastError() << '\n';
		exit(-1);
	}

	while (1)
	{
		char Buffer[1024] = { 0, };
		int RecvBytes = recv(ServerSocket, Buffer, 1024, 0);
		if (RecvBytes <= 0)
		{
			cout << "Error : " << GetLastError() << '\n';
			exit(-1);
		}

		string Message;
		cin >> Message;

		int SendBytes = send(ServerSocket, Message.c_str(), Message.size() + 1, 0);
		if (SendBytes <= 0)
		{
			cout << "Error : " << GetLastError() << '\n';
			exit(-1);
		}

		fflush(stdin);


	}

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}
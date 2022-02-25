#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <string>

using namespace std;

#pragma comment (lib,"ws2_32.lib")


int main()
{

	//윈속 초기화
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "WinSock Error : " << GetLastError() << endl;
		exit(-1);
	}
	//소켓생성
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error : " << GetLastError() << endl;
		exit(-1);
	}
	//ip랑 port 할당해서 소켓연결
	//SOCKADDR_IN ServerAddr;

	//memset(&ServerAddr, 0, sizeof(ServerAddr));

	//ServerAddr.sin_family = AF_INET;
	//ServerAddr.sin_port = htons(50000);
	//ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);


	SOCKADDR_IN ServerAddr;

	memset(&ServerAddr, 0, sizeof(ServerAddr));

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(5001);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "Bind Error : " << GetLastError() << endl;
		exit(-1);
	}

	//listen

	if (listen(ServerSocket, 0) == SOCKET_ERROR)
	{
		cout << "Listen Error : " << GetLastError() << endl;
		exit(-1);
	}

	//Accept
	while (1)
	{
		SOCKADDR_IN ClientAddr;

		int ClientAddrSize = sizeof(ClientAddr);
		SOCKET ClientSocket = 0;
		ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize);
		if (ClientSocket == SOCKET_ERROR)
		{
			cout << "Accept Error : " << GetLastError() << endl;
			exit(-1);
		}

		cout << "connect ip : " << inet_ntoa(ClientAddr.sin_addr) << endl;
		cout << "connect port : " << ntohs(ClientAddr.sin_port) << endl;

		//recv
		char Message[1024] = { 0, };
		recv(ClientSocket, Message, 1024 - 1, 0);

		cout << "client sended : " << Message << endl;
		//send
		send(ClientSocket, Message, strlen(Message) + 1, 0);

		cout << "client send : " << Message << endl;
		//소켓 닫기
		closesocket(ClientSocket);
	}

	closesocket(ServerSocket);
	
	//윈속 종료
	WSACleanup();
}
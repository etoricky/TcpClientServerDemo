// Microsoft Development Environment 2003 - Version 7.1.3088
// Copyright (r) 1987-2002 Microsoft Corporation. All Right Reserved
// Microsoft .NET Framework 1.1 - Version 1.1.4322
// Copyright (r) 1998-2002 Microsoft Corporation. All Right Reserved
//
// Run on Windows XP Pro machine, version 2002, SP 2
//
// <windows.h> already included
// WINVER = 0x0501 for Xp already defined in windows.h
// A sample of client program

#include <stdio.h>
#include <winsock2.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

int main()
{
	// Initialize Winsock.
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		printf("Client: Error at WSAStartup().\n");
		return -1;
	}

	// Create a socket.
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}

	// Connect to a server.
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientService.sin_port = htons(55555);

	if (connect(sock, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		printf("Client: connect() - Failed to connect.\n");
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	// Send and receive data.
	
	// Be careful with the array bound, provide some checking mechanism
	char sendbuf[200] = "Client: Sending some test string to server...";
	char recvbuf[200] = "";

	int bytesSent = send(sock, sendbuf, strlen(sendbuf), 0);
	if (bytesSent == SOCKET_ERROR) {
		printf("send() error %ld.\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return -1;
	}
	printf("bytesSent: %ld\n", bytesSent);
	printf(sendbuf);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(sock, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return -1;
	}

	int bytesRecv = 0;
	do {
		bytesRecv = recv(sock, recvbuf, 32, 0);
		if (bytesRecv == SOCKET_ERROR) {
			printf("recv() error %ld.\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return -1;
		}
		else if (bytesRecv==0) {
			printf("Server closed connection, i.e. recv() return 0\n");
		}
		printf("bytesRecv: %ld\n", bytesRecv);
		printf(recvbuf);
	} while (bytesRecv>0);

	return 0;
}
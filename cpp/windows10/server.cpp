// Microsoft Development Environment 2003 - Version 7.1.3088
// Copyright (r) 1987-2002 Microsoft Corporation. All Right Reserved
// Microsoft .NET Framework 1.1 - Version 1.1.4322
// Copyright (r) 1998-2002 Microsoft Corporation. All Right Reserved
//
// Run on Windows XP Pro machine, version 2002, SP 2
//
// <windows.h> already included...
// WINVER = 0x0501 for Xp already defined in windows.h

#include <stdio.h>
#include <winsock2.h>

#pragma comment (lib, "Ws2_32.lib")

int main()
{
	WSADATA wsaData;
	int wsaerr = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaerr != 0)
	{
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.*/
		printf("The Winsock dll not found!\n");
		return 0;
	} else {
		printf("The Winsock dll found!\n");
		printf("The status: %s.\n", wsaData.szSystemStatus);
	}

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.*/
		printf("The dll do not support the Winsock version %u.%u!\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
		WSACleanup();
		return 0;
	}
	else
	{
		printf("The dll supports the Winsock version %u.%u!\n", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
		printf("The highest version this dll can support: %u.%u\n", LOBYTE(wsaData.wHighVersion), HIBYTE(wsaData.wHighVersion));
	}

	/* The next task... */
	//////////Create a socket////////////////////////

	//Create a SOCKET object called m_socket.
	// Check for errors to ensure that the socket is a valid socket.
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if (listenSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return 0;
	}
	else
	{
		printf("socket() is OK!\n");
	}

	////////////////bind()//////////////////////////////
	// Create a sockaddr_in object and set its values.
	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(55555);
	
	// Call the bind function, passing the created socket and the sockaddr_in structure as parameters.
	// Check for general errors.
	if (bind(listenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
	{
		printf("bind() failed: %ld.\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return -1;
	}
	else
	{
		printf("bind() ok\n");
	}

	// Call the listen function, passing the created socket and the maximum number of allowed
	// connections to accept as parameters. Check for general errors.
	if (listen(listenSocket, 5) == SOCKET_ERROR) {
		printf("listen(): Error listening on socket %ld.\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return -1;
	}
	else
	{
		printf("listen() ok\n");
	}

	// Create a temporary SOCKET object called AcceptSocket for accepting connections.
	

	// Create a continuous loop that checks for connections requests. If a connection
	// request occurs, call the accept function to handle the request.
	printf("Server: Waiting for a client to connect...\n");
	printf("***Hint: Server is ready...run your client program...***\n");

	char sendbuf[200] = "Server sent this message\n";
	char recvbuf[200] = "";

	// Do some verification...
	while (1)
	{
		SOCKET sock = SOCKET_ERROR;
		while (sock == SOCKET_ERROR)
		{
			sock = accept(listenSocket, NULL, NULL);
		}

		// else, accept the connection...
		// When the client connection has been accepted, transfer control from the
		// temporary socket to the original socket and stop checking for new connections.
		printf("Server: Client Connected!\n");

		int bytesRecv = recv(sock, recvbuf, 32, 0); // maybe SOCKET_ERROR
		if (bytesRecv == SOCKET_ERROR) {
			printf("recv() error %ld.\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			break;
		}
		printf("bytesRecv: %ld\n", bytesRecv);
		printf(recvbuf);

		int bytesSent = send(sock, sendbuf, strlen(sendbuf), 0);
		if (bytesSent == SOCKET_ERROR) {
			printf("send() error %ld.\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			break;
		}
		printf("bytesSent: %ld\n", bytesSent);
		printf(sendbuf);

		// shutdown the connection since we're done
		int iResult = shutdown(sock, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return 1;
		}
		
	}
	
	return 0;
}
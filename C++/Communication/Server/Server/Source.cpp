#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")


void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main() 
{
	char ipstr[INET_ADDRSTRLEN];
	WSADATA wsaData;

	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	#define DEFAULT_PORT "27015"

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	char hostname[128];
	gethostname(hostname, 128);
	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(hostname, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	inet_ntop(result->ai_family, get_in_addr((struct sockaddr *)result->ai_addr), ipstr, sizeof ipstr);
	printf("Server's IP: ");
	printf(ipstr);
	printf("\n\r");
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	SOCKET ClientSock = SOCKET_ERROR;
	SOCKADDR_IN client_info = { 0 };
	int addrsize = sizeof(client_info);


	while (ClientSock == SOCKET_ERROR)
	{
		ClientSock = accept(ListenSocket, (struct sockaddr*)&client_info, NULL);
	}
	getpeername(ClientSock, (struct sockaddr*)&client_info, &addrsize);

	char *ip = inet_ntoa(client_info.sin_addr);

	printf("Connected to: %s\r\n", ip);

	
	#define DEFAULT_BUFLEN 512

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSock, recvbuf, recvbuflen, 0);
		if (iResult > 0) 
		{
			for (int i = 0; i < iResult; i++)
			{
				printf("%c",recvbuf[i]);
			}
			printf("\n\r");
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed: %d\n", WSAGetLastError());
			closesocket(ClientSock);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);
	return 0;
}

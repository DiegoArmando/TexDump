#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

int main()
{

	WSADATA wsaData;

	int iResult;

	// Initialize Winsock2
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	struct addrinfo *result = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;//IP version 4
	hints.ai_socktype = SOCK_STREAM;//Work like a pipe
	hints.ai_protocol = IPPROTO_TCP;//TCP protocol

	#define DEFAULT_PORT "27015"

	// Resolve the server address and port. IP address is of the server
	iResult = getaddrinfo("129.161.205.96", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}


	SOCKET ConnectSocket = INVALID_SOCKET;

	// Create a SOCKET for connecting to server with 
	ConnectSocket = socket(result->ai_family, result->ai_socktype,result->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	//Connect to server's socket. The servers socket is binded to a socket address 
	//with the configurations that the addrinfo result gathered.
	iResult = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	// Should really try the next address returned by getaddrinfo
	// if the connect call failed

	freeaddrinfo(result);//delete result and free memory

	#define DEFAULT_BUFLEN 512
	char *sendbuf = "this is a test";
	
	// Send an initial buffer
	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	while (true)
	{
		std::string temp;
		getline(std::cin,temp);//gather new line from user input
		iResult = send(ConnectSocket, temp.c_str(), temp.length(), 0);//send user input to server
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
	}


	return 0;
}

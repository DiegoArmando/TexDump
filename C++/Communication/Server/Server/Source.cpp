#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

/*This function takes in a sockaddr, determines weather it is IPv4 of IPv6 and then returnes 
  an IN_ADDR(IP address container) with the IP address in the sockaddr. This is currently used to
  display the IP address to the console.
 */
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main() 
{
	char ipstr[INET_ADDRSTRLEN];//This will contain the char* of the IP address in readable format
	WSADATA wsaData;//This is used to initialize Winsock

	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	#define DEFAULT_PORT "27015"//This is the port that the server will bind and listen to.

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	/* In this block of code determine the addrinfo so that the server can create a socket that
	will bind and listen to this particular address
	*/
	ZeroMemory(&hints, sizeof (hints));//Makes all values in hints 0 
	hints.ai_family = AF_INET;//IPv4
	hints.ai_socktype = SOCK_STREAM;//Communication works similar to a pipe
	hints.ai_protocol = IPPROTO_TCP;//TCP protocol
	hints.ai_flags = AI_PASSIVE;//Socket address is capable of binding and listening
	char hostname[128];
	gethostname(hostname, 128);//retrieves local host name and sets it to hostname
	//Using the hints, figure out the full information of the socket address
	iResult = getaddrinfo(hostname, DEFAULT_PORT, &hints, &result);//function returns number of addresses that match requirements
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}


	//set ipstr to the ip address of the address in the addrinfo variable result.
	inet_ntop(result->ai_family, get_in_addr((struct sockaddr *)result->ai_addr), ipstr, sizeof ipstr);
	printf("Server's IP: ");
	printf(ipstr);
	printf("\n\r");


	SOCKET ListenSocket = INVALID_SOCKET;//Declare the socket
	//Initalize socket using the result's characteristics
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) 
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	//Bind socket to the address in result
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	//configure socket to be listening for attemted connections. SOMAXCONN maximum number of connections.
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	SOCKET ClientSock = SOCKET_ERROR;//Declare a Client Socket
	SOCKADDR_IN client_info = { 0 };//Socket info of client 
	int addrsize = sizeof(client_info);


	while (ClientSock == SOCKET_ERROR)//Never stop trying to connect to a client
	{
		//Accept a connection implemented by a client
		ClientSock = accept(ListenSocket, NULL, NULL);
	}
	//gets the sockaddr infomation of the clients socket
	getpeername(ClientSock, (struct sockaddr*)&client_info, &addrsize);

	char *ip = inet_ntoa(client_info.sin_addr);//Only works for IPv4

	printf("Connected to: %s\r\n", ip);

	
	#define DEFAULT_BUFLEN 512

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Receive until the peer shuts down the connection
	do {
		//The code waits until something is recieved accross the client socket.
		//Stores recieved data in recvbuf and buffer lenght in recvbuflen
		//when a connection is closed an empty packet is sent to the server
		//iResult should be equivelent to recvbuflen
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

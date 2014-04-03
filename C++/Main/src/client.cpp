#include "client.h"

Client* Client::getInstance() {
	static Client client;
	return &client;
}

int Client::init()
{
	WSADATA wsaData;
	char ipstr[INET_ADDRSTRLEN];//This will contain the char* of the IP address in readable format
	int iResult;

	// Initialize Winsock2
	iResult = WSAStartup(MAKEWORD(2, 0), &wsaData);
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

	
	// Resolve the server address and port. IP address is of the server
	iResult = getaddrinfo("23.253.54.98", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	inet_ntop(result->ai_family, get_in_addr((struct sockaddr *)result->ai_addr), ipstr, sizeof ipstr);
	printf("Trying to connect to ==> ");
	printf(ipstr);
	printf(":%d", ntohs(((struct sockaddr_in *)result->ai_addr)->sin_port));
	printf("\n\r");


	ConnectSocket = INVALID_SOCKET;

	// Create a SOCKET for connecting to server with 
	ConnectSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
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
	return 0;
}
void Client::listening_thread()
{
	int iResult;
	while (true)
	{
		iResult = recv(ConnectSocket, recvbuf, 512, 0);
		if (iResult>0)
		{
			printf("Message: ");
			printf(recvbuf);
			printf("\n");
			Sleep(1000);
			
			if (recvbuf[0])
			{
				std::string mess(recvbuf);
				Message * message = new Message(mess.substr(mess.find(":") + 1), "", mess.substr(0, mess.find(":")));
				Manager::getInstance()->receive_message(*message);
				memset(recvbuf, 0, sizeof(recvbuf));
			}
			
			
		}
		else
			break;
	}
}

std::vector<std::string> Client::get_devices()
{
	std::vector<std::string> devices;
	std::string input = "GET_DEVICES:\0";
	send(ConnectSocket, input.c_str(),input.length(), 0);
	Sleep(100);
	std::string temp="";
	for(unsigned int i = 0; i <512 ; i++)
	{
		if (recvbuf[i] == ':')
		{
			devices.push_back(temp);
			temp = "";
		}
		else
			temp += recvbuf[i];
	}
	memset(recvbuf, 0, sizeof(recvbuf));
	printf("Devices: ");
	for (int i = 0; i < devices.size(); i++)
	{
		printf("%s,", devices[i].c_str());
	}
	printf("\n");
	return devices;

}
void Client::send_message(std::string message,std::string destination)
{
	std::string temp = "SEND_TO_" + destination + ":" + message+"\0";
	send(ConnectSocket, temp.c_str(), temp.length(), 0);
}
void Client::set_name(std::string _name)
{
	std::string temp("SET_NAME:");
	temp += _name;
	send(ConnectSocket, temp.c_str(), temp.length(), 0);
}
void *Client::get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
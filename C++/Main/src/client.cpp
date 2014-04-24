#include "client.h"

//returns the one instance of Client class
Client* Client::getInstance() {
	static Client client;
	return &client;
}
//initilzes connection to server and connects
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
//waits for incoming messages from server performs appropriate actions
void Client::listeningThread()
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
			std::string mess(recvbuf);
			if (mess.find(":") > 0)
			{
				if (mess.substr(0, mess.find(":")).compare("ERROR") == 0)
				{
					errorRecieved = true;
					errorFromServer = mess.substr(mess.find(":") + 1);
				}
				else if (mess.substr(0, mess.find(":")).compare("MESSAGE") == 0)
				{
					int pos = mess.find(":");
					int pos2 = mess.find("%:%", pos + 3);
					int pos3 = mess.find("%:%", pos2 + 3);
					Message * message = new Message(mess.substr(pos3 + 3), mess.substr(pos2 + 3, pos3 - pos2 - 1), mess.substr(pos + 3, pos2 - pos - 1));
					Manager::getInstance()->receive_message(*message);
					memset(recvbuf, 0, sizeof(recvbuf));
				}
				else if (mess.substr(0, mess.find(":")).compare("LOGGED_IN") == 0)
				{
					loggedIn = true;
				}
			}
			else
				break;
			
		}
	}
}

void Client::login(std::string username, std::string password, std::string deviceName)
{
	std::string out = "LOGIN:";
	out += username;
	out += ":";
	out += password;
	out += ":";
	out += deviceName;

	send(ConnectSocket, out.c_str(), out.length(), 0);

}
void Client::createUser(std::string username, std::string password, std::string deviceName, std::string email)
{
	std::string out = "REGISTER:";
	out += username;
	out += ":";
	out += password;
	out += ":";
	out += deviceName;
	out += ":";
	out += email;

	send(ConnectSocket, out.c_str(), out.length(), 0);
}
//returns a vector of connected devices
std::vector<std::string> Client::getDevices()
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
	for (unsigned int i = 0; i < devices.size(); i++)
	{
		printf("%s,", devices[i].c_str());
	}
	printf("\n");
	return devices;

}
//sends message to destination(through server)
void Client::sendMessage(std::string message,std::string destination)
{
	std::string temp = "SEND_TO_" + destination + ":" + message+"\0";
	send(ConnectSocket, temp.c_str(), temp.length(), 0);
}
//sets the name of the connection and sets it on server
void Client::setDeviceName(std::string _name)
{
	std::string temp("SET_NAME:");
	temp += _name;
	send(ConnectSocket, temp.c_str(), temp.length(), 0);
}
//used to help get ip address
void *Client::get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

bool Client::isLoggedIn()
{
	return loggedIn;
}
bool Client::errorOccurred()
{
	if (errorRecieved)
	{
		errorRecieved = false;
		return true;
	}
	return false;
}
std::string Client::getCurrentError()
{
	return errorFromServer;
}
#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <vector>
#include <conio.h>
#include <windows.h>
#include "message.h"
#include "manager.h"

#define DEFAULT_PORT "51723"

#pragma comment(lib, "Ws2_32.lib")

class Client
{
public:
	
	static Client* getInstance();//returns the one instance of Client class
	int init();//initilzes connection to server and connects
	void listeningThread();//waits for incoming messages from server performs appropriate actions
	void sendMessage(std::string message,std::string destination);//sends message to destination(through server)
	std::vector<std::string> getDevices();//returns a vector of connected devices
	void setDeviceName(std::string name);//sets the name of the connection and sets it on server
	void login(std::string username, std::string password, std::string deviceName);
	void createUser(std::string username, std::string password, std::string deviceName, std::string email);
	bool isLoggedIn();
	bool errorOccurred();
	std::string getCurrentError();

private:
	SOCKET ConnectSocket;//socket that will be connected to server
	char recvbuf[512];//buffer that is updated by listening_thread()

	bool loggedIn=false;
	bool errorRecieved = false;
	std::string errorFromServer;

	//used to make sure only one instance of Client class exists
	Client(){ };
	Client(Client const&){ };
	void operator=(Client const&){};

	//used to help get ip address
	void *get_in_addr(struct sockaddr *sa);
	
};


#endif
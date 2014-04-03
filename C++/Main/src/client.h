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
	void listening_thread();//waits for incoming messages from server performs appropriate actions
	void send_message(std::string message,std::string destination);//sends message to destination(through server)
	std::vector<std::string> get_devices();//returns a vector of connected devices
	void set_name(std::string name);//sets the name of the connection and sets it on server
	
private:
	SOCKET ConnectSocket;//socket that will be connected to server
	char recvbuf[512];//buffer that is updated by listening_thread()

	//used to make sure only one instance of Client class exists
	Client(){ };
	Client(Client const&){ };
	void operator=(Client const&){};

	//used to help get ip address
	void *get_in_addr(struct sockaddr *sa);
	
};


#endif
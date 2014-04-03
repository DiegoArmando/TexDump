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
	
	static Client* getInstance();
	int init();
	void listening_thread();
	void send_message(std::string message,std::string destination);
	std::vector<std::string> get_devices();
	void set_name(std::string name);
	std::string get_name();
private:
	SOCKET ConnectSocket;
	char recvbuf[512];
	Client(){ };
	Client(Client const&){ };
	void operator=(Client const&){};
	void *get_in_addr(struct sockaddr *sa);
	
};


#endif
#ifndef __CLIENT_SOCKET_INCLUDED__
#define __CLIENT_SOCKET_INCLUDED__


#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/socket.h>
#include <pthread.h>
#include "client_socket_container.h"

class client_socket_container;

class client_socket
{
    public:
        client_socket(char * client_ip, int socket,client_socket_container* container);
        ~client_socket();
        char* get_client_IP();
        int get_socket_number();
        std::string get_client_name();
        void set_client_name(std::string name);
        
        void * client_thread();
        
    private:
        char* client_IP;
        std::string client_name;
        int socket_number;
        
        client_socket_container* socket_container;
        
        void parseCommand(char * message);
};

#endif

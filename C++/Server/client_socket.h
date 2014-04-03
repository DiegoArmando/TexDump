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
        client_socket(char * client_ip, int socket,client_socket_container* container);//constructor
        ~client_socket();//destructor(called by itself)
        char* get_client_IP();//returns client's ip address
        int get_socket_number();//returns client's socket number
        std::string get_client_name();//returns client's name
        void set_client_name(std::string name);//sets client's name
        
        void * client_thread();//client's main thread. waits for received tcp data and calls parseCommand with the message
        
    private:
        char* client_IP;//example: "172.193.231.4"
        std::string client_name;//set to client_ip in constructor, can be changed by calling set_client_name
        int socket_number;//socket id given by OS 
        
        client_socket_container* socket_container;//Set in constructor, this enables client to perform operations on the container of clients
        
        void parseCommand(char * message);//when the client_socket thread receives new data this method parses the message and calls appropriate functions
};

#endif

#ifndef __MAIN_CONNECTION_INCLUDED__
#define __MAIN_CONNECTION_INCLUDED__

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include "client_socket.h"
#include "client_socket_container.h"

#define PORT "51723"  // the port users will be connecting to

#define NUMBEROFCONNECTIONS 1000

class main_connection
{
public:
    main_connection(client_socket_container* container);//Constructor
    int init();//Sets up bind connection to PORT and sets the port to listen for new connections.
    int wait_for_connections();//Called after init(). Accepts incoming connections, creates a client_socket for the connection, starts the connection's thread(through run_thread)
private:
    void * get_in_addr(struct sockaddr *sa);//used to get the IP address of a sockaddr object
    int sockfd;
    client_socket_container* container;//One instance, set in constructor
    static void * run_thread(void * args);//makes calling the client_socket's thread possible by passing the object into static reference
    

};

#endif

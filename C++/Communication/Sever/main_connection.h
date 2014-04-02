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
    main_connection(client_socket_container* container);
    int init();
    int wait_for_connections();
private:
    void * get_in_addr(struct sockaddr *sa);
    int sockfd;
    client_socket_container* container;
    static void * run_thread(void * args);
    

};

#endif

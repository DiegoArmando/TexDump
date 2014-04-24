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
#include <sys/time.h>
#include <mysql.h>
#include "client_socket.h"

#define PORT "51723"  // the port users will be connecting to

#define NUMBEROFCONNECTIONS 1000

class main_connection
{
public:
    main_connection();
    int init();//sets up connection
    int wait_for_connections();//accepts connections
    
private:
    void * get_in_addr(struct sockaddr *sa);
    int sockfd;
    MYSQL *connect;
    client_socket_container* container;
    
    static void * run_thread(void * args);//used to call a client_socket's thread function
    static void * messageSender(void * args);//checks outgoing message database every 10 seconds and sends messages to connected devices
    static std::string currentDateTime();//returns systems date and time
    

};

#endif

#include "main_connection.h"

void sigchld_handler(int s)//used to clean up dead processes
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}
//constructor
main_connection::main_connection(client_socket_container* socket_container)
{
    container = socket_container;
}
//Sets up bind connection to PORT and sets the port to listen for new connections.
int main_connection::init()
{
    struct addrinfo hints, *servinfo, *p;
    int rv,yes=1;
    struct sigaction sa;
    char s[INET6_ADDRSTRLEN];
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE; // use my IP
    if ((rv = getaddrinfo("0.0.0.0", PORT, &hints, &servinfo)) != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) 
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) 
        {
            perror("setsockopt");
            exit(1);
        }
        inet_ntop(p->ai_family,get_in_addr((struct sockaddr *)p->ai_addr),s, sizeof s);
        printf("Binded to ==> ");
        printf("%s",s);
        printf(":%d\n",ntohs(((struct sockaddr_in *)p->ai_addr)->sin_port));
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  
    {
        fprintf(stderr, "server: failed to bind\n");
        return 2;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, NUMBEROFCONNECTIONS) == -1) 
    {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) 
    {
        perror("sigaction");
        exit(1);
    }
}
//Called after init(). Accepts incoming connections, creates a client_socket for the connection, starts the connection's thread(through run_thread)
int main_connection::wait_for_connections()
{
    int new_fd;
    socklen_t sin_size;
    struct sockaddr_storage their_addr; // connector's address information
    char s[INET_ADDRSTRLEN];
    pthread_t thread;
    printf("server: waiting for connections...\n");
    char** paired = new char*[2];
    while(1) 
    {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }        
        inet_ntop(their_addr.ss_family,get_in_addr((struct sockaddr *)&their_addr),s, sizeof s);
        
        printf("server: got connection from %s with socket ID %d\n", s,new_fd);
        client_socket* new_connection = new client_socket(s,new_fd,container);
        pthread_create(&thread,NULL,&run_thread,new_connection); 
    }

    return 0;
}
//used to get the IP address of a sockaddr object
void * main_connection::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
//makes calling the client_socket's thread possible by passing the object into static reference
void * main_connection::run_thread(void * args)
{
    ((client_socket*)args)->client_thread();
}

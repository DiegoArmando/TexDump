#include "main_connection.h"

void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}
//constructor
main_connection::main_connection()
{
    /* Setup MYSQL connection */
    connect = mysql_init(NULL);

    if(!connect)
    {
        printf("INIT FAILED\n");
    }
    connect = mysql_real_connect(connect,"localhost","root","root","TEXDUMP",0,NULL,0);

    if(!connect)
    {
	 printf("Failed to connect to database: %s\n", mysql_error(connect));
    }
    std::string query("UPDATE computers SET connected=FALSE;");
    mysql_query(connect,query.c_str());
}
//creates a socket to bind to a port and accept all incoming sockets
int main_connection::init()
{
    struct addrinfo hints, *servinfo, *p;
    int rv,yes=1;
    struct sigaction sa;
    char s[INET6_ADDRSTRLEN];
    
    /* set information we know to be true */
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;//IP v4
    hints.ai_socktype = SOCK_STREAM;//two way communication stream
    hints.ai_protocol = IPPROTO_TCP;//TCP protocol
    hints.ai_flags = AI_PASSIVE;//bindable
    if ((rv = getaddrinfo("0.0.0.0", PORT, &hints, &servinfo)) != 0) //get network settings all posible connections with the information that we know to be true.
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
        //bind to socket
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

    //tell socket to listen
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
//this method accepts all incoming connections and creates a client_socket object to handle the connection
int main_connection::wait_for_connections()
{
    int new_fd;
    socklen_t sin_size;
    struct sockaddr_storage their_addr; // connector's address information
    char s[INET_ADDRSTRLEN];
    pthread_t thread;
    pthread_create(&thread,NULL,&messageSender,NULL); 
    printf("server: waiting for connections...\n");
    while(1) 
    {  // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }        
        //assigns a char* of the ip address to s 
        inet_ntop(their_addr.ss_family,get_in_addr((struct sockaddr *)&their_addr),s, sizeof s);
        
        printf("server: got connection from %s with socket ID %d\n", s,new_fd);
        client_socket* new_connection = new client_socket(s,new_fd);//create new client_socket
        pthread_create(&thread,NULL,&run_thread,new_connection); //start the client_socket's thread
    }

    return 0;
}
//this method is used to get the sockaddr_in found in a sockaddr
void * main_connection::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
//this method starts the client's thread
void * main_connection::run_thread(void * args)
{
    ((client_socket*)args)->client_thread();
}
//returns a string of the current date and time
std::string main_connection::currentDateTime() {
    std::time_t result = std::time(NULL);
    return std::asctime(std::localtime(&result));
}
//this method is started in a separate thread after init is complete. It handles outgoing messages
void * main_connection::messageSender(void * args)
{
    MYSQL *connect;
    MYSQL_RES *mess_result,*comp_result;
    MYSQL_ROW mess_row,send_comp_row,recv_comp_row;

    int query_state;
    
    connect = mysql_init(NULL);

    if(!connect)
    {
        printf("INIT FAILED\n");
        return NULL;
    }
    connect = mysql_real_connect(connect,"localhost","root","root","TEXDUMP",0,NULL,0);

    if(!connect)
    {
	 printf("Failed to connect to database: %s\n", mysql_error(connect));
     return NULL; 
    }   
    while(true)
    {
        mysql_query(connect,"select * from messages;");//get messages in database
        mess_result = mysql_store_result(connect);
        unsigned int numrows = mysql_num_rows(mess_result);//number of outgoing messages in database

        while((mess_row = mysql_fetch_row(mess_result)) != NULL)//loop through every message found in database
        {
            /*  Get sender info from database   */
            std::string query = "select * from computers where computer_id=";
            query+=mess_row[2];
            query+=";";
            printf("1)%s\n",query.c_str());
            mysql_query(connect,query.c_str());
            comp_result = mysql_store_result(connect);
            send_comp_row = mysql_fetch_row(comp_result);
            
            /*  Get destination info from database  */
            query = "select * from computers where computer_id=";
            query+=mess_row[3];
            query+=";";
            printf("2)%s\n",query.c_str());
            mysql_query(connect,query.c_str());
            comp_result = mysql_store_result(connect);
            recv_comp_row = mysql_fetch_row(comp_result);
            
            if(recv_comp_row[4][0] == '1')//if computer is currently logged in
            {
                printf("%s: SENDING MESSAGE FROM SENDER NAMED=%s with IP=%s TO COMPUTER NAMED=%s with IP=%s\n",currentDateTime().c_str(),send_comp_row[3],send_comp_row[2],recv_comp_row[3],recv_comp_row[2]);
                
                std::string out("MESSAGE:");
                out += send_comp_row[3];
                out += "%:%";
                out += mess_row[1];
                out += "%:%";
                out += mess_row[4];
                
                printf(" %s >> %s\n",recv_comp_row[5],out.c_str());
                //send message to computer
                send(atoi(recv_comp_row[5]),out.c_str(),out.length(),0);
                
                /*  Delete message from database after it is sent  */
                query = "DELETE FROM messages WHERE message_id=";
                query += mess_row[0];
                query +=";";
                mysql_query(connect,query.c_str());
                
            }
        }
        sleep(10);//wait 10 seconds
    }
    mysql_close(connect);
}

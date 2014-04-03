#include <iostream>
#include "main_connection.h"

client_socket_container* client_container = client_socket_container::Instance();//get a pointer to the one instance of client_socket_container
int main()
{
    main_connection* main = new main_connection(client_container);//create a main_connection
    main->init();//initialize the connection
    main->wait_for_connections();//wait and accept new connections
    
    return 0;
}


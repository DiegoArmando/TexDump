#include <iostream>
#include "main_connection.h"

client_socket_container* client_container = client_socket_container::Instance();
int main()
{
    main_connection* main = new main_connection(client_container);
    main->init();
    main->wait_for_connections();
    
    return 0;
}


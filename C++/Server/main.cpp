#include <iostream>
#include "main_connection.h"


int main()
{
    main_connection* main = new main_connection();
    main->init();
    main->wait_for_connections();
    
    return 0;
}


#ifndef __CLIENT_SOCKET_CONTAINER_INCLUDED__
#define __CLIENT_SOCKET_CONTAINER_INCLUDED__

#include "client_socket.h"
#include <vector>
#include <string.h>
class client_socket;

class client_socket_container
{
    public:
        static client_socket_container* Instance();
        
        void add_connection(client_socket* new_sock);
        void remove_connection(client_socket* remove_sock);
        std::string get_available_devices();
        client_socket* get_client(std::string client_name);
        
    private:
        client_socket_container(){};
        client_socket_container(client_socket_container const&){};
        client_socket_container& operator=(client_socket_container const&){};
        int get_connection_index(std::string client_name);
        static client_socket_container* one_instance;
        std::vector<client_socket*> connections;
        
};

#endif

#ifndef __CLIENT_SOCKET_CONTAINER_INCLUDED__
#define __CLIENT_SOCKET_CONTAINER_INCLUDED__

#include "client_socket.h"
#include <vector>
#include <string.h>
class client_socket;

class client_socket_container
{
    public:
        static client_socket_container* Instance();//returns the one instance of client_socket_container
        
        void add_connection(client_socket* new_sock);//adds a client socket to the container
        void remove_connection(client_socket* remove_sock);//removes a client socket from the container
        std::string get_available_devices();//returns a string of all devices in form: "device1,device2,device3,"
        client_socket* get_client(std::string client_name);//returns a pointer to a client_socket with the client_name
        
    private:
        //make sure only one instance of client_socket_container exists
        client_socket_container(){};
        client_socket_container(client_socket_container const&){};
        client_socket_container& operator=(client_socket_container const&){};
        
        int get_connection_index(std::string client_name);//returns the index in the container of the client_socket with the name equal to client_name
        static client_socket_container* one_instance;//used to make sure only one instance of client_socket_container exists
        std::vector<client_socket*> connections;//container of client_sockets
        
};

#endif

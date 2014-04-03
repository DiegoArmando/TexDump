#include "client_socket_container.h"
client_socket_container* client_socket_container::one_instance = NULL;

//returns the one instance of client_socket_container
client_socket_container* client_socket_container::Instance()
{
    if(!one_instance)
        one_instance = new client_socket_container;
    
    return one_instance;
}

//adds a client socket to the container
void client_socket_container::add_connection(client_socket* new_sock)
{
    connections.push_back(new_sock);
}

//removes a client socket from the container
void client_socket_container::remove_connection(client_socket* remove_sock)
{
    int position = get_connection_index(remove_sock->get_client_name());
    if(position>=0)
    {
        connections.erase(connections.begin()+ position );
        delete remove_sock;
    }
}

//returns a pointer to a client_socket with the client_name
client_socket* client_socket_container::get_client(std::string client_name)
{
    int position = get_connection_index(client_name);
    if(position>=0)
    {
        return connections[position];
    }
    return NULL;
}

//returns a string of all devices in form: "device1,device2,device3,"
std::string client_socket_container::get_available_devices()
{
    std::string list_of_clients = "";
    for(int i = 0;i<connections.size();i++)
    {
        list_of_clients+=connections[i]->get_client_name()+":";
    }
    return list_of_clients;
}

//returns the index in the container of the client_socket with the name equal to client_name
int client_socket_container::get_connection_index(std::string client_name)
{
    for(int i =0; i<connections.size();i++)
    {
        
        if(connections[i]->get_client_name().compare(client_name)==0)
            return i;
    }
    return -1;
}





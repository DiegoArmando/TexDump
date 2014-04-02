#include "client_socket_container.h"
client_socket_container* client_socket_container::one_instance = NULL;
client_socket_container* client_socket_container::Instance()
{
    if(!one_instance)
        one_instance = new client_socket_container;
    
    return one_instance;
}
void client_socket_container::add_connection(client_socket* new_sock)
{
    connections.push_back(new_sock);
}
void client_socket_container::remove_connection(client_socket* remove_sock)
{
    int position = get_connection_index(remove_sock->get_client_name());
    if(position>=0)
    {
        connections.erase(connections.begin()+ position );
        delete remove_sock;
    }
}
client_socket* client_socket_container::get_client(std::string client_name)
{
    int position = get_connection_index(client_name);
    if(position>=0)
    {
        return connections[position];
    }
    return NULL;
}
std::string client_socket_container::get_available_devices()
{
    std::string list_of_clients = "";
    for(int i = 0;i<connections.size();i++)
    {
        list_of_clients+=connections[i]->get_client_name()+":";
    }
    return list_of_clients;
}

int client_socket_container::get_connection_index(std::string client_name)
{
    for(int i =0; i<connections.size();i++)
    {
        
        if(connections[i]->get_client_name().compare(client_name)==0)
            return i;
    }
    return -1;
}





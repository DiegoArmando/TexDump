#include "client_socket.h"

client_socket::client_socket(char * IP_addr, int socket,client_socket_container* container)
{
    socket_number = socket;
    client_IP=new char[INET_ADDRSTRLEN];
    strcpy(client_IP,IP_addr);
    client_name = std::string(client_IP);
    socket_container = container;
    socket_container->add_connection(this);
}
client_socket::~client_socket()
{
    pthread_exit(NULL);
}
char* client_socket::get_client_IP()
{
    return client_IP;
}

int client_socket::get_socket_number()
{
    return socket_number;
}
std::string client_socket::get_client_name()
{
    return client_name;
}
void client_socket::set_client_name(std::string name)
{
    client_name = name;
}
void * client_socket::client_thread()
{
    int iResult;
    char recvbuf[512];
    while(1)
    {
        iResult = recv(socket_number,recvbuf,512,0);
        printf("Received text from %s - %s\n",client_IP,client_name.c_str());
        if(iResult>0)
        {
            parseCommand(recvbuf);
        }
        else
            break;
    }
    printf("Connection closed to %s - %s\n",client_IP,client_name.c_str());
    close(socket_number);
    socket_container->remove_connection(this);
    delete this;
    
}
void client_socket::parseCommand(char * message)
{
    std::string mess(message);
    int pos = mess.find(":");
    if(pos < 0)
    {
        printf("NO DELIMETER\n");
        return;
    }
    std::string command(mess.substr(0,pos));
    if(command.compare("GET_DEVICES")==0)
    {
        printf("GET_DEVICES: ");
        printf("'%s'\n",socket_container->get_available_devices().c_str());
    }
    else if(command.compare("SET_NAME")==0)
    {
        printf("SET_NAME: ");
        client_name = mess.substr(mess.find(":")+1);
        printf("'%s'\n",client_name.c_str());
    }
    else if(command.find("SEND_TO_")>=0)
    {
        std::string dest = command.substr(8);
        client_socket* destSocket = socket_container->get_client(dest);
        if(destSocket)
        {
            //printf("Destination specs: IP=%s,NAME=%s,ID=%d\n",destSocket->get_client_IP(),destSocket->get_client_name().c_str(),destSocket->get_socket_number());
            //send(destSocket->get_socket_number(),message.substr(command.length()),message.length()-command.length(),0)
        }
        else
        {
            printf("Device Name not valid\n");
        }
        
    }
    else
    {
        printf("ILLEGAL COMMAND\n");
    }
    
}

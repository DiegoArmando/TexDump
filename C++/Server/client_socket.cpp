#include "client_socket.h"
//constructor
client_socket::client_socket(char * IP_addr, int socket,client_socket_container* container)
{
    socket_number = socket;
    client_IP=new char[INET_ADDRSTRLEN];
    strcpy(client_IP,IP_addr);
    client_name = std::string(client_IP);
    socket_container = container;
    socket_container->add_connection(this);
}
//destructor(called by itself)
client_socket::~client_socket()
{
    pthread_exit(NULL);
}
//returns client's ip address
char* client_socket::get_client_IP()
{
    return client_IP;
}
//returns client's socket number
int client_socket::get_socket_number()
{
    return socket_number;
}
//returns client's name
std::string client_socket::get_client_name()
{
    return client_name;
}
//sets client's name
void client_socket::set_client_name(std::string name)
{
    client_name = name;
}
//client's main thread. waits for received tcp data and calls parseCommand with the message
void * client_socket::client_thread()
{
    int iResult;
    char recvbuf[512];
    while(1)
    {
        iResult = recv(socket_number,recvbuf,512,0);//wait for incoming data
        printf("Received text from ip=%s  name=%s\n",client_IP,client_name.c_str());
        if(iResult>0)//at close of connection iResult is 0
        {
            parseCommand(recvbuf);
            memset(recvbuf, 0, sizeof(recvbuf));//resets recvbuf
        }
        else
            break;
    }
    printf("Connection closed to ip=%s  name=%s\n",client_IP,client_name.c_str());
    close(socket_number);
    socket_container->remove_connection(this);
    delete this;
    
}
//when the client_socket thread receives new data this method parses the message and calls appropriate functions
void client_socket::parseCommand(char * message)
{
    std::string mess(message);
    int pos = mess.find(":");//':' is delimiter
    if(pos < 0)
    {
        printf("NO DELIMETER\n");
        return;
    }
    std::string command(mess.substr(0,pos));
    if(command.compare("GET_DEVICES")==0)
    {
        printf("GET_DEVICES: ");
        std::string output = socket_container->get_available_devices();
        output+="\0";
        printf("%s\n",output.c_str());
        send(socket_number,output.c_str(),output.length(),0);//sends back "device1,device2,device3,
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
        if(destSocket)//if a connection with the requested client_name exists
        {
            std::string output = client_name+":"+mess.substr(command.length()+1);//message format(<client name>:<message>)
            send(destSocket->get_socket_number(),output.c_str(),output.length(),0);//send message to destination device
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

#ifndef __CLIENT_SOCKET_INCLUDED__
#define __CLIENT_SOCKET_INCLUDED__

#include <string.h>
#include <stdio.h>
#include <ctime>
#include <mysql.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/socket.h>
#include <pthread.h>
#include <fstream>
#include <sstream>

class client_socket_container;

class client_socket
{
    public:
        client_socket(char * client_ip, int socket);
        ~client_socket();
        
        //thread that listens to client
        void * client_thread();
        
    private:
        std::string id;
        unsigned int socketID;
        char * clientIP;
        MYSQL *connect;
        
        void parseCommand(char * message);//calls appropriate methods based on received data
         
         
        /* Database query methods */
        
        std::string getComputerName();
        std::string getUsername();
        std::string getComputerID(std::string userID,std::string computerName);
        std::string getUserID();
        std::string getUserID(const char*username,const char*password);
        std::string getAvailableDevices();
       
        void newUser(const char * username,const char * password,const char*compName,const char*email);//adds a new user to database 
        void login(const char * username,const char * password,const char * compName);//logs in client
        void setComputerName(const char * name);//sets computers name of a logged in client 
        void sendToDestination(std::string destinationName, std::string message);//creates and adds a message to the message database
        
        std::string currentDateTime();//returns a string of the systems current date and time
};

#endif

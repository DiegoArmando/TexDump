#include "client_socket.h"

//constructor
client_socket::client_socket(char * IP_addr, int socket)
{
    /*   SET GLOBAL VARIABLES   */
    socketID = socket;
    clientIP=new char[INET_ADDRSTRLEN];
    strcpy(clientIP,IP_addr);
    id = "";
    
    /*   SETUP MYSQL CONNECTION   */
    connect = mysql_init(NULL);

    if(!connect)
    {
        printf("INIT FAILED\n");
    }
    connect = mysql_real_connect(connect,"localhost","root","root","TEXDUMP",0,NULL,0);

    if(!connect)
    {
	 printf("Failed to connect to database: %s\n", mysql_error(connect));
    }   
}
//destructor
client_socket::~client_socket()
{
    
    if(!id.empty())//if it is logged in
    {
        /*   UPDATE DATABASE TO SAY THE COMPUTER IS OFFLINE   */
        std::string query = "UPDATE computers SET connected=FALSE WHERE computer_id=";
        query+=id;
        query+=";";
        mysql_query(connect,query.c_str());
           
    }
    mysql_thread_end();//close mysql connection
    pthread_exit(NULL);//end clientThread
}
//Once a client is logged in this method returns the computers name saved in the database
std::string client_socket::getComputerName()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    //if not 0 query database and return computer name
    if(!id.empty())
    {
        std::string query = "SELECT computer_name FROM computers WHERE computer_id=";
        query+=id;
        query+=";";
        mysql_query(connect,query.c_str());
        result = mysql_store_result(connect);
        if(*mysql_error(connect)=='\0' && (row = mysql_fetch_row(result))!=NULL)//if query succeeds
        {
            return row[0];
        }       
    }
    return "";
}
//If the client is logged in this message returns the client user's username 
std::string client_socket::getUsername()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    //if not 0 query database and return username
    if(!id.empty())
    {
        std::string query = "select user_name from user_info where user_id=";
        query+=getUserID();
        query+=";";
        mysql_query(connect,query.c_str()); 
        result = mysql_store_result(connect);
        if(*mysql_error(connect)=='\0' && (row = mysql_fetch_row(result))!=NULL )//if query succeed
        {
            return row[0];
        }
    }
    return "";
}
//If client is logged in this method returns the user's ID number(not visible to user/only used in the server code)
std::string client_socket::getUserID()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    if(!id.empty())
    {
        std::string query = "select user_id from computers where computer_id=";
        query+=id;
        query+=";";
        mysql_query(connect,query.c_str());
        result = mysql_store_result(connect);
        if(*mysql_error(connect)=='\0' && (row = mysql_fetch_row(result)) != NULL)//if query succeeds
        {
            return row[0];
        }
    }
    return "";
}
//This method returns the userID given a username and password. Client does not need to be logged in to use this function as it is not user/computer specific
std::string client_socket::getUserID(const char * username, const char* password)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::ostringstream s;
    s << "select user_id from user_info where user_name='" << username << "' and password='"<<password<<"';";
    std::string query(s.str());
    mysql_query(connect,query.c_str());   
    result = mysql_store_result(connect);
    std::string userID;

    if(*mysql_error(connect)=='\0' && (row = mysql_fetch_row(result)) != NULL)
    {        
        userID = row[0];
        return userID;
    }
    return "";
}
//If the user is logged in this method creates a query to insert a message into the message table on the database
void client_socket::sendToDestination(std::string destinationName, std::string message)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    if(!id.empty())//if logged in
    {
        std::ostringstream s;
        s << "select computer_id from computers where user_id=" << getUserID() <<" and computer_name='"<<destinationName<<"';";
        std::string query(s.str());
        mysql_query(connect,query.c_str());
        result = mysql_store_result(connect);
        if(*mysql_error(connect)=='\0' && (row = mysql_fetch_row(result))!=NULL)//if query succeeds
        {
           std::ostringstream m;
           m << "INSERT INTO messages (timestamp,send_computer_id,recieve_computer_id,message) VALUES ('"<< currentDateTime() << "','"<<id<< "','"<<row[0]<< "','"<<message<< "');";
           std::string query2(m.str());
           mysql_query(connect,query2.c_str());
        }
    }
}
//If the client is logged in this method returns a string containing all user's device names seperated by a colon
std::string client_socket::getAvailableDevices()
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    std::string devices="";
    //query computer database for computerNames with username's id
    if(!id.empty())
    {
        /*gather devices*/
        std::ostringstream s;
        s << "select computer_name from computers where user_id=" << getUserID() <<";";
        std::string query(s.str());
        mysql_query(connect,query.c_str());
        result = mysql_store_result(connect);
        unsigned char i = 0;
        while((row = mysql_fetch_row(result)) != NULL)//for all devices registered to a user
        {
            devices+=row[0];
            devices+=":";
            i++;
        }
    }
    return devices;
}
//This method returns the device ID with a certain name registered to a specific user. Client does not need to be logged in 
std::string client_socket::getComputerID(std::string userID,std::string computerName)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::ostringstream s;
    s << "select computer_id from computers where user_id=" << userID << " and computer_name='"<<computerName<<"';";
    std::string query(s.str());
    mysql_query(connect,query.c_str());
    result = mysql_store_result(connect);
    if(*mysql_error(connect)=='\0' && (row = mysql_fetch_row(result))!=NULL)
    {
        return row[0];
    } 
    return "";
}
//If client is logged in this method updates the devices name in the database
void client_socket::setComputerName(const char * name)
{
    if(!id.empty())//computer is in database
    {  
        std::ostringstream s;
        s << "UPDATE computers SET computer_name='"<<name<<"' WHERE computer_id="<<id<<";";
        std::string query(s.str());
        mysql_query(connect,query.c_str());
    }
}
//this method is used to register a new user. It is called by parseCommand()
void client_socket::newUser(const char * username,const char * password, const char * compName, const char * email)
{
    MYSQL_RES *result;
    std::ostringstream s;
    std::string userID;
    
    s << "SELECT * FROM user_info WHERE user_name='"<<username<<"';";
    std::string query = s.str();
    mysql_query(connect,query.c_str());
    result = mysql_store_result(connect);
    unsigned int numrows = mysql_num_rows(result);
    s.str("");
    if(!numrows)//if user does not exist 
    {
        /*  create a new user  */
        s << "INSERT INTO user_info(user_name,password,email) VALUES ('"<< username << "','"<<password<< "','"<<email<<"');";
        std::string query2(s.str());
        mysql_query(connect,query2.c_str());
        userID = getUserID(username,password); 
    }
    else//send client an error message
    {
        std::string error = "ERROR:Username already exists";
        send(socketID,error.c_str(),error.length(),0);
        return;
    }
    /*Add a new computer to the database */ 
    s.str("");
    s << "INSERT INTO computers(user_id,ip_addr,computer_name,connected,socket_id) VALUES ("<< userID << ",'"<<clientIP<< "','"<<compName<< "',TRUE,"<<socketID<< ");";
    std::string query3(s.str());
    mysql_query(connect,query3.c_str());
    send(socketID,"LOGGED_IN:",10,0);
    id = getComputerID(userID,compName);//set global variable for computer_id
}
//this method is used to login a client. It is called by parseCommand()
void client_socket::login(const char * username,const char * password,const char * compName)
{
    std::string userID = getUserID(username, password);
    if(userID.empty())//if a user does not exist with given username and password
    {
        std::string error = "ERROR:No match for Username and Password";
        send(socketID,error.c_str(),error.length(),0);
        return;
    }
    printf("USER='%s',id='%s'\n",userID.c_str(),id.c_str());
    id = getComputerID(userID,compName);//try to set global variable for computer_id
    if(id.empty())//if computer not registered
    {  
        /* Register device */
        std::ostringstream s;
        s << "INSERT INTO computers(user_id,ip_addr,computer_name,connected,socket_id) VALUES ("<< userID << ",'"<<clientIP<< "','"<<compName<< "',TRUE,"<<socketID<< ");";
        std::string query(s.str());
        mysql_query(connect,query.c_str());
        id = getComputerID(userID,compName);//try to set global variable for computer_id again now that computer is registered
    }
    else//if computer is registered
    {
        /*  update device */
        std::ostringstream s;
        s << "UPDATE computers SET connected=TRUE, ip_addr='"<<clientIP<<"', socket_id='"<<socketID<< "' WHERE computer_id="<<id<<";";
        std::string query(s.str());
        mysql_query(connect,query.c_str());
    }
    send(socketID,"LOGGED_IN:",10,0);//tell client LOGIN was successful
}
//main thread that is called by main_connection
void * client_socket::client_thread()
{
    int iResult;
    char* recvbuf =new char[512];
    while(1)
    {
        memset(recvbuf, 0, sizeof(recvbuf));//clear buffer
        iResult = recv(socketID,recvbuf,512,0);//wait for input
        
        /*Log received message */
        std::ofstream log("log.txt",std::ios::app);
        log << currentDateTime()<<": Received text from ip="<<clientIP<<"  name='"<<getComputerName()<<"'\n   >> "<<recvbuf<<"\n";
        
        if(iResult>0)//if message contains text
        {
            parseCommand(recvbuf);
            
        }
        else//message of length 0 is sent during disconnection so it breaks loop 
            break;
        memset(recvbuf, 0, sizeof(recvbuf));//clear buffer
    }
    /* log that a disconnection occured */
    std::ofstream log("log.txt",std::ios::app);
    log << currentDateTime()<<": Connection closed from ip="<<clientIP<<"  name="<<getComputerName()<<"\n";
    close(socketID);
    delete this;//call destructor
    
}
//This method determines what to do with incoming message
//protocol for each command is next to if statements
//  -uppercase means it is explicitly required in this location
//  -lowercase means it is a description of what is needed in this location
//
//since this method is always running in the terminal. If something causes it to
//crash it is very beneficial to have print statements so the cause of the crash 
//can be quickly identified
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
    if(id.empty())//if not logged in
    {
        if(command.compare("LOGIN")==0)//lOGIN:username:password:computerName
        {
            int pos2 = mess.find(":",pos+1);
            int pos3 = mess.find(":",pos2+1);
            std::string username (mess.substr(pos+1,pos2-pos-1));
            std::string password (mess.substr(pos2+1,pos3-pos2-1));
            std::string computer_name (mess.substr(pos3+1));
            login(username.c_str(),password.c_str(),computer_name.c_str());
            printf("LOGIN Username='%s' Password='%s' Computer Name='%s' Comp_id='%s'\r\n",username.c_str(),password.c_str(),computer_name.c_str(),id.c_str());
            return;
        }
        else if(command.compare("REGISTER")==0)//REGISTER:username:password:computerName:email
        {
            printf("REGISTER---%s",mess.substr(pos+1).c_str());
            
            int pos2 = mess.find(":",pos+1);
            int pos3 = mess.find(":",pos2+1);
            int pos4 = mess.find(":",pos3+1);
            std::string username (mess.substr(pos+1,pos2-pos-1));
            std::string password (mess.substr(pos2+1,pos3-pos2-1));
            std::string computer_name (mess.substr(pos3+1,pos4-pos3-1));
            std::string email (mess.substr(pos4+1));
            newUser(username.c_str(),password.c_str(),computer_name.c_str(),email.c_str());
            printf("REGISTER Username='%s' Password='%s' Computer Name='%s' comp id='%s'\r\n",username.c_str(),password.c_str(),computer_name.c_str(),id.c_str());
            return;
        } 
        printf("ILLEGAL COMMAND before login Received from computer_id:%s\n",id.c_str());
    }
    else//if logged in
    {
        //only allow access to these functions if logged in
        if(command.compare("GET_DEVICES")==0)//GET_DEVICES:
        {
            printf("GET_DEVICES: ");
            std::string output=getAvailableDevices();
            output+="\0";
            printf("  >> %s\n",output.c_str());
            send(socketID,output.c_str(),output.length(),0);
            return;
        }
        else if(command.compare("SET_NAME")==0)//SET_NAME:newname
        {
            printf("SET_NAME: ");
            std::string newName (mess.substr(pos+1));
            setComputerName(newName.c_str());
            return;
        }
        else if(command.find("SEND_TO_")>=0)//SEND_TO_devicename:message
        {
            std::string dest = command.substr(8);
            sendToDestination(dest,mess.substr(pos+1));
            return;
        }
    }
    printf("ILLEGAL COMMAND Received from computer_id:%s\n",id.c_str());
    
}
//This method returns the current data and time of the system. 
std::string client_socket::currentDateTime() 
{
    std::time_t result = std::time(NULL);
    return std::asctime(std::localtime(&result));
}

Not commented yet but this is the layout of the files:

client_socket: 	
	- holds information regarding a socket
      	- contains thread method for listening to client connections
	- executes commands from client connections

client_socket_container: 
	- only one instance for application (Singleton)
	- holds all 'client_socket' objects 
	- add/remove client_socket to vector of client_sockets
	- contains lookup methods to search for client_sockets

main_connection:
	-initialize bind/listen connection
	-method to wait for new connections

main:
	-contains main method
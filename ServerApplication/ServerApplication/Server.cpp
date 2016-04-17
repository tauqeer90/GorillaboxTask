#include <iostream>
#include <winsock2.h>
#include "Server.h" 

using namespace std;
#define WRITE_BUFFER_SIZE 3000

Server::Server() {
	// port number to be used by the server.
	portNumber = 4001;
}

bool Server::initializeServer() {

	// Holds a structure containing Socket Information.
	WSADATA socketData;
 
	// Variable for specifying endpoints for socket connections.
	SOCKADDR_IN serverEndPoint, clientEndPoint;
 
	// Initializing the WinSock2 library for Windows creating sockets.
	WSAStartup(MAKEWORD(2,0), &socketData);

	// Initializing server Socket for IPv4 and TCP.
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	// Binding the server to the machine IP.
	serverEndPoint.sin_addr.s_addr = INADDR_ANY;
	serverEndPoint.sin_family = AF_INET;
	serverEndPoint.sin_port = htons(portNumber);

	// Declaring Client Socket.
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
 
	// Associates local address with the socket.
	bind(serverSocket, (SOCKADDR *)&serverEndPoint, sizeof(serverEndPoint));

	// Setting up the server to listen to the socket.
	listen(serverSocket, 0);
	cout << "waiting for client connect" << endl;

	// Connecting with the client
	int clientAddrSize = sizeof(clientEndPoint);

	if((clientSocket = accept(serverSocket, (SOCKADDR *)&clientEndPoint, &clientAddrSize)) != INVALID_SOCKET) {
		cout << "Client connected" << endl;
		
		// Receiving file path from client.
		char filePath[1024];
		recv(clientSocket, filePath, sizeof(filePath), 0);
		FILE *file = fopen(filePath,"rb");
        
		//memset(buffer, 0, sizeof(buffer));
 
		// If file could not be opened, return false.
		if(file==NULL) {
			cout << "File could not be opened." << endl;
			return false;
		}

		char writeBuffer[WRITE_BUFFER_SIZE]={0};

		// Iterating through the file content.
		while(1) {
			
			// Reading the file and sending over the TCP connection.
			int bytesRead = fread(writeBuffer, 1, WRITE_BUFFER_SIZE, file);
			if(bytesRead > 0) {
				send(clientSocket, writeBuffer, bytesRead, 0);
			}

			// If bytes read is lesser than the Buffer Size.
			if (bytesRead < WRITE_BUFFER_SIZE)
			{
				// End of file reached.
				if (feof(file)) {
					cout << "File reading completed." << endl;
					return true;
				}
                
				// Error while reading file.
				if (ferror(file)) {
					cout << "Error while reading file." << endl;
					return false;;
				}
			}

			// Clearing the buffer.
			memset(writeBuffer, 0, sizeof(WRITE_BUFFER_SIZE));
		}

		closesocket(clientSocket);
		cout << "Client disconnected." << endl;

	} else {
		cout << "Failed to connect with client." << endl;
		return false;
	}

	cout << "File transfered to client." << endl;
	return true;
}
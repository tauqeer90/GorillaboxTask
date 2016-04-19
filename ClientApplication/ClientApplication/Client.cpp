#include <iostream>
#include <winsock2.h>
#include "Client.h" 
#include <string>
 
using namespace std;
#define READ_BUFFER_SIZE 524288

bool Client::startClient(string ipAddress, int portNumber, string filePath) {
	// Path where the file will be downloaded.
	cout<< "Enter local directory where the file is to be downloaded (Format: drive_name:\\foldername\\ ): ";
	string download_file_path;
	cin >> download_file_path;
	download_file_path += (getFileName(filePath));

	// ip address to be used by the server (local host).
	char ipChar[sizeof(ipAddress)];
	strcpy(ipChar, ipAddress.c_str());

	// Holds a structure containing Socket Information.
	WSADATA socketData;

	// Variable for specifying endpoints for socket connections.
    SOCKADDR_IN clientEndPoint;

	// Initializing the WinSock2 library for Windows creating sockets.
    WSAStartup(MAKEWORD(2,0), &socketData);

	// Initializing server Socket for IPv4 and TCP.
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
 
	// Binding the client to the server IP.
    clientEndPoint.sin_addr.s_addr = inet_addr(ipChar); 
    clientEndPoint.sin_family = AF_INET;
    clientEndPoint.sin_port = htons(portNumber);
 
	// Connecting with the server.
	connect(serverSocket, (SOCKADDR *)&clientEndPoint, sizeof(clientEndPoint));

	// Sending the file path to the server.
	char buffer[sizeof(filePath)];
	strcpy(buffer, filePath.c_str());
	send(serverSocket, buffer, sizeof(buffer), 0);

	// Creating the downloaded file.
    FILE *downloaded_file = fopen(download_file_path.c_str(), "ab");

	// Buffering the bytes from tcp connection and writing in file.
	int bytesReceived = 0;
    char readBuffer[READ_BUFFER_SIZE];
    memset(readBuffer, '0', sizeof(READ_BUFFER_SIZE));

    while((bytesReceived = recv(serverSocket, readBuffer, sizeof(readBuffer), 0)) > 0) {
        printf("Bytes received %d\n",bytesReceived);
        fwrite(readBuffer, 1, bytesReceived, downloaded_file);
		memset(readBuffer, '0', sizeof(READ_BUFFER_SIZE));
    }

	// If while while reading bytes from tcp connection.
	if(bytesReceived < 0) {
		cout << "Error while receiving file." << endl;
        return false;
    }

	closesocket(serverSocket);
	WSACleanup();
	cout << "Socket closed." << endl << endl;
	
	return true;
}

string Client::getFileName(string filePath) {
	char separator = '\\';
	size_t i = filePath.rfind(separator, filePath.length());
	string fileName;
	if (i != string::npos) {
		fileName = (filePath.substr(i+1, filePath.length() - i));
	}
	return fileName;
}


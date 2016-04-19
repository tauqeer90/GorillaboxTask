#include <iostream>
#include <winsock2.h> 
#include "Client.h"  
#include <string>

using namespace std;
 
int main(int argc,char *argv[]) {

	// IP address of the server.
	string ipAaddress;
	// Port Number of the server.
	int portNumber;
	// File path on the server from where the file is to be downloaded.
	string filePath;

	if(argc == 3) {

		ipAaddress = argv[0];
		portNumber = (int) argv[1];
		filePath = argv[2];

	} else {
		cout<< "Enter IP address (Server at local host): ";
		cin >> ipAaddress;

		cout<< "Enter port number (Server Port Num: 4001): ";
		cin >> (int) portNumber;

		cout<< "Enter file path of the server (Format: drive_name:\\foldername\\filename ): ";
		cin >> filePath;
	}

	Client client;
	client.startClient(ipAaddress , portNumber, filePath);
}
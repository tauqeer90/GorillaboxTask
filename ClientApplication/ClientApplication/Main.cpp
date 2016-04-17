#include <iostream>
#include <winsock2.h> 
#include "Client.h"  

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
		cout<< "Input Arguments less than 3, so hardcoding the arguments." <<endl;
		ipAaddress = "127.0.0.1";
		portNumber = 4001;
		filePath = "E:\\abc.jpg";
	}

	Client client;
	client.startClient("127.0.0.1" , 4001, "E:\\abc.jpg");
}
#ifndef CLIENT_H
#define CLIENT_H
 
using namespace std;

class Client {
public:
	bool startClient(string ip, int port, string filePath);

private:
	string getFileName(string filePath);
};

#endif
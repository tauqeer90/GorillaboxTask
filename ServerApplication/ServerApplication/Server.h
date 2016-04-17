#ifndef SERVER_H
#define SERVER_H

using namespace std;

class Server {
public:
	Server();
	bool initializeServer();

private:
	int portNumber;
};

#endif
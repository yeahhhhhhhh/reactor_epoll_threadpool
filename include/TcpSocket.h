#ifndef __TCPSOCKET__
#define __TCPSOCKET__

#include <iostream>
#include "Socket.h"

using namespace std;

class TcpSocket : public Socket
{
public:
    int connfd_;
public:
    // TcpSocket(/* args */){};
    // ~TcpSocket(){};
	
	void init(const char *ip, int port);
	void listen();
    int getConnfd();
};


#endif // __TCPSOCKET__

// #include <sys/types.h>
// #include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>

#include "TcpSocket.h"

int TcpSocket::getConnfd(){
    return connfd_;
}

void TcpSocket::init(const char *ip, int port){
	Socket::init(ip, port, SOCK_STREAM);
}

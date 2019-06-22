#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include "TcpServerSocket.h"

TcpServerSocket::TcpServerSocket(){}
TcpServerSocket::~TcpServerSocket(){
//	if(this != NULL){
//		delete this;
//	}	
}

int TcpServerSocket::start(){
    connfd_ = accept(sockfd_, NULL, NULL);
    if(connfd_ < 0){
        cout << "accept error." << endl;
        cout << "errno = " << errno << endl;
        exit(EXIT_FAILURE);
    }
    return connfd_;
}

void TcpServerSocket::listen(){
	TEST_NZ(::listen(sockfd_, 20));
}

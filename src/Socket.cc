#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "Socket.h"

Socket::Socket(){}
Socket::~Socket(){}

void Socket::init(const char *ip, int port, int type){
    sockfd_ = socket(AF_INET, type, 0);
    
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
	if(ip == NULL || ip == ""){	
        addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
	}else{
	 	addr.sin_addr.s_addr = inet_addr(ip);
	}
    
    unsigned value = 1;
    setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

    TEST_NZ(bind(sockfd_, (struct sockaddr*)&addr, sizeof(struct sockaddr)));

    if(port == 0){
        struct sockaddr_in addr2;
        socklen_t len = sizeof(struct sockaddr);
        TEST_NZ(getsockname(sockfd_, (struct sockaddr*)&addr2, &len));
        port_ = ntohs(addr2.sin_port);
    }else{
        port_ = port;
    }
}

int Socket::getSockfd(){
    return sockfd_;
}

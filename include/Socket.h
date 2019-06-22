#ifndef __SOCKET__
#define __SOCKET__

#include <stdlib.h>

#include "Utils.h"

#define TEST_NZ(x) do{ if((x)) Utils::die("" #x ""); }while(0)
#define TEST_Z(x) do{ if(!(x)) Utils::die("" #x ""); }while(0)

class Socket
{
public:
    int sockfd_;
    int connfd_;
    int port_;
    char *ip_;
public:
    Socket();
    ~Socket();

    void init(const char *ip, int port, int type);
    int getSockfd();
};


#endif // __SOCKET__

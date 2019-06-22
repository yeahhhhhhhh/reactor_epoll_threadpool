#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "Utils.h"

using namespace std;

void Utils::die(const char *msg){
    cout << "error:" << msg << endl;
}

int Utils::send(int fd, char *buf, size_t len){
    int ret;
    ret = ::write(fd, buf, len);
    if(ret < 0){
        cout << "send error." << endl;
        exit(EXIT_FAILURE);
    }else if(ret != len){
        cout << "not send all ." << endl;
        exit(EXIT_FAILURE);
    }else{
        return ret;
    }
}
int Utils::recv(int fd, char *buf, size_t len){
    int ret;
    ret = ::read(fd, buf, len);
    if(ret < 0){
        cout << "recv error." << endl;
        exit(EXIT_FAILURE);
    }
    return ret;
}

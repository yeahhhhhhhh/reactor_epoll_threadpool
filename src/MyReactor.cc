#include <iostream>
#include <string.h>
#include <unistd.h>

#include "MyReactor.h"
#include "TcpServerSocket.h"
#include "MyHandler.h"

using namespace std;

MyReactor::MyReactor(){}
MyReactor::~MyReactor(){}

void MyReactor::handleEvent(void *arg){
	TcpServerSocket server = *(TcpServerSocket*)arg;
	int ret;
	int n;
	while(1){
		ret = me->wait();
		for(int i = 0; i < ret; i++){
			if(me->events_[i].data.fd == server.sockfd_){
				server.start();
				
				MyHandler *mh = new MyHandler();
				mh->mr_ = this;
				mh->eventfd_ = me->events[i].data.fd;
//				me->events[i].data.ptr = mh;
				
				me->addEvent(server.connfd_, mh);
			}else if(me->events[i].events & EPOLLIN){
				MyHandler *mh = (MyHandler*)(me->events[i].data.ptr);
				pool_->addTask(handleRead_, mh);
			}else if(me->events[i].events & EPOLLOUT){
				MyHandler *mh = (MyHandler*)(me->events[i].data.ptr);
				pool_->addTask(handleWrite_, mh);
			}
		}
	}
}

void MyReactor::registReadEvent(void *(*handleRead)(void *), void *arg){
	handleRead_ = handleRead;
	argR_ = arg;
}

void MyReactor::registWriteEvent(void *(*handleWrite)(void *), void *arg){
	handleWrite_ = handleWrite;
	argW_ = arg;
}



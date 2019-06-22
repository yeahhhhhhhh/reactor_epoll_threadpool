#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <iostream>
#include <errno.h>
#include <string.h>

#include "MyEpoll.h"

using namespace std;

MyEpoll::MyEpoll(){}
MyEpoll::~MyEpoll(){}

int MyEpoll::create(int size){
	memset(events_, 0, sizeof(events_));
	int ret;
	ret = epoll_create1(size);
	if(ret < 0){
		cout << "epoll_create error." << endl;
		exit(EXIT_FAILURE);
	}
	epfd_ = ret;
	return ret;
}
int MyEpoll::addEvent(int eventFd, void *arg){
	struct epoll_event *ev = new epoll_event;
//	ev.data.fd = eventFd;
	ev->data.ptr = arg;
	ev->events = EPOLLIN | EPOLLET;
	int ret;
	ret = epoll_ctl(epfd_, EPOLL_CTL_ADD, eventFd, ev);
	if(ret < 0){
		cout << "epoll_ctl error." << endl;
		exit(EXIT_FAILURE);
	}
	return ret; // 0
}

int MyEpoll::modifyEvent(int eventFd, void *arg){
	struct epoll_event ev;
//	ev.data.fd = eventFd;
	ev.data.ptr = arg;
	ev.events = EPOLLOUT | EPOLLET;
	int ret;
	ret = epoll_ctl(epfd_, EPOLL_CTL_MOD, eventFd, &ev);
	if(ret < 0){
		cout << "epoll_ctl error." << endl;
		exit(EXIT_FAILURE);
	}
	return ret; // 0
}

int MyEpoll::modifyEvent2(int eventFd, void *arg){
	struct epoll_event ev;
//	ev.data.fd = eventFd;
	ev.data.ptr = arg;
	ev.events = EPOLLIN | EPOLLET;
	int ret;
	ret = epoll_ctl(epfd_, EPOLL_CTL_MOD, eventFd, &ev);
	if(ret < 0){
		cout << "epoll_ctl error." << endl;
		exit(EXIT_FAILURE);
	}
	return ret; // 0
}

int MyEpoll::deleteEvent(int eventFd){
	int ret;
	ret = epoll_ctl(epfd_, EPOLL_CTL_DEL, eventFd, NULL);
	if(ret < 0){
		cout << "epoll_ctl error." << endl;
		exit(EXIT_FAILURE);
	}
	return ret; // 0
}
	

int MyEpoll::wait(){
	int ret;
	ret = epoll_wait(epfd_, events_, 20, -1);
	
	if(ret < 0){
		cout << "errno = " << errno << endl;
		cout << "epoll_wait error." << endl;
		exit(EXIT_FAILURE);
	}
	return ret;
}

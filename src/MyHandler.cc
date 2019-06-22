#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "MyHandler.h"

using namespace std;

MyHandler::MyHandler(){
	recvBuf_ = new char[1024];
	sendBuf_ = new char[1024];
}
MyHandler::~MyHandler(){}

void* MyHandler::handleRead(void *arg){
	MyHandler *mh = (MyHandler*)arg;
	int ret;
	memset(mh->recvBuf_, 0, sizeof(mh->recvBuf_));
	ret = read(mh->eventfd_, mh->recvBuf_, 1024);
	if(ret < 0){
		cout << "read error." << endl;
		mh->me_->deleteEvent(mh->eventfd_);
		close(mh->eventfd_);
		return NULL;
	}else if(ret == 0){
		cout << "read over." << endl;
		mh->me_->deleteEvent(mh->eventfd_);
		close(mh->eventfd_);
		return NULL;
	}
	memset(mh->sendBuf_, 0, sizeof(mh->sendBuf_));
	strcpy(mh->sendBuf_, mh->recvBuf_);
	cout << "*thread " << pthread_self() << " recv: " << mh->recvBuf_ << endl;
	mh->me_->modifyEvent(mh->eventfd_, mh);
}
void* MyHandler::handleWrite(void *arg){
	MyHandler *mh = (MyHandler*)arg;
	int ret;
	ret = write(mh->eventfd_, mh->sendBuf_, strlen(mh->sendBuf_));
	if(ret < 0){
		cout << "write error." << endl;
		mh->me_->deleteEvent(mh->eventfd_);
		close(mh->eventfd_);
		return NULL;
	}
	memset(mh->sendBuf_, 0, sizeof(mh->sendBuf_));
	mh->me_->modifyEvent2(mh->eventfd_, mh);
}

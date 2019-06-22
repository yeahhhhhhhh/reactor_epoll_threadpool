#include <unistd.h>
#include <errno.h>

#include "MyLoop.h"
#include "TcpServerSocket.h"
#include "MyHandler.h"

MyLoop::MyLoop(){}
MyLoop::MyLoop(MyEpoll *me, MyThreadPool *pool){
	me_ = me;
	pool_ = pool;
}
MyLoop::~MyLoop(){}

void MyLoop::loop(void *arg){
	TcpServerSocket *server = (TcpServerSocket*)arg;
	int ret;
	while(1){
		ret = me_->wait();
		for(int i = 0; i < ret; i++){
			if(*(int*)(me_->events_[i].data.ptr) == server->sockfd_){
				server->start();
				cout << "server->start();" << endl;
				MyHandler *mh = new MyHandler();
				mh->eventfd_ = server->connfd_;
				mh->me_ = me_;
				me_->addEvent(server->connfd_, mh);
			}else if(me_->events_[i].events & EPOLLIN){
				MyHandler *mh = (MyHandler*)(me_->events_[i].data.ptr);
				pool_->addTask(mh->handleRead, mh);
			}else if(me_->events_[i].events & EPOLLOUT){
				MyHandler *mh = (MyHandler*)(me_->events_[i].data.ptr);
				pool_->addTask(mh->handleWrite, mh);
			}
		}
	}
}

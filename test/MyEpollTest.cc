#define BOOST_TEST_MODULE myEpollTest
#include "Test.h"

#include <iostream>
#include <string.h>

#include "MyEpoll.h"
#include "TcpServerSocket.h"
#include "MyHandler.h"
#include "MyThreadPool.h"
#include "MyLoop.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(test)

BOOST_AUTO_TEST_CASE(t1){
	MyEpoll *me = new MyEpoll();
	me->create(0);
	
	TcpServerSocket *server = new TcpServerSocket();
	server->init("127.0.0.1", 9998);
	server->listen();
	
	me->addEvent(server->sockfd_, &(server->sockfd_));
	
	MyThreadPool *pool = new  MyThreadPool();
	pool->init(3);
	
	MyLoop *loop = new MyLoop(me, pool);
	loop->loop(server);
}

BOOST_AUTO_TEST_SUITE_END()

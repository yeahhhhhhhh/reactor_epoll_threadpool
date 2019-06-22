#ifndef __MYHANDLER__
#define __MYHANDLER__

#include "MyEpoll.h"

class MyHandler {
    public:
	  int eventfd_;
	  MyEpoll *me_;
	  char *recvBuf_;
	  char *sendBuf_;
	  
    public:
	  MyHandler ();
	  virtual ~MyHandler ();
	 
	public:
	  static void* handleRead(void *arg);
	  static void* handleWrite(void *arg);
	  
};

#endif // __MYHANDLER__

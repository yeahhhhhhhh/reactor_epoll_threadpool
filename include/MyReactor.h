#ifndef __MYREACTOR__
#define __MYREACTOR__

#include "MyThreadPool.h"
#include "MyEpoll.h"

class MyReactor {
    public:
	  MyThreadPool *pool_;
	  MyEpoll *me;
	  void *(*handleRead_)(void *);
	  void *(*handleWrite_)(void *);
	  void *argR_;
	  void *argW_;
	  
    public:
	  MyReactor ();
	  virtual ~MyReactor ();
	 
	public:
	  void handleEvent(void *arg);
	  void registReadEvent(void *(*handleRead)(void *arg), void *arg);
	  void registWriteEvent(void *(*handleWrite)(void *arg), void *arg);
	  
};

#endif // __MYREACTOR__

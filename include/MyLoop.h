#ifndef __MYLOOP__
#define __MYLOOP__

#include "MyEpoll.h"
#include "MyThreadPool.h"

class MyLoop {
    public:
	  MyEpoll *me_;
	  MyThreadPool *pool_;
	  
    public:
	  MyLoop ();
	  MyLoop (MyEpoll *me, MyThreadPool *pool);
	  virtual ~MyLoop ();
	 
	public:
	  void loop(void *arg);
	  
};

#endif // __MYLOOP__

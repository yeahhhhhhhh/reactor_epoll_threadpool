#ifndef __MYCONDITION__
#define __MYCONDITION__

#include <pthread.h>

class MyCondition {
    public:
	  static pthread_mutex_t *pMutex_;
	  static pthread_cond_t *pCond_;
	  
    public:
	  MyCondition ();
	  virtual ~MyCondition ();
	 
	public:
	  static int init(MyCondition *cond);
	  static int lock(MyCondition *cond);
	  static int unlock(MyCondition *cond);
	  static int wait(MyCondition *cond);
	  static int signal(MyCondition *cond);
	  static int broadcast(MyCondition *cond);
	  static int destroy(MyCondition *cond);
};

#endif // __MYCONDITION__

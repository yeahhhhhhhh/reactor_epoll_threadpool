#ifndef __MYTHREAD__
#define __MYTHREAD__

class MyThread {
    public:
	  pthread_t pid_;
	  void *(*func_)(void*);
	  void *p_;
	  
    public:
	  MyThread ();
	  virtual ~MyThread ();
	 
	public:
	  int run();
	  int join();
	  
};

#endif // __MYTHREAD__

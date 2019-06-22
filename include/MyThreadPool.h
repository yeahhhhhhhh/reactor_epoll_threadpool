#ifndef __MYTHREADPOOL__
#define __MYTHREADPOOL__

#include "MyCondition.h"
#include "MyThread.h"

typedef struct Task{
	void *(*run)(void *args);
	void *arg;
	struct Task *next;
}Task;

class MyThreadPool {
    public:
	  static MyCondition *cond_; 
	  static Task *firstTask_; 
	  static Task *lastTask_;
	  static int threadCount_; // 现有的线程数量
	  static int idleThreadCount_; // 空闲的线程数量
	  static int maxThreadCount_; // 最大的线程数量
	  static int isQuit_; // 是否销毁线程
	  
    public:
	  MyThreadPool ();
	  virtual ~MyThreadPool ();
	 
	public:
	  void init(int maxThreadCount);
	  void addTask(void *(*run)(void *arg), void *arg);
	  void destroy();
	  static void* routine(void *arg);
	  
};

#endif // __MYTHREADPOOL__

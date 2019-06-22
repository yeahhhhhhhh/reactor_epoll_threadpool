#ifndef __MYEPOLL__
#define __MYEPOLL__

#include <sys/epoll.h>

class MyEpoll {
    public:
	  int epfd_;
	  struct epoll_event events_[20];
	  
    public:
	  MyEpoll ();
	  virtual ~MyEpoll ();
	 
	public:
	  int create(int size);
	  int addEvent(int eventFd, void *arg);
	  int modifyEvent(int eventFd, void *arg);
	  int modifyEvent2(int eventFd, void *arg);
	  int deleteEvent(int eventFd);
	  int wait();
	  
};

#endif // __MYEPOLL__

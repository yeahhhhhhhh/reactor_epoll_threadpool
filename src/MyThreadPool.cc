#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "MyThreadPool.h"
#include "MyCondition.h"
#include "MyThread.h"

using namespace std;

MyCondition* MyThreadPool::cond_ = new MyCondition();
Task* MyThreadPool::firstTask_ = NULL;
Task* MyThreadPool::lastTask_ = NULL;
int MyThreadPool::threadCount_ = 0; // 现有的线程数量
int MyThreadPool::idleThreadCount_ = 0; // 空闲的线程数量
int MyThreadPool::maxThreadCount_ = 3; // 最大的线程数量
int MyThreadPool::isQuit_ = 0; // 是否销毁线程

MyThreadPool::MyThreadPool(){}
MyThreadPool::~MyThreadPool(){}

void MyThreadPool::init(int maxThreadCount){
	MyCondition::init(cond_);
	if(maxThreadCount <= 0){
		return;
	}
	maxThreadCount_ = maxThreadCount; // 最大的线程数量
}
void MyThreadPool::addTask(void *(*run)(void *arg), void *arg){
	Task *newTask = new Task;
	newTask->run = run;
	newTask->arg = arg;
	newTask->next = NULL;
	
	MyCondition::lock(cond_);
	
	if(firstTask_ == NULL){
		firstTask_ = newTask;
	}else{
		lastTask_->next = newTask;
	}
	lastTask_ = newTask;
	
	if(idleThreadCount_ > 0){
		MyCondition::signal(cond_);
	}else if(threadCount_ < maxThreadCount_){
		MyThread *t = new MyThread();
		t->func_ = routine;
		t->run();
		threadCount_++;
	}
	MyCondition::unlock(cond_);
}
void MyThreadPool::destroy(){
	if(isQuit_ == 1){
		return;
	}
	MyCondition::lock(cond_);
	isQuit_ = 1;
	if(threadCount_ > 0){
		if(idleThreadCount_ > 0){
			MyCondition::signal(cond_);
		}
		while(threadCount_ != 0){
			MyCondition::wait(cond_);
		}
	}
	MyCondition::unlock(cond_);
	MyCondition::destroy(cond_);
}
void* MyThreadPool::routine(void *arg){
	cout << "thread " << pthread_self() << " is running" << endl;
	while(1){
		MyCondition::lock(cond_);
		idleThreadCount_++;
		while(firstTask_ == NULL && isQuit_ == 0){
			cout << "thread " << pthread_self() << " is waiting" << endl;
			MyCondition::wait(cond_);
		}
		if(firstTask_ != NULL){
			idleThreadCount_--;
			Task *task = firstTask_;
			firstTask_ = firstTask_->next;
			MyCondition::unlock(cond_);
			task->run(task->arg);
			free(task);
			MyCondition::lock(cond_);
		}
		if(firstTask_ == NULL && isQuit_ == 1){
			threadCount_--;
			if(threadCount_ == 0){
				MyCondition::signal(cond_);
			}
			MyCondition::unlock(cond_);
			break;
		}
		MyCondition::unlock(cond_);
	}
	cout << "thread " << pthread_self() << " is exiting" << endl;
	return NULL;
}





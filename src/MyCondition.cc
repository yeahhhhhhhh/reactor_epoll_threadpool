#include <stdlib.h>

#include "MyCondition.h"

pthread_mutex_t* MyCondition::pMutex_ = NULL;
pthread_cond_t* MyCondition::pCond_ = NULL;

MyCondition::MyCondition(){}
MyCondition::~MyCondition(){}

int MyCondition::init(MyCondition *cond){
	cond->pMutex_ = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	cond->pCond_ = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
	int ret;
	if((ret = pthread_mutex_init(cond->pMutex_, NULL))){
		return ret;
	}
	if((ret = pthread_cond_init(cond->pCond_, NULL))){
		return ret;
	}
	return 0;
}
int MyCondition::lock(MyCondition *cond){
	return pthread_mutex_lock(cond->pMutex_);
}
int MyCondition::unlock(MyCondition *cond){
	return pthread_mutex_unlock(cond->pMutex_);
}
int MyCondition::wait(MyCondition *cond){
	return pthread_cond_wait(cond->pCond_, cond->pMutex_);
}
int MyCondition::signal(MyCondition *cond){
	return pthread_cond_signal(cond->pCond_);
}
int MyCondition::broadcast(MyCondition *cond){
	return pthread_cond_signal(cond->pCond_);
}
int MyCondition::destroy(MyCondition *cond){
	int ret;
	if((ret = pthread_mutex_destroy(cond->pMutex_))){
		return ret;
	}
	if((ret = pthread_cond_destroy(cond->pCond_))){
		return ret;
	}
	return 0;
}

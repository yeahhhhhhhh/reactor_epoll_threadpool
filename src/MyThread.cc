#include <pthread.h>
#include <iostream>

#include "MyThread.h"

using namespace std;

MyThread::MyThread(){}
MyThread::~MyThread(){}

int MyThread::run(){
	return pthread_create(&pid_, NULL, func_, p_);
}

int MyThread::join(){
	cout << "pid = " << pid_ << endl;
	return pthread_join(pid_, NULL);
}

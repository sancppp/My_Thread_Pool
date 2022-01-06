#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_
#include <thread>
#include <mutex>
#include <mutex>
#include <pthread.h>
#include "TaskQueue.h"

class ThreadPool
{
private:
    TaskQueue* TaskQ;
    pthread_t *workers; //消费者线程
    pthread_t m_manager;  //管理者线程
    pthread_mutex_t mutexpool;
    pthread_cond_t notEmpty;
    int minNum;
    int maxNum;
    int busyNum;
    int liveNum;
    int exitNum;
    bool shutdown;
public:
    ThreadPool(int _min,int _max);
    ~ThreadPool();

    void addTask(Task task);//加任务
    inline int getBusyNum();
    inline int getAliveNum();

private:
    void * worker(void * arg);//消费者线程任务函数
    void * manager(void * arg);//管理者

};

#endif
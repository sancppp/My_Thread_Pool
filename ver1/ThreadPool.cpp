#include "ThreadPool.h"
#include "TaskQueue.h"
#include <iostream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
ThreadPool::ThreadPool(int _min, int _max)
{
    //可以添加创建失败的后续处理  dowhile
    TaskQ = new TaskQueue;
    minNum = _min;
    maxNum = _max;
    busyNum = 0;
    liveNum = _min;
    //初始化线程
    workersID = new pthread_t[maxNum];
    memset(workersID, 0, sizeof(pthread_t) * maxNum);
    //初始化锁
    pthread_mutex_init(&mutexpool, NULL);
    pthread_cond_init(&notEmpty, NULL);
    for (int i = 0; i < minNum; i++)
    {
        pthread_create(&workersID[i], NULL, worker, this);
        cout << "创建子线程, ID: " << to_string(workersID[i]) << endl;
    }
    // 创建管理者线程, 1个
    pthread_create(&managerID, NULL, manager, this);
}

ThreadPool::~ThreadPool()
{
    shutdown = true;
    pthread_join(managerID, NULL);
    for (int i = 0; i < liveNum; i++)
    {
        pthread_cond_signal(&notEmpty);
    }
    if (TaskQ)
        delete TaskQ;
    if (workersID)
        delete[] workersID;
    pthread_mutex_destroy(&mutexpool);
    pthread_cond_destroy(&notEmpty);
}

void ThreadPool::addTask(Task task)
{
    if (shutdown)
        return;
    //里层已经加锁了，外层不能加锁，死锁的条件之一
    TaskQ->addTask(task);
    pthread_cond_signal(&notEmpty);
}
int ThreadPool::getBusyNum()
{
    pthread_mutex_lock(&mutexpool);
    int tmp = busyNum;
    pthread_mutex_unlock(&mutexpool);
    return tmp;
}
int ThreadPool::getAliveNum()
{
    pthread_mutex_lock(&mutexpool);
    int tmp = liveNum;
    pthread_mutex_unlock(&mutexpool);
    return tmp;
}

void *ThreadPool::worker(void *arg) //传进this
{
    //核心：任务队列里有任务就取&&执行
    ThreadPool *pool = static_cast<ThreadPool *>(arg);
    while (true)
    {
        pthread_mutex_lock(&pool->mutexpool);
        while (pool->TaskQ->taskNumber() == 0 && !pool->shutdown)
        {
            //阻塞
            pthread_cond_wait(&pool->notEmpty, &pool->mutexpool);
            if (0 && pool->exitNum)
            {
                // exit
            }
        }
        if (pool->shutdown)
        {
            pthread_mutex_unlock(&pool->mutexpool);
            pool->threadExit();
        }
        //可以取任务了
        Task task = pool->TaskQ->getTask();
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexpool);
        // do
        task.function(task.arg);
        // delete task.arg;
        task.function = nullptr;
        pthread_mutex_lock(&pool->mutexpool);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexpool);
    }
    return nullptr;
}

void *ThreadPool::manager(void *arg)
{
    ThreadPool *pool = static_cast<ThreadPool *>(arg);
    while (!pool->shutdown)
    {
        sleep(5);
        pthread_mutex_lock(&pool->mutexpool);
        //取数据

        pthread_mutex_unlock(&pool->mutexpool);
        if (0) //加线程
        {
            pthread_mutex_lock(&pool->mutexpool);

            pthread_mutex_unlock(&pool->mutexpool);
        }
        if (0) //减线程
        {
            pthread_mutex_lock(&pool->mutexpool);

            pthread_mutex_unlock(&pool->mutexpool);
        }
        if (pool->shutdown)
        {
            //退出了
        }
    }
    return nullptr;
}

void ThreadPool::threadExit()
{
    pthread_t tid = pthread_self();
    for (int i = 0; i < maxNum; i++)
    {
        if (workersID[i] == tid)
        {
            workersID[i] = 0;
            break;
        }
    }
    pthread_exit(NULL);
}
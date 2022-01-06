#include "ThreadPool.h"

ThreadPool::ThreadPool(int _min, int _max)
{
    TaskQ = new TaskQueue;
    minNum = _min;
    maxNum = _max;
}

ThreadPool::~ThreadPool()
{
}
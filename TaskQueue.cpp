#include "TaskQueue.h"

TaskQueue::TaskQueue()
{
    pthread_mutex_init(&mutex, NULL);
}
TaskQueue::~TaskQueue()
{
    pthread_mutex_destroy(&mutex);
}
void TaskQueue::addTask(Task taskk)
{
    pthread_mutex_lock(&mutex);
    TaskQ.push(taskk);
    pthread_mutex_unlock(&mutex);
}

void TaskQueue::addTask(callback f, void *arg)
{
    pthread_mutex_lock(&mutex);
    TaskQ.push((Task){f, arg});
    pthread_mutex_unlock(&mutex);
}

Task TaskQueue::getTask()
{
    Task t;
    pthread_mutex_lock(&mutex);
    if (!TaskQ.empty())
    {
        t = TaskQ.front();
        TaskQ.pop();
    }
    pthread_mutex_unlock(&mutex);
    return t;
}

int TaskQueue::taskNumber()
{
    return TaskQ.size();
}
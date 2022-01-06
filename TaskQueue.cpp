#include "taskqueue.h"

Taskqueue::Taskqueue()
{
    pthread_mutex_init(&mutex, NULL);
}
Taskqueue::~Taskqueue()
{
    pthread_mutex_destroy(&mutex);
}
void Taskqueue::addTask(Task taskk)
{
    pthread_mutex_lock(&mutex);
    TaskQ.push(taskk);
    pthread_mutex_unlock(&mutex);
}

void Taskqueue::addTask(callback f, void *arg)
{
    pthread_mutex_lock(&mutex);
    TaskQ.push((Task){f, arg});
    pthread_mutex_unlock(&mutex);
}

Task Taskqueue::getTask()
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

int Taskqueue::taskNumber()
{
    return TaskQ.size();
}
#ifndef TASK_QUQUE_H_
#define TASK_QUQUE_H_
#include <queue>
#include <pthread.h>
using callback = void (*)(void *); //函数指针
class Task
{
private:
    callback function;
    void *arg;

public:
    Task() : function(nullptr), arg(nullptr) {}
    Task(callback _f, void *_arg) : function(_f), arg(_arg){};
    ~Task();
};

class Taskqueue
{
private:
    std::queue<Task> TaskQ; //任务队列
    pthread_mutex_t mutex;  //互斥锁
public:
    Taskqueue();
    ~Taskqueue();

    void addTask(Task task); //添加任务
    Task getTask();          //取出一个任务
    inline int taskNumber(); //获取队列的任务数量
};

#endif
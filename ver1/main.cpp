#include <iostream>
#include <ctime>
#include "ThreadPool.h"
#include <unistd.h>
using namespace std;

void func(void *arg)
{
    int num = *(int *)arg;
    cout << to_string(pthread_self())<<" is working~~~~~~~~ " << num << endl;
    //sleep(1);
}

int main()
{
    ThreadPool pool(3, 10);
    sleep(1);
    for (int i = 1; i <= 100; i++)
    {
        int *num = new int(100 + i);
        // cout << "!!" << endl;
        pool.addTask(Task(func, num));
    }
    sleep(10);
    return 0;
}

#include <iostream>
#include <ctime>
#include "ThreadPool.h"
#include <unistd.h>
using namespace std;

void func(void *arg)
{
    cout << "!" << endl;
}

int main()
{
    ThreadPool pool(3, 10);

    for (int i = 1; i <= 100; i++)
    {
        int *num = new int(100 + i);
        // cout << "!!" << endl;
        pool.addTask(Task(func, num));
    }
    return 0;
}
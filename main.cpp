#include <iostream>
#include <ctime>
using namespace std;
void init() {}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int StartTime = clock();
#endif
    int T = 1;
    scanf("%d", &T);
    while (T--)
    {
        cout << "hello world" << endl;
    }
#ifndef ONLINE_JUDGE
    printf("Run_Time = %d ms\n", clock() - StartTime);
#endif
    return 0;
}
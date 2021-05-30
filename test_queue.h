#include "queue.h"
#include "list.h"
#include <iostream>
using namespace std;

void test_queue()
{
    mystl::queue<int> que;
    que.push(1);
    que.push(2);
    que.push(3);
    que.push(4);

    cout << que.size() << endl;
    cout << que.front() << endl;

    que.pop(); cout << que.front() << endl;
    que.pop(); cout << que.front() << endl;
    que.pop(); cout << que.front() << endl;
    cout << que.size() << endl;

    mystl::queue<int, mystl::list<int>> que2;
    que2.push(1);
    que2.push(2);
    que2.push(3);
    que2.push(4);

    cout << que2.size() << endl;
    cout << que2.front() << endl;

    que2.pop(); cout << que2.front() << endl;
    que2.pop(); cout << que2.front() << endl;
    que2.pop(); cout << que2.front() << endl;
    cout << que2.size() << endl;
}
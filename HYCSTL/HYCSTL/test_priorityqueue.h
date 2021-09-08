#include "priority_queue.h"
#include <iostream>
using namespace std;

void test_priorityQueue()
{
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    mystl::priority_queue<int> ipq(ia, ia + 9);
    cout << "size=" << ipq.size() << endl;

    for(int i = 0; i < ipq.size(); ++i)
        cout << ipq.top() << ' ';
    cout << endl;

    while (!ipq.empty())
    {
        cout << ipq.top() << ' ';
        ipq.pop();
    }
    cout << endl;
}
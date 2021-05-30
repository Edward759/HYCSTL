#include "stack.h"
#include "list.h"
#include <iostream>
using namespace std;

void test_stack()
{
    mystl::stack<int> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.push(4);

    cout << stk.size() << endl;
    cout << stk.top() << endl;

    stk.pop(); cout << stk.top() << endl;
    stk.pop(); cout << stk.top() << endl;
    stk.pop(); cout << stk.top() << endl;
    cout << stk.size() << endl;

    mystl::stack<int, mystl::list<int>> stk2;
    stk2.push(1);
    stk2.push(2);
    stk2.push(3);
    stk2.push(4);

    cout << stk2.size() << endl;
    cout << stk2.top() << endl;

    stk2.pop(); cout << stk2.top() << endl;
    stk2.pop(); cout << stk2.top() << endl;
    stk2.pop(); cout << stk2.top() << endl;
    cout << stk2.size() << endl;
}
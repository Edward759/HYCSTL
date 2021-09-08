#include "deque.h"
#include "alloc.h"
#include <iostream>
using namespace std;

void test_deque()
{
    mystl::deque<int, alloc, 8> ideq(20, 9);
    cout << "size=" << ideq.size() << endl;

    for(int i = 0; i < ideq.size(); ++i)
        ideq[i] = i;

    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;

    for(int i = 0; i < 3; i++)
        ideq.push_back(i);

    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.push_back(3);
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.push_front(99);
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.push_front(98);
    ideq.push_front(97);
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    mystl::deque<int, alloc, 8>::iterator iter;
    iter = mystl::find(ideq.begin(), ideq.end(), 99);
    cout << *iter << endl;
    cout << *(iter.cur) << endl;

    ideq.pop_back();
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.pop_front();
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.erase(ideq.begin() + 2);
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.erase(ideq.begin() + 2, ideq.begin() + 5);
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.insert(ideq.begin() + 2, 100);
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;

    ideq.clear();
    for(int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;
    cout << "size=" << ideq.size() << endl;
}
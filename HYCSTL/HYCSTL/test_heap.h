#include "heap.h"
#include "vector.h"
#include <iostream>
using namespace std;

void test_heap()
{
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    mystl::vector<int> ivec(ia, ia + 9);

    mystl::make_heap(ivec.begin(), ivec.end());
    for(int i = 0; i < ivec.size(); ++i)
        cout << ivec[i] << ' ';
    cout << endl;

    ivec.push_back(7);
    mystl::push_heap(ivec.begin(), ivec.end());
    for(int i = 0; i < ivec.size(); ++i)
        cout << ivec[i] << ' ';
    cout << endl;

    mystl::pop_heap(ivec.begin(), ivec.end());
    cout << ivec.back() << endl;
    ivec.pop_back();

    for(int i = 0; i < ivec.size(); ++i)
        cout << ivec[i] << ' ';
    cout << endl;

    mystl::sort_heap(ivec.begin(), ivec.end());
    for(int i = 0; i < ivec.size(); ++i)
        cout << ivec[i] << ' ';
    cout << endl;

    int ia2[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    mystl::make_heap(ia2, ia2 + 9);

    mystl::sort_heap(ia2, ia2 + 9);
    for(int i = 0; i < 9; ++i)
        cout << ia2[i] << ' ';
    cout << endl;

    mystl::make_heap(ia2, ia2 + 9);
    mystl::pop_heap(ia2, ia2 + 9);
    cout << ia2[8] << endl;
}
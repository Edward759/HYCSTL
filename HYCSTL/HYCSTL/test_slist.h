#pragma once
#include "slist.h"
#include "algobase.h"
#include <iostream>
using namespace std;


void test_slist()
{
    int i;
    mystl::slist<int> islist;
    cout << "size=" << islist.size() << endl;

    islist.push_front(9);
    islist.push_front(1);
    islist.push_front(2);
    islist.push_front(3);
    islist.push_front(4);
    cout << "size=" << islist.size() << endl;

    mystl::slist<int>::iterator ite = islist.begin();
    mystl::slist<int>::iterator ite2 = islist.end();
    for(; ite != ite2; ++ite)
        cout << *ite << ' ';
    cout << endl;

    ite = mystl::find(islist.begin(), islist.end(), 1);
    if(ite != 0)
        islist.insert(ite, 99);
    cout << "size=" << islist.size() << endl;
    cout << *ite << endl;
    
    ite = islist.begin();
    ite2 = islist.end();
    for(; ite != ite2; ++ite)
        cout << *ite << ' ';
    cout << endl;
}
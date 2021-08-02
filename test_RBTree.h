#pragma once
#include "RBTree.h"
#include "function.h"
#include <iostream>
using namespace std;
using namespace mystl;


void test_RBTree()
{
    mystl::rb_tree<int, int, mystl::identity<int>, mystl::less<int>> itree;
    cout << itree.size() << endl;

    itree.insert_unique(10);
    itree.insert_unique(7);
    itree.insert_unique(8);

    itree.insert_unique(15);
    itree.insert_unique(5);
    itree.insert_unique(6);

    itree.insert_unique(11);

    itree.insert_unique(13);
    itree.insert_unique(12);

    cout << itree.size() << endl;

    rb_tree<int, int, mystl::identity<int>, mystl::less<int>>::iterator iter1 = itree.begin();
    rb_tree<int, int, mystl::identity<int>, mystl::less<int>>::iterator iter2 = itree.end();
    for (; iter1 != iter2; ++iter1)
        cout << *iter1 << ' ';
    cout << endl;

    iter1 = itree.begin();
    iter2 = itree.end();
    __rb_tree_base_iterator rbtite;
    for (; iter1 != iter2; ++iter1)
    {
        rbtite = __rb_tree_base_iterator(iter1);
        cout << *iter1 << '(' << rbtite.node->color << ") ";
    }
    cout << endl;
}


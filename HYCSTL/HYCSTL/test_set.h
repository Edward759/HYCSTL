#pragma once

#include "set.h"
#include <iostream>
using namespace std;

void test_set()
{
    int i;
    int ia[5] = {0, 1, 2, 3, 4};
    set<int> iset(ia, ia + 5);

    cout << "size=" << iset.size() << endl;
    cout << "3 count=" << iset.count(3) << endl;

    iset.insert(3);
    cout << "size=" << iset.size() << endl;
    cout << "3 count=" << iset.count(3) << endl;

    iset.insert(5);
    cout << "size=" << iset.size() << endl;
    cout << "3 count=" << iset.count(3) << endl;

    iset.erase(1);
    cout << "size=" << iset.size() << endl;
    cout << "3 count=" << iset.count(3) << endl;
    cout << "1 count=" << iset.count(1) << endl;

	set<int>::iterator iter1 = iset.begin();
	set<int>::iterator iter2 = iset.end();
	for (; iter1 != iter2; ++iter1)
		cout << *iter1;
	cout << endl;

	iter1 = mystl::find(iset.begin(), iset.end(), 3);
	if (iter1 != iset.end())
		cout << "3 found" << endl;

	iter1 = mystl::find(iset.begin(), iset.end(), 1);
	if (iter1 == iset.end())
		cout << "1 not found" << endl;

	iter1 = iset.find(3);
	if (iter1 != iset.end())
		cout << "3 found" << endl;

	iter1 = iset.find(1);
	if (iter1 == iset.end())
		cout << "1 not found" << endl;
}
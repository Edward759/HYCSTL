#pragma once
#include <iostream>
#include "list.h"
#include "algo.h"
using namespace std;

void test_list()
{
	mystl::list<int> ilist;
	cout << "size=" << ilist.size() << endl;

	ilist.push_back(0);
	ilist.push_back(1);
	ilist.push_back(2);
	ilist.push_back(3);
	ilist.push_back(4);
	cout << "size=" << ilist.size() << endl;

	mystl::list<int>::iterator iter;
	for (iter = ilist.begin(); iter != ilist.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;

	iter = mystl::find(ilist.begin(), ilist.end(), 3);
	if (iter != nullptr)
		ilist.insert(iter, 99);
	cout << "size=" << ilist.size() << endl;
	cout << *iter << endl;

	for (iter = ilist.begin(); iter != ilist.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;

	iter = mystl::find(ilist.begin(), ilist.end(), 1);
	if (iter != nullptr)
		cout << *(ilist.erase(iter)) << endl;

	for (iter = ilist.begin(); iter != ilist.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;
}
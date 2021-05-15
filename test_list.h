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

	iter = ilist.begin() + 1;
	cout << *iter << endl;
	iter = ilist.end() - 2;
	cout << *iter << endl;

	cout << "Transeferring in the same list." << endl;
	cout << "Before transfer:" << endl;
	for (iter = ilist.begin(); iter != ilist.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;
	cout << "After transfer:" << endl;
	ilist.transfer(ilist.begin(), ilist.begin() + 1, ilist.begin() + 3);
	for (iter = ilist.begin(); iter != ilist.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;
	cout << endl;

	cout << "Transeferring in different lists." << endl;
	mystl::list<int> ilist1, ilist2;

	ilist1.push_back(0);
	ilist1.push_back(1);
	ilist1.push_back(2);
	ilist1.push_back(3);
	ilist1.push_back(4);

	ilist2.push_back(10);
	ilist2.push_back(11);
	ilist2.push_back(12);
	ilist2.push_back(13);
	ilist2.push_back(14);

	cout << "list1 before transfer:" << endl;
	for (iter = ilist1.begin(); iter != ilist1.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;
	cout << "list2 before transfer:" << endl;
	for (iter = ilist2.begin(); iter != ilist2.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;

	cout << "Exec ilist1.transfer(ilist1.begin(), ilist2.begin() + 1, ilist2.begin() + 3)" << endl;
	ilist1.transfer(ilist1.begin(), ilist2.begin() + 1, ilist2.begin() + 3);

	cout << "list1 after transfer:" << endl;
	for (iter = ilist1.begin(); iter != ilist1.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;
	cout << "list2 after transfer:" << endl;
	for (iter = ilist2.begin(); iter != ilist2.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;
	cout << endl;

}
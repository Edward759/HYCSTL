#pragma once
#include <iostream>
#include <string>
#include "list.h"
#include "algo.h"
using namespace std;

void print(mystl::list<int>& ilist, string name = "")
{
	mystl::list<int>::iterator iter;
	
	if(name != "")
		cout << name << ":" << endl;
	for (iter = ilist.begin(); iter != ilist.end(); ++iter)
		cout << *iter << ' ';
	cout << endl;
	cout << endl;
}

mystl::list<int> fill(int n = 0)
{
	mystl::list<int> l;

	for(int i = 0; i < 5; i++)
	{
		int elem = i + 10 * n;
		l.push_back(elem);
	}
	cout << "new list:"<<endl;
	print(l);
	return l;
}

void test_list()
{
	mystl::list<int> ilist;
	cout << "size=" << ilist.size() << endl;

	ilist = fill();
	cout << "size=" << ilist.size() << endl;
	print(ilist);

	mystl::list<int>::iterator iter;
	iter = mystl::find(ilist.begin(), ilist.end(), 3);
	if (iter != nullptr)
		ilist.insert(iter, 99);
	cout << "size=" << ilist.size() << endl;
	cout << *iter << endl;

	print(ilist);

	iter = mystl::find(ilist.begin(), ilist.end(), 1);
	if (iter != nullptr)
		cout << *(ilist.erase(iter)) << endl;

	print(ilist);

	iter = ilist.begin() + 1;
	cout << *iter << endl;
	iter = ilist.end() - 2;
	cout << *iter << endl;

	mystl::list<int> ilist1, ilist2;

	ilist1 = fill();
	ilist2 = fill(1);

	cout << "ilist1:"<<endl;
	print(ilist1);
	cout << "ilist2:"<<endl;
	print(ilist2);

	cout << "ilist1.splice(ilist1.begin() + 1, ilist2):" << endl;
	ilist1.splice(ilist1.begin() + 1, ilist2);
	print(ilist1);

	ilist1 = fill();
	ilist2 = fill(1);

	cout << "ilist1.splice(iter1, ilist1, iter2)" <<endl;
	auto iter1 = ilist1.begin() + 1, iter2 = ilist2.begin();
	ilist1.splice(iter1, ilist1, iter2);
	print(ilist1, "ilist1");

	ilist1 = fill();
	ilist2 = fill(1);
	cout << "ilist1.splice(ilist1.begin() + 1, ilist1, ilist2.begin(), ilist2.end())" <<endl;
	ilist1.splice(ilist1.begin() + 1, ilist1, ilist2.begin(), ilist2.end());
	print(ilist1, "ilist1");

	ilist1 = fill();
	ilist2 = fill(1);
	ilist1.push_back(27);
	cout << "exec ilist1.merge(ilist2)" <<endl;
	ilist1.merge(ilist2);
	print(ilist1, "ilist1");

	ilist.clear();
	ilist = fill();
	cout << "exec ilist.reverse()" <<endl;
	ilist.reverse();

	print(ilist, "ilist");

	ilist.push_back(9);
	ilist.push_back(7);
	ilist.push_back(5);
	print(ilist, "ilist");
	ilist.sort();
	print(ilist, "ilist");
}
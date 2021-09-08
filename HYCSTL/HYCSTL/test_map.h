#pragma once
#include "map.h"
#include<iostream>
using namespace std;

void test_map()
{
	mystl::map<string, int>simap;
	simap[string("jjhou")] = 1;
	simap[string("jerry")] = 2;
	simap[string("jason")] = 3;
	simap[string("jimmy")] = 4;

	mystl::pair<string, int> value(string("david"), 5);
	simap.insert(value);

	mystl::map<string, int>::iterator simap_iter = simap.begin();
	for (; simap_iter != simap.end(); ++simap_iter)
		cout << simap_iter->first << ' '
		<< simap_iter->second << endl;

	int number = simap[string("jjhou")];
	cout << number << endl;

	mystl::map<string, int>::iterator iter1;

	iter1 = simap.find(string("mchen"));
	if (iter1 == simap.end())
		cout << "mchen not found" << endl;

	iter1 = simap.find(string("jerry"));
	if (iter1 != simap.end())
		cout << "jerry found" << endl;

	iter1->second = 9;
	int number2 = simap[string("jerry")];
	cout << number2 << endl;
}
#pragma once
#include "hashtable.h"
#include "hash_func.h"
#include "function.h"
#include <iostream>
using namespace std;

__STL_BEGIN_NAMESPACE

void test_hashtable()
{
	mystl::hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc>
		iht(50, hash<int>(), equal_to<int>());
	cout << iht.size() << endl;
	cout << iht.bucket_count() << endl;

	iht.insert_unique(59);
	iht.insert_unique(63);
	iht.insert_unique(108);
	cout << iht.size() << endl;
	cout << iht.bucket_count() << endl;

	hashtable<int,
		int,
		hash<int>,
		identity<int>,
		equal_to<int>,
		alloc>
		iht2(50, hash<int>(), equal_to<int>());

	cout << iht2.size() << endl;
	cout << iht2.bucket_count() << endl;
	cout << iht2.max_bucket_count() << endl;

	iht2.insert_unique(59);
	iht2.insert_unique(63);
	iht2.insert_unique(108);
	iht2.insert_unique(2);
	iht2.insert_unique(53);
	iht2.insert_unique(55);
	cout << iht2.size() << endl;

	hashtable<int,
		int,
		hash<int>,
		identity<int>,
		equal_to<int>,
		alloc>
		::iterator iter = iht2.begin();

	for (int i = 0; i < iht2.size(); ++i, ++iter)
		cout << *iter << ' ';
	cout << endl;

	for (int i = 0; i < iht2.bucket_count(); ++i) {
		int n = iht2.elems_in_bucket(i);
		if (n != 0)
			cout << "bucket [" << i << "] has " << n << " elems." << endl;
	}
	
	for (int i = 0; i <= 47; i++)
		iht2.insert_equal(i);
	cout << iht2.size() << endl;
	cout << iht2.bucket_count() << endl;

	for (int i = 0; i < iht2.bucket_count(); ++i) {
		int n = iht2.elems_in_bucket(i);
		if (n != 0)
			cout << "bucket[" << i << "] has " << n << " elems." << endl;
	}

	iter = iht2.begin();
	for (int i = 0; i < iht2.size(); ++i, ++iter)
		cout << *iter << ' ';
	cout << endl;

	cout << *(iht2.find(2)) << endl;
	cout << iht2.count(2) << endl;
}

__STL_END_NAMESPACE
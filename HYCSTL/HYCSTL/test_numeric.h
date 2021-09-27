#pragma once
#include "numeric.h"
#include "vector.h"
#include "function.h"
#include <iostream>
using namespace std;

__STL_BEGIN_NAMESPACE

void test_numeric()
{
	int ia[5] = { 1,2,3,4,5 };
	vector<int>iv(ia, ia + 5);

	cout << accumulate(iv.begin(), iv.end(), 0) << endl;
	cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) << endl;

	cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;
	cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10,
		minus<int>(),plus<int>()) << endl;
}

__STL_END_NAMESPACE
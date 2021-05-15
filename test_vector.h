#pragma once
#include <iostream>

#include "vector.h"
#include "algo.h"

void OutOfMem()
{
	std::cerr << "out of memory" << std::endl;
	std::abort();
}

void test_vector()
{
	mystl::malloc_alloc::set_malloc_handler(OutOfMem);
	mystl::vector<int>iv(2, 9);
	iv.push_back(1);
	iv.push_back(2);
	iv.push_back(3);
	iv.push_back(4);

	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;

	for (int i = 0; i < iv.size(); ++i)
		std::cout << iv[i] << " ";
	std::cout << std::endl;

	iv.push_back(5);
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;

	for (int i = 0; i < iv.size(); ++i)
		std::cout << iv[i] << " ";
	std::cout << std::endl;

	iv.pop_back();
	iv.pop_back();
	std::cout << "size=" << iv.size() << std::endl;
	std::cout << "capacity=" << iv.capacity() << std::endl;

	for (int i = 0; i < iv.size(); ++i)
		std::cout << iv[i] << " ";
	std::cout << std::endl;

	iv.insert(iv.begin() + 2, 3, 7);

	iv.erase(iv.begin(), iv.begin() + 2);
	for (int i = 0; i < iv.size(); ++i)
		std::cout << iv[i] << " ";
	std::cout << std::endl;

	mystl::vector<int>::iterator iter = mystl::find(iv.begin(), iv.end(), 1);
	std::cout << *iter << std::endl;

	iv.clear();
	for (int i = 0; i < iv.size(); ++i)
		std::cout << iv[i] << " ";
	std::cout << std::endl;
}
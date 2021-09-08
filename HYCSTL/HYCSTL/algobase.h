#pragma once
#include "iterator.h"

namespace mystl
{
	template<class OutputIterator,class Size,class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}

	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}

	template <class InputIterator, class OutputIterator>
	struct __copy_dispatch
	{
		OutputIterator operator() (InputIterator first, InputIterator last, OutputIterator result)
		{
			return __copy(first, last, result, iterator_category(first));
		}
	};

	template <class InputIterator,class OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		return __copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
	}

	inline char* copy(const char* first, const char* last, char* result)
	{
		memmove(result, first, last - first);
		return result + (last - first);
	}

	inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
	{
		memmove(result, first, sizeof(wchar_t)*(last - first));
		return result + (last - first);
	}

	

	template <class InputIterator, class OutputIterator>
	inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag)
	{
		for (; first != last; ++result, ++first)
			*result = *first;
		return result;
	};

	template <class T>
	struct __copy_dispatch<T*, T*>
	{
		T* operator() (T* first, T*last, T* result)
		{
			typedef typename __type_traits<T>::has_trivial_assignment_operator t;
			return __copy_t(first, last, result, t());
		}
	};

	template <class T>
	struct __copy_dispatch<const T*, T*>
	{
		T* operator() (const T* first, const T*last, T* result)
		{
			typedef typename __type_traits<T>::has_trivial_assignment_operator t;
			return __copy_t(first, last, result, t());
		}
	};

	template <class RandomAccessIerator, class OutputIterator>
	inline OutputIterator __copy(RandomAccessIerator first, RandomAccessIerator last, 
		OutputIterator result, random_access_iterator_tag)
	{
		return __copy_d(first, last, result, distance_type(first));
	};

	template <class RandomAccessIerator, class OutputIterator, class Distance>
	inline OutputIterator __copy_d(RandomAccessIerator first, RandomAccessIerator last, 
			OutputIterator result, Distance*)
	{
		for (Distance n = last - first; n > 0; --n, ++result, ++first)
			*result = *first;
		return result;
	};

	template <class T>
	inline T* __copy_t(const T* first, const T* last, T* result, __true_type)
	{
		memmove(result, first, sizeof(T)*(last - first));
		return result + (last - first);
	}

	template <class T>
	inline T* __copy_t(const T* first, const T* last, T* result, __false_type)
	{
		return __copy_d(first, last, result, (ptrdiff_t*)0); 
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2>
	inline BidirectionalIterator2 __copy_backward(BidirectionalIterator1 first,
		BidirectionalIterator1 last,
		BidirectionalIterator2 result)
	{
		for (; first != last; --result, --last)
			*result = *last;
		return result;
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2>
	struct __copy_backward_dispatch
	{
		BidirectionalIterator2 operator()(BidirectionalIterator1 first,
			BidirectionalIterator1 last,
			BidirectionalIterator2 result)
		{
			return __copy_backward(first, last, result);
		}
	};

	template <class BidirectionalIterator1, class BidirectionalIterator2>
	inline BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, 
												BidirectionalIterator1 last, 
												BidirectionalIterator2 result)
	{
		return __copy_backward_dispatch<BidirectionalIterator1, 
										BidirectionalIterator2>()(first, last, result);
	}

	

	

	template <class T>
	struct __copy_backward_dispatch<T*, T*>
	{
		T* operator() (T* first, T*last, T* result)
		{
			typedef typename __type_traits<T>::has_trivial_assignment_operator t;
			return __copy_backward_t(first, last, result, t());
		}
	};

	template <class T>
	struct __copy_backward_dispatch<const T*, T*>
	{
		T* operator() (const T* first, const T*last, T* result)
		{
			typedef typename __type_traits<T>::has_trivial_assignment_operator t;
			return __copy_backward_t(first, last, result, t());
		}
	};

	template <class T>
	inline T* __copy_backward_t(const T* first, const T* last, T* result, __true_type)
	{
		const ptrdiff_t N = last - first;
		memmove(result - N, first, sizeof(T) * N);
		return result - N;
	}

	template <class T>
	inline T* __copy_backward_t(const T* first, const T* last, T* result, __false_type)
	{
		return __copy_backward(first, last, result);
	}

	template <class T>
	inline const T& max(const T& a, const T& b)
	{
		return a < b ? b : a;
	}

	template <class T,class Compare>
	inline const T& max(const T& a, const T& b, Compare comp)
	{
		return comp(a, b) ? b : a;
	}

	template <class T>
	inline void swap(T& a, T& b) 
	{
		T tmp = a;
		a = b;
		b = tmp;
	}
}
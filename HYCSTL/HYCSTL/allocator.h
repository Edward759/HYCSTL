#pragma once

namespace mystl
{
	template <class T>
	inline T* allocate(ptrdiff_t size, T*)
	{
		set_new_handler(nullptr);
		T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if (nullptr == tmp)
		{
			cerr << "out of memory" << endl;
			exit(1);
		}
		return tmp;
	}

	template <class T>
	inline void deallocate(T* buffer)
	{
		::operator delete(buffer);
	}

	template <class T>
	class allocator
	{
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*		const_pointer;
		typedef T&			reference;
		typedef const T&		const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

	public:
		static T* allocate(size_type n);
		static void deallocate(pointer ptr);
		static pointer address(reference x);
		static const_pointer const_address(const_reference x);
		static size_type init_page_size();
		static size_type max_size()const;
	};

	template <class T>
	T* allocator<T>::allocate(size_type n)
	{
		return mystl::allocate((difference_type)n, (pointer)0);
	}

	template <class T>
	void allocator<T>::deallocate(pointer ptr)
	{
		mystl::deallocate(ptr);
	}

	template <class T>
	allocator<T>::pointer allocator<T>::address(reference x)
	{
		return (pointer)&x;
	}

	template <class T>
	allocator<T>::const_pointer allocator<T>::const_address(const_reference x)
	{
		return (const_pointer)&x;
	}

	template <class T>
	allocator<T>::size_type allocator<T>::init_page_size()
	{
		return max(size_type(1), size_type(4096 / sizeof(T)));
	}

	template <class T>
	allocator<T>::size_type allocator<T>::max_size()const
	{
		return max(size_type(1), size_type(UINT_MAX / sizeof(T)));
	}

	class allocator<void>
	{
	public:
		typedef void* pointer;
	};
}
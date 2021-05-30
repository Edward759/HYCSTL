#pragma once
#include "heap.h"
#include "vector.h"
#include "function.h"

namespace mystl
{
    template <class T, class Sequence = vector<T>,
                class Compare = less<typename Sequence::value_type>>
    class priority_queue
    {
    public:
        typedef typename Sequence::value_type value_type;
        typedef typename Sequence::size_type size_type;
        typedef typename Sequence::reference reference;
        typedef typename Sequence::const_reference const_reference;

    protected:
        Sequence c;
        Compare comp;
    public:
        priority_queue() : c() {}
        explicit priority_queue(const Compare& x) : c(), comp(x){}

        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last, const Compare& x)
        : c(first, last), comp(x)
        {
            make_heap(c.begin(), c.end(), comp);
        }
        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last)
        : c(first, last)
        {
            make_heap(c.begin(), c.end(), comp);
        }

        bool empty()const{return c.empty();}
        size_type size()const{return c.size();}
        const_reference top()const{return c.front();}
        void push(const value_type& x)
        {
            try
            {
                c.push_bacK(x);
                push_heap(c.begin(), c.end(), comp);
            }
            catch(const std::exception& e)
            {
                c.clear();
            }
        }
        void pop()
        {
            try
            {
                pop_heap(c.begin(), c.end(), comp);
                c.pop_back();
            }
            catch(const std::exception& e)
            {
                c.clear();
            }
            
        }
    };
}; // namespace mystl

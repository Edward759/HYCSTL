#pragma once
#include "iterator.h"
#include "alloc.h"
#include "pair.h"

namespace mystl
{
    typedef bool __rb_tree_color_type;
    const __rb_tree_color_type __rb_tree_red = false;
    const __rb_tree_color_type __rb_tree_black = true;

    struct __rb_tree_node_base
    {
        typedef __rb_tree_color_type color_type;
        typedef __rb_tree_node_base *base_ptr;

        color_type color;
        base_ptr parent;
        base_ptr left;
        base_ptr right;

        static base_ptr minimum (base_ptr x)
        {
            while (x->left != 0)
                x = x->left;
            return x;
        }

        static base_ptr maximum (base_ptr x)
        {
            while (x->right != 0)
                x = x->right;
            return x;
        }
    };

    template <class Value>
    struct __rb_tree_node : public __rb_tree_node_base
    {
        typedef __rb_tree_node<Value> *link_type;
        Value value_field;
    };

    struct __rb_tree_base_iterator
    {
        typedef __rb_tree_node_base::base_ptr base_ptr;
        typedef bidirectional_iterator_tag iterator_category;
        typedef ptrdiff_t difference_type;

        base_ptr node;

        void increment()
        {
            if(node->right != 0)
            {
                node = node->right;
                while(node->left != 0)
                    node = node->left;
            }
            else
            {
                base_ptr y = node->parent;
                while(node == y->right)
                {
                    node = y;
                    y = y->parent;
                }
                if(node->right != y)
                    node = y;
            }
        }

        void decrement()
        {
            if(node->color == __rb_tree_red && node->parent->parent == node)
                node = node->right;
            else if(node->left != 0)
            {
                base_ptr y = node->left;
                while(y->right != 0)
                    y = y->right;
                node = y;
            }
            else
            {
                base_ptr y = node->parent;
                while(node == y->left)
                {
                    node = y;
                    y = y->parent;
                }
                node = y;
            }
        }
    };
    
    template <class Value, class Ref, class Ptr>
    struct __rb_tree_iterator : public __rb_tree_base_iterator
    {
        typedef Value value_type;
        typedef Ref reference;
        typedef Ptr pointer;
        typedef __rb_tree_iterator<Value, Value &, Value *> iterator;
        typedef __rb_tree_iterator<Value, const Value &, const Value *> const_iterator;
        typedef __rb_tree_iterator<Value, Ref, Ptr> self;
        typedef __rb_tree_node<Value> *link_type;

        __rb_tree_iterator(){}
        __rb_tree_iterator(link_type x) { node = x; }
        __rb_tree_iterator(const iterator &it) { node = it.node; }

        reference operator*() const { return link_type(node)->value_field; }
        pointer operator->() const { return &(operator*()); }

        self &operator++() 
        { 
            increment();
            return *this;
        }
        self operator++(int)
        {
            self tmp = *this;
            increment();
            return tmp;
        }

        self &operator--() 
        { 
            decrement();
            return *this;
        }
        self operator--(int)
        {
            self tmp = *this;
            decrement();
            return tmp;
        }
    };
    
    inline bool operator==(const __rb_tree_base_iterator& x, const __rb_tree_base_iterator& y)
    {
        return x.node == y.node;
    }

    inline bool operator!=(const __rb_tree_base_iterator& x, const __rb_tree_base_iterator& y) 
    {
        return x.node != y.node;
    }

	inline void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root)
	{
		__rb_tree_node_base *y = x->right;
		x->right = y->left;
		if (y->left != 0)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;

		if (x == root)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	inline void __rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root)
	{
		__rb_tree_node_base *y = x->left;
		x->left = y->right;
		if (y->right != 0)
			y->right->parent = x;
		y->parent = x->parent;

		if (x == root)
			root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root)
	{
		x->color = __rb_tree_red;
		while (x != root && x->parent->color == __rb_tree_red)
		{
			if (x->parent == x->parent->parent->left)
			{
				__rb_tree_node_base *y = x->parent->parent->right;
				if (y && y->color == __rb_tree_red)
				{
					x->parent->color = __rb_tree_black;
					y->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_rebalance;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->right)
					{
						x = x->parent;
						__rb_tree_rotate_left(x, root);
					}
					x->parent->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					__rb_tree_rotate_right(x->parent->parent, root);
				}
			}
			else
			{
				__rb_tree_node_base *y = x->parent->parent->left;
				if (y && y->color == __rb_tree_red)
				{
					x->parent->color = __rb_tree_black;
					y->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->left)
					{
						x = x->parent;
						__rb_tree_rotate_right(x, root);
					}
					x->parent->color = __rb_tree_black;
					x->parent->parent->color = __rb_tree_red;
					__rb_tree_rotate_left(x->parent->parent, root);
				}
			}
		}
		root->color = __rb_tree_black;
	}

	inline __rb_tree_node_base*
		__rb_tree_rebalance_for_erase(__rb_tree_node_base* z,
			__rb_tree_node_base*& root,
			__rb_tree_node_base*& leftmost,
			__rb_tree_node_base*& rightmost)
	{
		__rb_tree_node_base* y = z;
		__rb_tree_node_base* x = 0;
		__rb_tree_node_base* x_parent = 0;
		if (y->left == 0)             // z has at most one non-null child. y == z.
			x = y->right;               // x might be null.
		else
			if (y->right == 0)          // z has exactly one non-null child.  y == z.
				x = y->left;              // x is not null.
			else {                      // z has two non-null children.  Set y to
				y = y->right;             //   z's successor.  x might be null.
				while (y->left != 0)
					y = y->left;
				x = y->right;
			}
		if (y != z) {                 // relink y in place of z.  y is z's successor
			z->left->parent = y;
			y->left = z->left;
			if (y != z->right) {
				x_parent = y->parent;
				if (x) x->parent = y->parent;
				y->parent->left = x;      // y must be a left child
				y->right = z->right;
				z->right->parent = y;
			}
			else
				x_parent = y;
			if (root == z)
				root = y;
			else if (z->parent->left == z)
				z->parent->left = y;
			else
				z->parent->right = y;
			y->parent = z->parent;
			mystl::swap(y->color, z->color);
			y = z;
			// y now points to node to be actually deleted
		}
		else {                        // y == z
			x_parent = y->parent;
			if (x) x->parent = y->parent;
			if (root == z)
				root = x;
			else
				if (z->parent->left == z)
					z->parent->left = x;
				else
					z->parent->right = x;
			if (leftmost == z)
				if (z->right == 0)        // z->left must be null also
					leftmost = z->parent;
			// makes leftmost == header if z == root
				else
					leftmost = __rb_tree_node_base::minimum(x);
			if (rightmost == z)
				if (z->left == 0)         // z->right must be null also
					rightmost = z->parent;
			// makes rightmost == header if z == root
				else                      // x == z->left
					rightmost = __rb_tree_node_base::maximum(x);
		}
		if (y->color != __rb_tree_red) {
			while (x != root && (x == 0 || x->color == __rb_tree_black))
				if (x == x_parent->left) {
					__rb_tree_node_base* w = x_parent->right;
					if (w->color == __rb_tree_red) {
						w->color = __rb_tree_black;
						x_parent->color = __rb_tree_red;
						__rb_tree_rotate_left(x_parent, root);
						w = x_parent->right;
					}
					if ((w->left == 0 || w->left->color == __rb_tree_black) &&
						(w->right == 0 || w->right->color == __rb_tree_black)) {
						w->color = __rb_tree_red;
						x = x_parent;
						x_parent = x_parent->parent;
					}
					else {
						if (w->right == 0 || w->right->color == __rb_tree_black) {
							if (w->left) w->left->color = __rb_tree_black;
							w->color = __rb_tree_red;
							__rb_tree_rotate_right(w, root);
							w = x_parent->right;
						}
						w->color = x_parent->color;
						x_parent->color = __rb_tree_black;
						if (w->right) w->right->color = __rb_tree_black;
						__rb_tree_rotate_left(x_parent, root);
						break;
					}
				}
				else {                  // same as above, with right <-> left.
					__rb_tree_node_base* w = x_parent->left;
					if (w->color == __rb_tree_red) {
						w->color = __rb_tree_black;
						x_parent->color = __rb_tree_red;
						__rb_tree_rotate_right(x_parent, root);
						w = x_parent->left;
					}
					if ((w->right == 0 || w->right->color == __rb_tree_black) &&
						(w->left == 0 || w->left->color == __rb_tree_black)) {
						w->color = __rb_tree_red;
						x = x_parent;
						x_parent = x_parent->parent;
					}
					else {
						if (w->left == 0 || w->left->color == __rb_tree_black) {
							if (w->right) w->right->color = __rb_tree_black;
							w->color = __rb_tree_red;
							__rb_tree_rotate_left(w, root);
							w = x_parent->left;
						}
						w->color = x_parent->color;
						x_parent->color = __rb_tree_black;
						if (w->left) w->left->color = __rb_tree_black;
						__rb_tree_rotate_right(x_parent, root);
						break;
					}
				}
			if (x) x->color = __rb_tree_black;
		}
		return y;
	}

    template <class Key, class Value, class KeyOfValue, class Compare,
            class Alloc = alloc>
    class rb_tree
    {
    protected:
        typedef void *void_pointer;
        typedef __rb_tree_node_base *base_ptr;
        typedef __rb_tree_node<Value> rb_tree_node;
        typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
        typedef __rb_tree_color_type color_type;
    public:
        typedef Key key_type;
        typedef Value value_type;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef rb_tree_node *link_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
    protected:
        link_type get_node()
        {
            return rb_tree_node_allocator::allocate();
        }
        void put_node(link_type p)
        {
            rb_tree_node_allocator::deallocate(p);
        }

        link_type create_node(const value_type& x)
        {
            link_type tmp = get_node();
            try
            {
                construct(&tmp->value_field, x);
            }
            catch(const std::exception& e)
            {
                put_node(tmp);
            }
            return tmp;
            
        }

        link_type clone_node(link_type x)
        {
            link_type tmp = create_node(x->value_field);
            tmp->color = x->color;
            tmp->left = 0;
            tmp->right = 0;
            return tmp;
        }

        void destroy_node(link_type p)
        {
            destroy(&p->value_field);
            put_node(p);
        }

    protected:
        size_type node_count;
        link_type header;
        Compare key_compare;

        link_type& root()const
        {
            return (link_type &)header->parent;
        }
        link_type& leftmost()const
        {
            return (link_type &)header->left;
        }
        link_type& rightmost()const
        {
            return (link_type &)header->right;
        }

        static link_type& left(link_type x)
        {
            return (link_type &)(x->left);
        }
        static link_type& right(link_type x)
        {
            return (link_type &)(x->right);
        }
        static link_type& parent(link_type x)
        {
            return (link_type &)(x->parent);
        }
        static reference value(link_type x)
        {
            return x->value_field;
        }
        static const Key& key(link_type x)
        {
            return KeyOfValue()(value(x));
        }
        static color_type& color(link_type x)
        {
            return (color_type &)(x->color);
        }

        static link_type& left(base_ptr x)
        {
            return (link_type &)(x->left);
        }
        static link_type& right(base_ptr x)
        {
            return (link_type &)(x->right);
        }
        static link_type& parent(base_ptr x)
        {
            return (link_type &)(x->parent);
        }
        static reference value(base_ptr x)
        {
            return ((link_type)x)->value_field;
        }
        static const Key& key(base_ptr x)
        {
            return KeyOfValue()(value(x));
        }
        static color_type& color(base_ptr x)
        {
            return (color_type &)(x->color);
        }

        static link_type minimum(link_type x)
        {
            return (link_type)__rb_tree_node_base::minimum(x);
        }
        static link_type maximum(link_type x)
        {
            return (link_type)__rb_tree_node_base::maximum(x);
        }

    public:
        typedef __rb_tree_iterator<value_type, reference, pointer> iterator;
        typedef __rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

    private:
        iterator __insert(base_ptr x, base_ptr y, const value_type &v);
        link_type __copy(link_type x, link_type p);
        void __erase(link_type x);
        void init()
        {
            header = get_node();
            color(header) = __rb_tree_red;

            root() = 0;
            leftmost() = header;
            rightmost() = header;
        }

        void clear() 
        {
            if (node_count != 0) 
            {
                __erase(root());
                leftmost() = header;
                root() = 0;
                rightmost() = header;
                node_count = 0;
            }
        }
        

    public:
        rb_tree(const Compare& comp = Compare())
        : node_count(0), key_compare(comp)
        {
            init();
        }
        ~rb_tree()
        {
            clear();
            put_node(header);
        }
        rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &
            operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc> &x);
        
    public:
        Compare key_comp()const
        {
            return key_compare;
        }
        iterator begin()
        {
            return leftmost();
        }

		const_iterator begin() const 
		{ 
			return leftmost(); 
		}

        iterator end()
        {
            return header;
        }

		const_iterator end() const 
		{ 
			return header; 
		}

        bool empty()const
        {
            return node_count == 0;
        }
        size_type size()const
        {
            return node_count;
        }
        size_type max_size()const
        {
            return size_type(-1);
        }

    public:
        iterator find(const key_type& x);
		const_iterator find(const key_type& x) const;
        size_type count(const key_type& x) const;
        pair<iterator, bool> insert_unique(const value_type &v)
        {
            link_type y = header;
            link_type x = root();
            bool comp = true;
            while(x != 0)
            {
                y = x;
                comp = key_compare(KeyOfValue()(v), key(x));
                x = comp ? left(x) : right(x);
            }

            iterator j = iterator(y);
            if(comp)
                if(j == begin())
                    return pair<iterator, bool>(__insert(x, y, v), true);
                else
                    --j;

            if(key_compare(key(j.node), KeyOfValue()(v)))
                return pair<iterator, bool>(__insert(x, y, v), true);

            return pair<iterator, bool>(j, false);
        }

        iterator insert_equal(const value_type &v)
        {
            link_type y = header;
            link_type x = root();
            while(x!=0)
            {
                y = x;
                x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
            }
            return __insert(x, y, v);
        }

        template <class InputIterator>
        void insert_unique(InputIterator first, InputIterator last);
        template <class InputIterator>
        void insert_equal(InputIterator first, InputIterator last);
        iterator lower_bound(const key_type& x);
        const_iterator lower_bound(const key_type& x) const;
        iterator upper_bound(const key_type& x);
        const_iterator upper_bound(const key_type& x) const;

        void erase(iterator position);
        size_type erase(const key_type& x);
        void erase(iterator first, iterator last);
        void erase(const key_type* first, const key_type* last);

        pair<iterator,iterator> equal_range(const key_type& x);
        pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
    };

    template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::
    __insert(base_ptr x_, base_ptr y_, const Value& v)
    {
        link_type x = (link_type)x_;
        link_type y = (link_type)y_;
        link_type z;

        if(y == header || x != 0 || key_compare(KeyOfValue()(v), key(y)))
        {
            z = create_node(v);
            left(y) = z;
            if(y == header)
            {
                root() = z;
                rightmost() = z;
            }
            else if(y == leftmost())
                leftmost() = z;
        }
        else
        {
            z = create_node(v);
            right(y) = z;
            if(y == rightmost())
                rightmost() = z;
        }
        parent(z) = y;
        left(z) = 0;
        right(z) = 0;

        __rb_tree_rebalance(z, header->parent);
        ++node_count;
        return iterator(z);
    }

    template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__erase(link_type x) 
    {
        while (x != 0)
        {
            __erase(right(x));
            link_type y = left(x);
            destroy_node(x);
            x = y;
        }
    }

    template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator 
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key& k) 
    {
        link_type y = header;        // Last node which is not less than k. 
        link_type x = root();        // Current node. 

        while (x != 0) 
        {
            if (!key_compare(key(x), k))
                y = x, x = left(x);
            else
                x = right(x);
        }

        iterator j = iterator(y);   
        return (j == end() || key_compare(k, key(j.node))) ? end() : j;
    }

	template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key& k) const {
		link_type y = header; /* Last node which is not less than k. */
		link_type x = root(); /* Current node. */

		while (x != 0) {
			if (!key_compare(key(x), k))
				y = x, x = left(x);
			else
				x = right(x);
		}
		const_iterator j = const_iterator(y);
		return (j == end() || key_compare(k, key(j.node))) ? end() : j;
	}

    template <class K, class V, class KoV, class Cmp, class Al> template<class II>
    void rb_tree<K, V, KoV, Cmp, Al>::insert_equal(II first, II last) 
    {
        for ( ; first != last; ++first)
            insert_equal(*first);
    }

    template <class K, class V, class KoV, class Cmp, class Al> template<class II>
    void rb_tree<K, V, KoV, Cmp, Al>::insert_unique(II first, II last) 
    {
        for ( ; first != last; ++first)
            insert_unique(*first);
    }

    template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
    typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type 
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::count(const Key& k) const 
    {
        pair<const_iterator, const_iterator> p = equal_range(k);
        size_type n = 0;
        distance(p.first, p.second, n);
        return n;
    }

    template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const Key& k) {
  link_type y = header; /* Last node which is not less than k. */
  link_type x = root(); /* Current node. */

  while (x != 0) 
    if (!key_compare(key(x), k))
      y = x, x = left(x);
    else
      x = right(x);

  return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const Key& k) const {
  link_type y = header; /* Last node which is not less than k. */
  link_type x = root(); /* Current node. */

  while (x != 0) 
    if (!key_compare(key(x), k))
      y = x, x = left(x);
    else
      x = right(x);

  return const_iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(const Key& k) {
  link_type y = header; /* Last node which is greater than k. */
  link_type x = root(); /* Current node. */

   while (x != 0) 
     if (key_compare(k, key(x)))
       y = x, x = left(x);
     else
       x = right(x);

   return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(const Key& k) const {
  link_type y = header; /* Last node which is greater than k. */
  link_type x = root(); /* Current node. */

   while (x != 0) 
     if (key_compare(k, key(x)))
       y = x, x = left(x);
     else
       x = right(x);

   return const_iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
inline void
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator position) {
	link_type y = (link_type)__rb_tree_rebalance_for_erase(position.node,
		header->parent,
		header->left,
		header->right);
	destroy_node(y);
	--node_count;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type 
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const Key& x) {
  pair<iterator,iterator> p = equal_range(x);
  size_type n = 0;
  distance(p.first, p.second, n);
  erase(p.first, p.second);
  return n;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator first, 
                                                            iterator last) {
  if (first == begin() && last == end())
    clear();
  else
    while (first != last) erase(first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const Key* first, 
                                                            const Key* last) {
  while (first != last) erase(*first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
inline pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator,
            typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator>
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(const Key& k) {
  return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
}

template <class Key, class Value, class KoV, class Compare, class Alloc>
inline pair<typename rb_tree<Key, Value, KoV, Compare, Alloc>::const_iterator,
            typename rb_tree<Key, Value, KoV, Compare, Alloc>::const_iterator>
rb_tree<Key, Value, KoV, Compare, Alloc>::equal_range(const Key& k) const {
  return pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));
}
}
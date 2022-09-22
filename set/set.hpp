#ifndef SET_HPP
# define SET_HPP

#include"RedBlackT.hpp"

namespace ft
{
template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class Set
    {
        public:
            typedef T                                                                   key_type;
            typedef T                                                                   value_type;
            typedef Compare                                                             key_compare;
            typedef Compare                                                             value_compare;
            typedef Alloc                                                               allocator_type;
            typedef typename allocator_type::reference                                  reference;
            typedef typename allocator_type::const_reference                            const_reference;
            typedef typename allocator_type::pointer                                    pointer;
            typedef typename allocator_type::const_pointer                              const_pointer;
            typedef RBT_S<key_compare, allocator_type>                                    RBT_S;
            typedef typename RBT_S::iterator                                              iterator;
            typedef typename RBT_S::const_iterator                                        const_iterator;
            typedef typename RBT_S::reverse_iterator                                      reverse_iterator;
            typedef typename RBT_S::const_reverse_iterator                                const_reverse_iterator;
            typedef std::ptrdiff_t                                                      difference_type;
            typedef size_t                                                              size_type;

            explicit Set (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()):_tree(comp)
            {
                (void)comp; (void)alloc;
            }
            template <class InputIterator>
            Set (InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()):_tree(comp)
            {
                (void)comp; (void)alloc;
                _tree.insert(first, last);
            }
            Set (const Set& x) {*this = x;}
            ~Set(void){}
            Set& operator= (const Set& x)
            {
                _tree = x._tree;
                return (*this);
            }
            //Element access:
            value_type& operator[] (const key_type& k)
            {
                return (_tree[k]);
            }

            //Modifiers:
            ft::pair<iterator, bool> insert (const value_type& val)
            {
                return (_tree.insert(val));
            }
            iterator insert (iterator position, const value_type& val)
            {
                return (_tree.insert(position, val));
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                _tree.insert(first, last);
            }
            size_type erase (const key_type& k) { return (_tree.erase(k));}
            void erase (iterator position) {_tree.erase(position);}
            void erase (iterator first, iterator last){_tree.erase(first, last);}
            void swap (Set& x)
            {
                _tree.swap(x._tree);
            }
            void clear() { _tree.clear(); }

            //Iterators:
            iterator begin() { return _tree.begin(); }
            const_iterator begin() const { return _tree.begin(); }
            iterator end() { return _tree.end(); }
            const_iterator end() const { return _tree.end(); }
            reverse_iterator rbegin() { return _tree.rbegin();  }
            const_reverse_iterator rbegin() const { return _tree.rbegin(); }
            reverse_iterator rend() { return _tree.rend(); }
            const_reverse_iterator rend() const {  return _tree.rend(); }

            //Capacity:
            bool empty() const { return _tree.empty(); }
            size_type size() const { return _tree.size(); }
            size_type max_size() const { return _tree.max_size(); }

            //Observers:
            key_compare key_comp() const { return key_compare(); }
            value_compare value_comp() const {return key_compare();}

            //Operations:
            iterator find (const key_type& k)
            {
                return (_tree.find(k));
            }
            const_iterator find (const key_type& k) const
            {
                return (_tree.find(k));
            }
            size_type count (const key_type& k) const
            {
                return _tree.count(k);
            }
            iterator lower_bound (const key_type& k) { return _tree.lower_bound(k); }
            const_iterator lower_bound (const key_type& k) const { return _tree.lower_bound(k); }
            iterator upper_bound (const key_type& k) { return _tree.upper_bound(k); }
            const_iterator upper_bound (const key_type& k) const { return _tree.upper_bound(k); }
            ft::pair<iterator,iterator> equal_range (const key_type& k){ return _tree.equal_range(k);}
            ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const { return _tree.equal_range(k); }
            //Allocator:
            allocator_type get_allocator() const { return Alloc(); }
        private:
            RBT_S _tree;
    };
    // relational operators
    template< class T, class Compare, class Alloc >
    bool operator==( const ft::Set<T,Compare,Alloc>& lhs, const ft::Set<T,Compare,Alloc>& rhs )
    { return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
    
    template< class T, class Compare, class Alloc >
    bool operator!=( const ft::Set<T,Compare,Alloc>& lhs, const ft::Set<T,Compare,Alloc>& rhs )
    { return (lhs.size() != rhs.size() || !ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

    template< class T, class Compare, class Alloc >
    bool operator< ( const ft::Set<T,Compare,Alloc>& lhs, const ft::Set<T,Compare,Alloc>& rhs )
    { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

    template< class T, class Compare, class Alloc >
    bool operator<=( const ft::Set<T,Compare,Alloc>& lhs, const ft::Set<T,Compare,Alloc>& rhs )
    { return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }

    template< class T, class Compare, class Alloc >
    bool operator>( const ft::Set<T,Compare,Alloc>& lhs, const ft::Set<T,Compare,Alloc>& rhs )
    { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }

    template< class T, class Compare, class Alloc >
    bool operator>=( const ft::Set<T,Compare,Alloc>& lhs, const ft::Set<T,Compare,Alloc>& rhs )
    { return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

}

#endif

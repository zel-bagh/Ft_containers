#ifndef MAP
# define MAP

#include<functional>



template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
    class map
    {
        public:
            typedef Key                                                                 key_type;
            typedef T                                                                   mapped_type;
            typedef std::pair<const key_type,mapped_type>                                value_type;
            typedef Compare                                                             key_compare;
            typedef Alloc                                                               allocator_type;
            typedef typename allocator_type::reference                                  reference;
            typedef typename allocator_type::const_reference                            const_reference;
            typedef typename allocator_type::pointer                                    pointer;
            typedef typename allocator_type::const_pointer                              const_pointer;
            typedef ft::RBT<key_type, mapped_type, key_compare, allocator_type>         RB_Tree;
            typedef typename Alloc::template rebind<RB_Tree>::other                     tree_allocator_type;
            typedef ft::RBTNode<value_type>                                             node;
            typedef node*                                                               nodePointer;
            typedef ft::MIterator<ft::RBTNode<value_type>, RB_Tree, value_type>         iterator;
            typedef ft::MIterator<ft::RBTNode<value_type>, RB_Tree, const value_type>   const_iterator;
            typedef ft::reverse_iterator<iterator>                                      reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>                                const_reverse_iterator;
            typedef std::ptrdiff_t                                                      difference_type;
            typedef size_t                                                              size_type;
            typedef class value_compare : public std::binary_function<value_type,value_type,bool>
            {
                friend class map;
                protected:
                Compare comp;
                value_compare (Compare c) : comp(c) {}
                public:
                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;
                bool operator() (const value_type& x, const value_type& y) const
                {
                    return comp(x.first, y.first);
                }
            }   value_compare;
            explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) : _treeAlloc(tree_allocator_type())
            {
                (void)comp; (void)alloc;
                _tree = _treeAlloc.allocate(1);
                _treeAlloc.construct(_tree);
            }
            template <class InputIterator>
            map (InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : _treeAlloc(tree_allocator_type())
            {
                (void)comp; (void)alloc;
                _tree = _treeAlloc.allocate(1);
                _treeAlloc.construct(_tree);
                for (InputIterator it = first; it != last; it++)
                    _tree->insertNode(*it);
            }
            map (const map& x): _treeAlloc(tree_allocator_type()) { _tree = NULL; *this = x; }
            ~ map()
            {
                _treeAlloc.destroy(_tree);
                _treeAlloc.deallocate(_tree, 1);
            }
            map& operator= (const map& x)
            {
                if (_tree != NULL)
                {
                    _treeAlloc.destroy(_tree);
                    _treeAlloc.deallocate(_tree, 1);
                }
                _tree = _treeAlloc.allocate(1);
                _treeAlloc.construct(_tree);
                if (!x.empty())
                    this->insert(x.begin(), x.end());
                return (*this);
            }
            //Element access:
            mapped_type& operator[] (const key_type& k)
            {
                nodePointer _node = _tree->findNode(k);
                if (_node == NULL)
                    return ((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
                else
                    return (_node->vatype->second);
            }

            //Modifiers:
            ft::pair<iterator, bool> insert (const value_type& val)
            {
                ft::pair<nodePointer, bool> _inserted = _tree->insertNode(val);
                return (ft::make_pair(iterator(_inserted.first, _tree), _inserted.second));
            }
            iterator insert (iterator position, const value_type& val)
            {
                ft::pair<nodePointer, bool> _inserted = _tree->insertNode(val);
                position = iterator(_inserted.first, _tree);
                return (position);
            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last)
            {
                for (InputIterator it = first; it != last; it++)
                    _tree->insertNode(*it);
            }
            size_type erase (const key_type& k) { return (_tree->eraseNode(k) ? 1 : 0); }
            void erase (iterator position) { _tree->eraseNode(position->first); }
            void erase (iterator first, iterator last)
            {
                if (!empty())
                {
                    ft::vector<key_type> _keys;
                    for (; first != last; first++)
                        _keys.push_back((*first).first);
                    for (size_type i = 0; i < _keys.size(); i++)
                        _tree->eraseNode(_keys[i]);
                }
            }
            void swap (map& x)
            {
                RB_Tree* _tmpTree = x._tree;
                x._tree = this->_tree;
                this->_tree = _tmpTree;
            }
            void clear() { _tree->clear(); }

            //Iterators:
            iterator begin() { return (iterator(_tree->first(), _tree)); }
            const_iterator begin() const { return (const_iterator(_tree->first(), _tree)); }
            iterator end() { return (iterator(NULL, _tree, true)); }
            const_iterator end() const { return (const_iterator(NULL, _tree, true)); } //last is error
            reverse_iterator rbegin() { return (reverse_iterator(end())); }
            const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }
            reverse_iterator rend() { return (reverse_iterator(begin())); }
            const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

            //Capacity:
            bool empty() const { return (_tree->size() == 0); }
            size_type size() const { return (_tree->size()); }
            size_type max_size() const { return (_tree->max_size()); }

            //Observers:
            key_compare key_comp() const { return (_tree->key_comp()); }
            value_compare value_comp() const { return (value_compare(_tree->key_comp())); }

            //Operations:
            iterator find (const key_type& k)
            {
                nodePointer _node = _tree->findNode(k);
                return ((_node != NULL) ? iterator(_node, _tree) : end());
            }
            const_iterator find (const key_type& k) const
            {
                nodePointer _node = _tree->findNode(k);
                return ((_node != NULL) ? iterator(_node, _tree) : end());
            }
            size_type count (const key_type& k) const
            {
                nodePointer _node = _tree->findNode(k);
                return ((_node != NULL) ? 1 : 0);
            }
            iterator lower_bound (const key_type& k) { return (iterator(_tree->lower_bound(k), _tree)); }
            const_iterator lower_bound (const key_type& k) const { return (const_iterator(_tree->lower_bound(k), _tree)); }
            iterator upper_bound (const key_type& k) { return (iterator(_tree->upper_bound(k), _tree)); }
            const_iterator upper_bound (const key_type& k) const { return (const_iterator(_tree->upper_bound(k), _tree)); }
            ft::pair<iterator,iterator> equal_range (const key_type& k){ return (ft::make_pair(iterator(_tree->lower_bound(k), _tree), iterator(_tree->upper_bound(k), _tree))); }
            ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const { return (ft::make_pair(const_iterator(_tree->lower_bound(k), _tree), const_iterator(_tree->upper_bound(k), _tree))); }

            //Allocator:
            allocator_type get_allocator() const { return (_tree->get_allocator()); }
        private:
            RB_Tree* _tree;
            tree_allocator_type _treeAlloc;
    };
    //relational operators
    template< class Key, class T, class Compare, class Alloc >
    bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    { return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
    
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    { return (lhs.size() != rhs.size() || !ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

    template< class Key, class T, class Compare, class Alloc >
    bool operator< ( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    { return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    { return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
    { return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

}

#endif

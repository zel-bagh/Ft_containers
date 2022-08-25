#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE
#include<functional>
#include <stdexcept> 

template <class Key, class T, class Key_Compare, class Alloc>
class RBT
{
    public:
        typedef typename Alloc::reference   reference;
        typedef typename Alloc::pointer     pointer;
        typedef typename Alloc::value_type         value_type;
        typedef unsigned int    size_type;
    public:
        RBT(void)
        {
            root_node = NULL;
            _begin = NULL;
            _end = NULL;
        }
        RBT(const RBT& obj) {*this = obj;} // should copy
        ~RBT(void) {} /// should destruct all nodes
    public:
        const RBT& operator=(const RBT& obj)
        {
            (void)obj;
            return *this;
        }
    public:
        class RBTNode
        {
            public:
                pointer                 pair;
                bool                    is_black;
                bool                    is_begin;
                bool                    is_end;
                RBTNode*                right_child;
                RBTNode*                left_child;
                RBTNode*                parent;
            public:
                RBTNode(const reference p, RBTNode* prt, bool color) : is_black(color), parent(prt)
                {
                    Alloc allocator;
                    pair = allocator.allocate(1);
                    *pair = p;
                    right_child = NULL;
                    left_child = NULL;
                    is_begin = 0;
                    is_end = 0;
                }
                RBTNode(const RBTNode& obj) {*this = obj;}
                ~RBTNode()
                {
                    delete pair;
                }
            public:
                const RBTNode& operator=(const RBTNode& obj)
                {
                    (void)obj; //////////
                    return *this;
                }
        };
    public:
        class iterator
        {
            private:
                RBTNode* node;
                RBTNode** begin;
                RBTNode** end;
                bool to_begin;
                bool to_end;
            public:
                iterator(void)
                {
                    node = NULL;
                    begin = NULL;
                    end = NULL;
                    to_begin = 0;
                    to_end = 0;
                }
                iterator(RBTNode& obj, RBTNode** begin, RBTNode** end, bool to_begin, bool to_end)
                {
                    node = &obj;
                    this->begin = begin;
                    this->end = end;
                    this->to_begin = to_begin;
                    this->to_end = to_end;
                }
                iterator(const iterator& obj) {*this = obj;}
                ~iterator(void){}
            public:
                iterator&   operator=(const iterator& obj)
                {
                    node = obj.node;
                    begin = obj.begin;
                    end = obj.end;
                    to_begin = obj.to_begin;
                    to_end = obj.to_end;
                    return    *this;
                }
                pointer     operator->(void) {return (node->pair);}
                reference   operator*(void) {return (*(node->pair));}
                void    operator++(void);
                void    operator--(void);
        };
        class const_iterator
        {
            private:
                iterator it;
            public:
            const_iterator(void){};
            const_iterator(const const_iterator& obj){it = obj.it;}
            const_iterator(const iterator& obj){it = obj;}
            ~const_iterator(void);
            const pointer     operator->(void) {return (&(*it));}
            const reference   operator*(void) {return (*it);}
            void    operator++(void){it++;}
            void    operator--(void){it--;}
        };
        class reverse_iterator
        {
            private:
                iterator it;
            public:
            reverse_iterator(void){};
            reverse_iterator(const reverse_iterator& obj){it = obj.it;}
            reverse_iterator(const iterator& obj){it = obj;}
            ~reverse_iterator(void);
            pointer     operator->(void) {return (&(*it));}
            reference   operator*(void) {return (*it);}
            void    operator++(void){it--;}
            void    operator--(void){it++;}
        };
        class const_reverse_iterator
        {
            private:
                iterator it;
            public:
            const_reverse_iterator(void){};
            const_reverse_iterator(const reverse_iterator& obj){it = obj.it;}
            const_reverse_iterator(const iterator& obj){it = obj;}
            ~const_reverse_iterator(void);
            const pointer     operator->(void) {return (&(*it));}
            const reference   operator*(void) {return (*it);}
            void    operator++(void){it--;}
            void    operator--(void){it++;}
        };
    public: //Modifiers:
        std::pair<iterator, bool> insert(const std::pair<const Key, T>& pair);
        // void insert (iterator first, iterator last);
        bool erase(const Key& k);
        void erase(iterator position);
        void erase(iterator first, iterator last);
        void swap (RBT& x);
        void clear(void);
    public: //Iterators
        iterator begin(void);
        const_iterator begin(void) const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
    public: //capacity
        bool empty() const;
        size_type size() const;
        size_type max_size() const;
    public: //Element access:
        T& operator[] (const Key& k);
        T& at (const Key& k);
        const T& at (const Key& k) const;
    private:
        void two_adjacent_red_nodes_fixing(RBTNode* node);
        void black_node_missing_fixing(RBTNode* node, bool erase);
        void erase_rednode_nochildren(RBTNode* node);
        void erase_blacknode_oneredchildren(RBTNode* node);
    public:
        RBTNode* root_node;
        RBTNode* _begin;
        RBTNode* _end;
};

//Iterator functions=================================================================================================>

template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::iterator::operator++(void)
{
    if (!node && to_begin)
    {
        node = *begin;
        to_begin = 0;
    }
    else if (node->is_end)
    {
        node = NULL;
        to_end = 1;
    }
    else if (node->right_child)
    {
        node = node->right_child;
        while (node->left_child)
            node = node->left_child;
    }
    else
    {
        if (node->parent->left_child == node)
            node = node->parent;
        else
        {
            while (node->parent->right_child == node)
                node = node->parent;
            node = node->parent;
        }
    }
    return ;
}

template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::iterator::operator--(void)
{
    if (!node && to_end)
    {
        node = *end;
        to_end = 0;
    }
    else if (node->is_begin)
    {
        node = NULL;
        to_end = 1;
    }
    else if (node->left_child)
    {
        node = node->left_child;
        while (node->right_child)
            node = node->right_child;
    }
    else
    {
        if (node->parent->right_child == node)
            node = node->parent;
        else
        {
            while (node->parent->left_child == node)
                node = node->parent;
            node = node->parent;
        }
    }
    return ;
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::iterator RBT<Key, T, Key_Compare, Alloc>::begin(void)
{
    if (root_node)
        return (iterator(_begin, &_begin, &_end, 0, 0));
    return (iterator());
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::const_iterator RBT<Key, T, Key_Compare, Alloc>::begin(void) const
{
    if (root_node)
        return (const_iterator(iterator(_begin, &_begin, &_end, 0, 0)));
    return (const_iterator());
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::iterator RBT<Key, T, Key_Compare, Alloc>::end(void)
{
    if (root_node)
        return (iterator(NULL, &_begin, &_end, 0, 1));
    return (iterator());
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::const_iterator RBT<Key, T, Key_Compare, Alloc>::end(void) const
{
    if (root_node)
        return (const_iterator(iterator(NULL, &_begin, &_end, 0, 1)));
    return (const_iterator());
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::reverse_iterator RBT<Key, T, Key_Compare, Alloc>::rbegin(void)
{
    if (root_node)
        return (reverse_iterator(iterator(_end, &_begin, &_end, 0, 0)));
    return (reverse_iterator());
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::const_reverse_iterator RBT<Key, T, Key_Compare, Alloc>::rbegin(void) const
{
    if (root_node)
        return (const_reverse_iterator(iterator(_end, &_begin, &_end, 0, 0)));
    return (const_reverse_iterator());
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::reverse_iterator RBT<Key, T, Key_Compare, Alloc>::rend(void)
{
    if (root_node)
        return (reverse_iterator(iterator(NULL, &_begin, &_end, 1, 0)));
    return (reverse_iterator());
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::const_reverse_iterator RBT<Key, T, Key_Compare, Alloc>::rend(void) const
{
    if (root_node)
        return (const_reverse_iterator(iterator(NULL, &_begin, &_end, 1, 0)));
    return (const_reverse_iterator());
}
//Capacity=====================================================================================================================>

template <class Key, class T, class Key_Compare, class Alloc>
bool RBT<Key, T, Key_Compare, Alloc>::empty(void) const
{
    if (root_node)
        return (0);
    return (1);
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::size_type RBT<Key, T, Key_Compare, Alloc>::size(void) const
{
    unsigned int n;

    n = 0;
    if (root_node)
        return (0);
    iterator it = begin();
    iterator end = end();
    while(it != end)
    {
        n++;
        it++;
    }
    return n;
    
}

template <class Key, class T, class Key_Compare, class Alloc>
typename RBT<Key, T, Key_Compare, Alloc>::size_type RBT<Key, T, Key_Compare, Alloc>::max_size(void) const
{
    return (Alloc().max_size());
}

//Element access==============================================================================================================================>

template <class Key, class T, class Key_Compare, class Alloc>
T& RBT<Key, T, Key_Compare, Alloc>::operator[](const Key& k)
{
    T value;

    return ((*(insert(std::pair<Key, T>(k, value)).first)).second);
}

template <class Key, class T, class Key_Compare, class Alloc>
T& RBT<Key, T, Key_Compare, Alloc>::at(const Key& k)
{
    iterator it = begin();
    iterator end = end();
    Key_Compare compare;
    
    while (it != end)
    {
        if (compare((*it).first, k) == 0 && compare(k, (*it).first) == 0)
            return ((*it).second);
        it++;
    }
    throw (std::out_of_range("key not found"));
}

//Modifiers==============================================================================================================================>

template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::swap(RBT& x)
{
    RBTNode* tmp;

    tmp = root_node;
    root_node = x.root_node;
    x.root_node = tmp;
    tmp = _begin;
    _begin = x._begin;
    x._begin = tmp;
    tmp = _end;
    _end = x._end;
    x._end = tmp;
}

template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::clear(void)
{
    iterator it = begin();
    iterator end = end();
    erase(it, end);
}

template <class Key, class T, class Key_Compare, class Alloc>
std::pair<typename RBT<Key, T, Key_Compare, Alloc>::iterator, bool> RBT<Key, T, Key_Compare, Alloc>::insert(const std::pair<const Key, T>& pair)
{
    value_type pr;
    RBTNode    *node;
    Key_Compare compare;

    pr.first = pair.first;
    pr.second = pair.second;
    if (root_node == NULL)
    {
        root_node = new RBTNode(pr, 0, 1);
        root_node->is_end = 1;
        root_node->is_begin = 1;
        _end = root_node;
        _begin = root_node;
        return (std::pair<iterator, bool> (iterator(*root_node), 1));
    }
    else
    {
        node = root_node;
        while (1)
        {
            if (compare(pr.first, node->pair->first) == 1)
            {
                if (node->left_child == NULL)
                {
                    node->left_child = new RBTNode(pr, node, 0);
                    node = node->left_child;
                    break ;
                }
                    node = node->left_child;
            }
            else if (compare(node->pair->first, pr.first) == 1)
            {
                if (node->right_child == NULL)
                {
                    node->right_child = new RBTNode(pr, node, 0);
                    node = node->right_child;
                    break ;
                }
                    node = node->right_child;
            }
            else
                return (std::pair<iterator, bool> (iterator(*node), 0));
        }
        if (node->parent->right_child == node && node->parent->is_end)
        {
            node->parent->is_end = 0;
            node->is_end = 1;
            _end = node;
        }
        else if (node->parent->left_child == node && node->parent->is_begin)
        {
            node->parent->is_begin = 0;
            node->is_begin = 1;
            _begin = node;
        }
        if (node->parent->is_black)
            return (std::pair<iterator, bool> (iterator(*node), 1));
        two_adjacent_red_nodes_fixing(node);
        return (std::pair<iterator, bool> (iterator(*node), 1));
    }
}
template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::two_adjacent_red_nodes_fixing(RBTNode* node)
{
    if (node->parent->parent->left_child == node->parent)
    {
        if (node->parent->parent->right_child && !node->parent->parent->right_child->is_black)
        {
            node->parent->parent->right_child->is_black = 1;
            node->parent->is_black = 1;
            if (node->parent->parent->parent == NULL)
                return ;
            node->parent->parent->is_black = 0;
            if (!node->parent->parent->parent->is_black)
                two_adjacent_red_nodes_fixing(node->parent->parent);
            return ;
        }
        else if (node->parent->left_child == node)
        {
            node->parent->parent->left_child = node->parent->right_child;
            if (node->parent->right_child)
                node->parent->right_child->parent = node->parent->parent;
            node->parent->parent->is_black = 0;
            node->parent->right_child = node->parent->parent;
            node->parent->is_black = 1;
            node->parent->parent = node->parent->parent->parent;
            if (node->parent->parent == NULL)
                root_node = node->parent;
            node->parent->right_child->parent = node->parent;
            if (node->parent->parent)
            {
                if (node->parent->parent->left_child == node->parent->right_child)
                    node->parent->parent->left_child = node->parent;
                else
                    node->parent->parent->right_child = node->parent;
            }
            return ;
        }
        else
        {
            node->parent->parent->left_child = node->right_child;
            if (node->right_child)
                node->right_child->parent = node->parent->parent;
            node->parent->parent->is_black = 0;
            node->parent->right_child = node->left_child;
            if (node->left_child)
                node->left_child->parent = node->parent;
            node->is_black = 1;
            node->right_child = node->parent->parent;
            node->left_child = node->parent;
            node->left_child->parent = node;
            node->parent = node->right_child->parent;
            if (node->parent == NULL)
                root_node = node;
            node->right_child->parent = node;
            if (node->parent)
            {
                if (node->parent->left_child == node->right_child)
                    node->parent->left_child = node;
                else
                    node->parent->right_child = node;
            }
            return ;
        }
    }
    else
    {
        if (node->parent->parent->left_child && !node->parent->parent->left_child->is_black)
        {
            node->parent->parent->left_child->is_black = 1;
            node->parent->is_black = 1;
            if (node->parent->parent->parent == NULL)
                return ;
            node->parent->parent->is_black = 0;
            if (!node->parent->parent->parent->is_black)
                two_adjacent_red_nodes_fixing(node->parent->parent);
            return ;
        }
        else if (node->parent->right_child == node)
        {
            node->parent->parent->right_child = node->parent->left_child;
            if (node->parent->left_child)
                node->parent->left_child->parent = node->parent->parent;
            node->parent->parent->is_black = 0;
            node->parent->left_child = node->parent->parent;
            node->parent->is_black = 1;
            node->parent->parent = node->parent->parent->parent;
            if (node->parent->parent == NULL)
                root_node = node->parent;
            node->parent->left_child->parent = node->parent;
            if (node->parent->parent)
            {
                if (node->parent->parent->left_child == node->parent->left_child)
                    node->parent->parent->left_child = node->parent;
                else
                    node->parent->parent->right_child = node->parent;
            }
            return ;
        }
        else
        {
            node->parent->parent->right_child = node->left_child;
            if (node->left_child)
                node->left_child->parent = node->parent->parent;
            node->parent->parent->is_black = 0;
            node->parent->left_child = node->right_child;
            if (node->right_child)
                node->right_child->parent = node->parent;
            node->is_black = 1;
            node->left_child = node->parent->parent;
            node->right_child = node->parent;
            node->right_child->parent = node;
            node->parent = node->left_child->parent;
            if (node->parent == NULL)
                root_node = node;
            node->left_child->parent = node;
            if (node->parent)
            {
                if (node->parent->left_child == node->left_child)
                    node->parent->left_child = node;
                else
                    node->parent->right_child = node;
            }
            return ;
        }
    }
}

template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::erase_rednode_nochildren(RBTNode* node)
{
    if (node->parent->left_child == node)
        node->parent->left_child = NULL;
    else
        node->parent->right_child = NULL;
    delete node;
}


template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::erase_blacknode_oneredchildren(RBTNode* node)
{
    if (!node->parent)
    {
        root_node = (node->right_child)? node->right_child : node->left_child;
        root_node->is_begin = 1;
        root_node->is_end = 1;
        root_node->is_black = 1;
        root_node->parent = NULL;
        _begin = root_node;
        _end = root_node;
    }
    else if (node->parent->right_child == node)
    {
        if (node->right_child)
        {
            node->parent->right_child = node->right_child;
            node->right_child->parent = node->parent;
            node->right_child->is_black = 1;
        }
        else
        {
            node->parent->right_child = node->left_child;
            node->left_child->parent = node->parent;
            node->left_child->is_black = 1;
            node->left_child->is_end = node->is_end;
            _end = (node->is_end)? node->left_child : _end;
        }
    }
    else
    {
        if (node->right_child)
        {
            node->parent->left_child = node->right_child;
            node->right_child->parent = node->parent;
            node->right_child->is_black = 1;
            node->right_child->is_begin = node->is_begin;
            _begin = (node->is_begin)? node->right_child : _begin;
        }
        else
        {
            node->parent->left_child = node->left_child;
            node->left_child->parent = node->parent;
            node->left_child->is_black = 1;
        }     
    }
    delete node;
}

template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::black_node_missing_fixing(RBTNode* node, bool erase)
{
    RBTNode *parent;

    parent = node->parent;
    if (parent->left_child == node)
    {
        if (parent->right_child->is_black)
        {
            if ((parent->right_child->left_child && parent->right_child->left_child->is_black && parent->right_child->right_child && parent->right_child->right_child->is_black)
            ||(!parent->right_child->left_child && !parent->right_child->right_child))
            {
                parent->right_child->is_black = 0;
                if (erase)
                {
                    parent->left_child = NULL;
                    delete (node);
                }
                if (parent->is_black && parent->parent)
                    black_node_missing_fixing(parent, 0);
                else
                    parent->is_black = 1;
            }
            else if (parent->right_child->right_child && !parent->right_child->right_child->is_black)
            {
                parent->right_child->is_black = parent->is_black;
                parent->is_black = 1;
                parent->right_child->parent = parent->parent;
                if (parent->parent)
                {
                    if (parent->parent->right_child == parent)
                        parent->parent->right_child = parent->right_child;
                    else
                        parent->parent->left_child = parent->right_child;
                }
                else
                    root_node = parent->right_child;
                parent->parent = parent->right_child;
                parent->right_child = parent->right_child->left_child;
                parent->parent->left_child = parent;
                if (parent->right_child)
                    parent->right_child->parent = parent;
                parent->parent->right_child->is_black = 1;
                if (erase) 
                {
                    parent->left_child = NULL;
                    delete node;
                }
            }
            else if (parent->right_child->left_child && !parent->right_child->left_child->is_black &&
                (!parent->right_child->right_child || (parent->right_child->right_child && parent->right_child->right_child->is_black)))
            {
                parent->right_child->left_child->is_black = 1;
                parent->right_child->is_black = 0;
                parent->right_child->left_child->parent = parent;
                parent->right_child->parent = parent->right_child->left_child;
                parent->right_child->left_child = parent->right_child->left_child->right_child;
                if (parent->right_child->left_child)
                    parent->right_child->left_child->parent = parent->right_child;
                parent->right_child->parent->right_child = parent->right_child;
                parent->right_child = parent->right_child->parent;
                black_node_missing_fixing(node, 0);
            }
        }
        else
        {
            parent->is_black = 0;
            parent->right_child->is_black = 1;
            parent->right_child->parent = parent->parent;
            if (parent->parent)
            {
                if (parent->parent->left_child == parent)
                    parent->parent->left_child = parent->right_child;
                else
                    parent->parent->right_child = parent->right_child;
            }
            else
                root_node = parent->right_child;
            parent->parent = parent->right_child;
            parent->right_child = parent->right_child->left_child;
            parent->right_child->parent = parent;
            parent->parent->left_child = parent;
            black_node_missing_fixing(node, erase);
        }
    }
    else if (parent->right_child == node)
    {
        if (parent->left_child->is_black)
        {
            if ((parent->left_child->left_child && parent->left_child->left_child->is_black && parent->left_child->right_child && parent->left_child->right_child->is_black)
            ||(!parent->left_child->left_child && !parent->left_child->right_child))
            {
                parent->left_child->is_black = 0;
                if (erase)
                {
                    parent->right_child = NULL;
                    delete (node);
                }
                if (parent->is_black && parent->parent)
                    black_node_missing_fixing(parent, 0);
                else
                    parent->is_black = 1;
            }
            else if (parent->left_child->left_child && !parent->left_child->left_child->is_black)
            {
                parent->left_child->is_black = parent->is_black;
                parent->is_black = 1;
                parent->left_child->parent = parent->parent;
                if (parent->parent)
                {
                    if (parent->parent->right_child == parent)
                        parent->parent->right_child = parent->left_child;
                    else
                        parent->parent->left_child = parent->left_child;
                }
                else
                    root_node = parent->left_child;
                parent->parent = parent->left_child;
                parent->left_child = parent->left_child->right_child;
                parent->parent->right_child = parent;
                if (parent->left_child)
                    parent->left_child->parent = parent;
                parent->parent->left_child->is_black = 1;
                if (erase)
                {
                    parent->right_child = NULL;
                    delete node;
                }
            }
            else if (parent->left_child->left_child && !parent->left_child->left_child->is_black &&
                (!parent->left_child->right_child || (parent->left_child->right_child && parent->left_child->right_child->is_black)))
            {
                parent->left_child->right_child->is_black = 1;
                parent->left_child->is_black = 0;
                parent->left_child->right_child->parent = parent;
                parent->left_child->parent = parent->left_child->right_child;
                parent->left_child->right_child = parent->left_child->right_child->left_child;
                if (parent->left_child->right_child)
                    parent->left_child->right_child->parent = parent->left_child;
                parent->left_child->parent->left_child = parent->left_child;
                parent->left_child = parent->left_child->parent;
                black_node_missing_fixing(node, 0);
            }
        }
        else
        {
            parent->is_black = 0;
            parent->left_child->is_black = 1;
            parent->left_child->parent = parent->parent;
            if (parent->parent)
            {
                if (parent->parent->left_child == parent)
                    parent->parent->left_child = parent->left_child;
                else
                    parent->parent->right_child = parent->left_child;
            }
            else
                root_node = parent->left_child;
            parent->parent = parent->left_child;
            parent->left_child = parent->left_child->right_child;
            parent->left_child->parent = parent;
            parent->parent->right_child = parent;
            black_node_missing_fixing(node, erase);
        }
    }
}

template <class Key, class T, class Key_Compare, class Alloc>
bool RBT<Key, T, Key_Compare, Alloc>::erase(const Key& k)
{
    Key_Compare compare;
    RBTNode *node = root_node;
    RBTNode *rnode;
    bool color;
    if (!node)
        return (0);
    while (compare(k, node->pair->first) || compare(node->pair->first, k))
    {
        node = (compare(k, node->pair->first))? node->left_child : node->right_child;
        if (!node)
            return (0);
    }
    if (!node->right_child && !node->left_child)
    {
        if (!node->parent)
        {
            root_node = NULL;
            _begin = NULL;
            _end = NULL;
            delete node;
        }
        else
        {
            if (node->is_begin)
            {
                node->parent->is_begin = 1;
                _begin =  node->parent;
            }
            else if (node->is_end)
            {
                node->parent->is_end = 1;
                _end = node->parent;
            }
            if (!node->is_black)
                erase_rednode_nochildren(node);
            else
                black_node_missing_fixing(node, 1);
        }
    }
    else if (node->right_child && node->left_child)
    {
        rnode = node->right_child;
        while (rnode->left_child)
            rnode = rnode->left_child;
        RBTNode *tmp;
        tmp = rnode->parent;
        rnode->parent = node->parent;
        if (node->parent)
        {
            if (node->parent->right_child == node)
                node->parent->right_child = rnode;
            else
                node->parent->left_child = rnode;
        }
        else
            root_node = rnode;
        if (node->right_child == rnode)
        {
            node->parent = rnode;
            node->right_child = rnode->right_child;
            if (node->right_child)
                node->right_child->parent = node;
            rnode->right_child = node;
            rnode->left_child = node->left_child;
            rnode->left_child->parent = rnode;
            node->left_child = NULL;
            color = node->is_black;
            node->is_black = rnode->is_black;
            rnode->is_black = color;
        }
        else
        {
            rnode->left_child = node->left_child;
            rnode->left_child->parent = rnode;
            node->left_child = NULL;
            node->parent = tmp;
            node->parent->left_child = node;
            tmp = rnode->right_child;
            rnode->right_child = node->right_child;
            rnode->right_child->parent = rnode;
            node->right_child = tmp;
            if (node->right_child)
                node->right_child->parent = node;
            color = node->is_black;
            node->is_black = rnode->is_black;
            rnode->is_black = color;
        }
        if (!node->is_black)
            erase_rednode_nochildren(node);
        else if (node->right_child)
            erase_blacknode_oneredchildren(node);
        else
            black_node_missing_fixing(node, 1);
    }
    else
        erase_blacknode_oneredchildren(node);
    return (1);
}

template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::erase(iterator position)
{
    erase(position->first);
}

template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::erase(iterator first, iterator last)
{
    iterator next;

    while (first != last)
    {
        next = first++;
        first--;
        erase(first->first);
        first = next;
    }
}

#endif
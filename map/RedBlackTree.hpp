#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE
#include<functional>

template <class Key, class T, class Key_Compare, class Alloc>
class RBT
{
    public:
        typedef typename Alloc::reference   reference;
        typedef typename Alloc::pointer     pointer;
        typedef typename Alloc::_Tp         value_type;
    public:
        RBT(void) {root_node = NULL;}
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
                RBTNode*                right_child;
                RBTNode*                left_child;
                RBTNode*                parent;
            public:
                RBTNode(const reference p, RBTNode& prt, bool color) : is_black(color), parent(&prt)
                {
                    Alloc allocator;
                    this->pair = allocator.allocate(1);
                    this->pair[0] = pair;
                    right_child = NULL;
                    left_child = NULL;
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
            public:
                iterator(void) {node = NULL;}
                iterator(const RBTNode& obj){node = &obj;}
                iterator(const iterator& obj) {*this = obj;}
                ~iterator(void){}
            public:
                const reference   operator=(const iterator& obj)
                {
                    node = obj.node;
                    return    *this;
                }
                reference   operator->(void) {return (*(node->pair));}
                reference   operator*(void) {return (*(node->pair));}
        };
    public:
        std::pair<iterator, bool> insert(const std::pair<const Key, T>& pair);
        void erase(const Key& k);
    private:
        void two_adjacent_red_nodes_fixing(RBTNode* node);
        void black_node_missing_fixing(RBTNode* node, bool erase);
        void erase_rednode_nochildren(RBTNode* node);
        void erase_balcknode_oneredchildren(RBTNode* node);
    private:
        RBTNode* root_node;
};

template <class Key, class T, class Key_Compare, class Alloc>
std::pair<typename RBT<Key, T, Key_Compare, Alloc>::iterator, bool> RBT<Key, T, Key_Compare, Alloc>::insert(const std::pair<const Key, T>& pair)
{
    value_type pr;
    RBTNode    *node;
    Key_Compare compare;

    pr.first = pair.first;
    pr.second = pair.second;
    if (root_node == NULL) // create root node
        root_node = new RBTNode(pr, 0, 1);
    else
    {
        node = root_node;
        while (1)
        {
            if (compare(pr.first, node->pair->first) == 1)
            {
                if (node->left_child == NULL)
                {
                    node->left_child = new RBTNode(pr, *node, 0);
                    node = node->left_child;
                    break ;
                }
                    node = node->left_child;
            }
            else if (compare(node->pair->first, pr.first) == 1)
            {
                if (node->right_child == NULL)
                {
                    node->right_child = new RBTNode(pr, *node, 0);
                    node = node->right_child;
                    break ;
                }
                    node = node->right_child;
            }
            else
                return (std::pair<iterator, bool> (iterator(*node), 0));
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
            node->parent->right_child->parent = node->parent;
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
            node->right_child->parent = node;
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
            node->parent->left_child->parent = node->parent;
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
            node->left_child->parent = node;
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
void RBT<Key, T, Key_Compare, Alloc>::erase_balcknode_oneredchildren(RBTNode* node)
{
    *(node->pair) = (node->right_child)? *(node->right_child->pair) : *(node->left_child->pair);
    if (node->right_child)
    {
        delete node->right_child;
        node->right_child = NULL;
    }
    else
    {
        delete node->left_child;
        node->left_child = NULL;
    }
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
            }

        }
    }
}

template <class Key, class T, class Key_Compare, class Alloc>
void RBT<Key, T, Key_Compare, Alloc>::erase(const Key& k)
{
    Key_Compare compare;
    RBTNode node = root_node;
    RBTNode rnode;
    if (!node)
        return;
    while (compare(k, node->pair->first) || compare(node->pair->first, k))
    {
        node = (compare(k, node->pair->first))? node->left_child : node->right_child;
        if (!node)
            return;
    }
    if (!node->right_child && !node->left_child)
    {
        if (!node->is_black)
            erase_rednode_nochildren(node);
        else if (!node.parent)
        {
            root_node == NULL;
            delete node;
        }
        else
            black_node_missing_fixing(node, 1);
    }
    else if (node->right_child && node->left_child)
    {
        rnode = node->right_child;
        while (rnode->left_child)
            rnode = rnode->left_child;
        *(node->pair) = *(rnode->pair);
        if (!rnode->is_black)   
            erase_rednode_nochildren(rnode);
        else if (rnode->right_child)
            erase_balcknode_oneredchildren(rnode);
        else
            black_node_missing_fixing(rnode, 1);
    }
    else
        erase_balcknode_oneredchildren(node);
}





#endif
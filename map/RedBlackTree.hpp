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
                bool                    is_root;
                bool                    is_black;
                RBTNode*                right_child;
                RBTNode*                left_child;
                RBTNode*                parent;
            public:
                RBTNode(const reference pair)
                {
                    Alloc allocator;
                    this->pair = allocator.allocate(1);
                    this->pair[0] = pair;
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
                iterator(const RBTNode& obj){node = &obj};
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
    private:
        RBTNode* root_node;
};

template <class Key, class T, class Key_Compare, class Alloc>
std::pair<typename RBT<Key, T, Key_Compare, Alloc>::iterator, bool> RBT<Key, T, Key_Compare, Alloc>::insert(const std::pair<const Key, T>& pair)
{
    bool       r;
    value_type pr;
    RBTNode    *node;
    Key_Compare compare;
    iterator    it;
    std::pair<iterator, bool> return_value;

    pr.first = pair.first;
    pr.second = pair.second;
    if (root_node == NULL) // create root node
    {
        root_node = new RBTNode(pr);
        root_node->is_black = 1;
        root_node->is_root = 1;
        root_node->left_child = NULL;
        root_node->right_child = NULL;
        root_node->parent = NULL;
    }
    else
    {
        node = root_node;
        while (1)
        {
            r = compare(pr.first, node->pair->first);
            if (compare(pr.first, node->pair->first) == 1)
            {
                if (node->left_child == NULL)
                {
                    node->left_child = new RBTNode(pr);
                    break ;
                }
                    node = node->left_child;
            }
            else if (compare(node->pair->first, pr.first) == 1)
            {
                if (node->right_child == NULL)
                {
                    node->right_child = new RBTNode(pr);
                    break ;
                }
                    node = node->right_child;  
            }
            else
                return (std::pair<iterator, bool> (iterator(*node), 0));
        }
        
    }
} 






#endif
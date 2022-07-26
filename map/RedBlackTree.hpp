#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE
#include<functional>

template <class Key, class T, class Key_Compare, class Alloc>
class RBT
{
    public:
        typedef typename Alloc::reference   reference;
        typedef typename Alloc::pointer     pointer;
    private:
        RBTNode* root_node;
    public:
        RBT(void) {root_node = NULL;}
        RBT(const RBT& obj) {*this = obj;}
        ~RBT(void) {}
    public:
        const RBT& operator=(const RBT& obj)
        {
            (void)obj;
            return *this;
        }
    public:
        std::pair<typename RBT::iterator, bool> insert(const std::pair<const Key, T>& pair);
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
                    (void)obj;
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

};

template <class Key, class T, class Key_Compare, class Alloc>
std::pair<typename RBT<Key, T, Key_Compare, Alloc>::iterator, bool> RBT<Key, T, Key_Compare, Alloc>::insert(const std::pair<const Key, T>& pair)
{
    
} 






#endif
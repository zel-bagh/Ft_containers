#include<memory>
#include<iostream>
#include<map>
#include"test.hpp"
#include"RedBlackTree.hpp"


class test
{
    public:
        int c;
    test()
    {c = 0;}
    test operator++(int)
    {
        test tmp;
        tmp.c = c;
        c++;
        return tmp;
    }
    test& operator++(void)
    {c++;return *this;}
    bool operator==(test& obj)
    {
        return (c == obj.c);
    }
};

int main()
{
    // RBT<int, int, std::less<int>, std::allocator<std::pair<int, int> > > rbt;

    // std::pair<int,int> p(50,50);
    //     std::pair<int,int> r(100,100);
    // std::pair<int,int> f(25,25);
    //     std::pair<int,int> e(500,500);




    // rbt.insert(p);
    // std::cout << rbt.root_node->pair->first << std::endl;

    // rbt.insert(r);
    // rbt.insert(f);
    //     rbt.insert(e);
    //     std::cout << rbt.root_node->pair->first << std::endl;
    // rbt.erase(25);
    //         std::cout << rbt.root_node->pair->first << std::endl;

    // std::map<int,int> m;
    // m.insert(std::pair<int,int>(100, 100));
    // std::map<int, int>::iterator it = m.begin();
    // std::map<int, int>::iterator end = m.end();
    // if (it++ == end)
    //     std::cout << "it got incremented before comparison" << std::endl;

    test t;
    test o;

    if (t++ == o)
        std::cout << "comparison before incrementation" << std::endl;
    
}
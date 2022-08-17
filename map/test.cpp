#include<memory>
#include<iostream>
#include<map>
#include"test.hpp"
#include"RedBlackTree.hpp"


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

    std::map<int,int> m;
    // m.insert(std::pair<int,int>(100, 100));
    //     m.insert(std::pair<int,int>(25, 25));

    // m.insert(std::pair<int,int>(500, 500));

    std::map<int,int>::iterator it = m.begin();
    




    std::cout << (*it).first;


    
}
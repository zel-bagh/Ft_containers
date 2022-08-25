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
    m.insert(std::pair<int,int>(100, 100));
    //     m.insert(std::pair<int,int>(25, 25));

    // m.insert(std::pair<int,int>(500, 500));
    // m.insert(std::pair<int,int>(50, 50));

    // std::map<int,int>::iterator it = m.begin();
    
    // m.erase(it);
    // std::cout <<  it->first;

    // std::map<int,int> n;
    // n.insert(std::pair<int,int>(200, 200));
    // std::map<int, int>::iterator it = n.begin();
    // it++;
    // it--;
    // std::cout << it->first << std::endl;
    // it++;
    // std::map<int, int>::iterator ti = m.begin();
    // m.swap(n);

    // it--;
    //  std::cout << it->first;
    try
    {
    m.at(4);
    }
    catch(std::out_of_range& a)
    {
        std::cout << a.what();
    }





    
}
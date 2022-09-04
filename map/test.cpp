#include<memory>
#include<iostream>
#include<map>
#include"test.hpp"
#include"map.hpp"
#include<unistd.h>


// class test
// {
//     public:
//         int c;
//     test()
//     {c = 0;}
//     test operator++(int)
//     {
//         test tmp;
//         tmp.c = c;
//         c++;
//         return tmp;
//     }
//     test& operator++(void)
//     {c++;return *this;}
//     int operator*(void)
//     {
//         return (c);
//     }
// };


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

    // test t;
    // test o;


    ft::Map<int, int> m;
    int i = 0;
    while (++i <= 15)
        m.insert(std::pair<const int, int>(i, i));
    ft::Map<int, int>::iterator it = m.begin();
    ft::Map<int, int>::iterator end = m.end();
    m.erase(15);
    m.erase(11);
     m.erase(9);
    m.erase(4);
    m.erase(3);

    // m.erase(88);
    // m.erase(99);
    it = m.begin();
    end = m.end();
    ft::Map<int, int>::iterator tmp;
    while(it != end)
    {
        tmp = ++it; it--;
        std::cout << "deleting " << it->first << std::endl;
        m.erase(it->first);
        std::cout << "deleted" << std::endl;
        it = tmp;
    }
    it.show();

}
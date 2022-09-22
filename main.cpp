#include"map/map.hpp"
#include"vector/vector.hpp"
#include"set/set.hpp"
#include"stack/stack.hpp"
#include<map>
#include<set>
#include<vector>
#include<stack>
#include <iterator>


int main(void)
{
    std::cout << "================Comparing iterator and const_iterator=================" << std::endl;
    {
        ft::Vector<int> v(5,5);
        ft::Vector<int>::iterator it = v.begin();
        ft::Vector<int>::const_iterator c_it = v.begin();
        std::cout << (c_it == it) << std::endl;
    }
    std::cout << "==============Testing Vector swap======================================" << std::endl;
    {
        ft::Vector<int> v(5,5);
        ft::Vector<int> w(5,6);
        ft::Vector<int>::iterator v_it = v.begin();
        ft::Vector<int>::iterator w_it = w.begin();
        std::cout << "           ==before swap==" << std::endl;
        std::cout << "*v_it = " << *v_it << "   and    *w_it = " << *w_it << std::endl;
        v.swap(w);
        ft::Vector<int>::iterator v_it1 = v.begin();
        ft::Vector<int>::iterator w_it1 = w.begin();
        std::cout << "           ==after swap==" << std::endl;
        std::cout << "*v_it1 = " << *v_it1 << "   and    *w_it1 = " << *w_it1 << std::endl;

        std::cout << "*v_it = " << *v_it << "   and    *w_it = " << *w_it << std::endl;
    }
    std::cout << "==============Testing map======================================" << std::endl;
    {
        ft::Map<int, int> m;
        m.insert(ft::make_pair(1,1));
        m.insert(ft::make_pair(1,2));
        std::cout << "m[1] = "<< m[1] << std::endl;
        for(int i = 100; i > 0; i--)
            m.insert(ft::make_pair(i, i));
        ft::Map<int, int>::iterator it = m.begin();
        ft::Map<int, int>::iterator end = m.end();
        while (it != end)
        {
            std::cout << it->first << std::endl;
            it++;
        }
        std::cout << "==========testing iterator validation============" << std::endl;
        it = m.begin();
        m.insert(ft::make_pair(101,101));
        m.erase(100);
        std::cout << "it = " << it->first << std::endl;
        std::cout << "===========swaping===============" << std::endl;
        ft::Map<int, int> M;
        M.swap(m);
        std::cout << "M size now is = " << M.size() << " from " << M.begin()->first << "  to  " << (--M.end())->first << std::endl;
        std::cout << "m size is = " << m.size() << std::endl;
    }
    // system("leaks a.out");
}
#include<memory>
#include<iostream>
#include<map>
#include"map.hpp"
#include<unistd.h>
#include<iterator>
#include<vector>
#include"vector.hpp"
#include"tools.hpp"
#include<time.h>
#include <ctime>
#include <sys/time.h>

void  show(std::vector<int>& v)
{
   std::cout << "==========vector element are============ " << std::endl;
   std::vector<int>::iterator it = v.begin();
   std::vector<int>::iterator end = v.end();

   while (it != end)
      std::cout << *(it++) << std::endl;
   std::cout << "========================================="<< std::endl;
}

template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };
int main()
{
/*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::Vector<std::string>::size_type s, ft_s;
        ft::Vector<std::string>::size_type c, ft_c;
        /*
         * bool to store the comparison
         */
        bool cond = 1;
        {
            std::vector<std::string> v1(3, "hello");
            std::vector<std::string> v(3, "string");
            ft::Vector<std::string> ft_v(3, "string");
            ft::Vector<std::string>::iterator valid_it;

            v.reserve(6);
            ft_v.reserve(6);
            valid_it = ft_v.begin();
            v.insert(v.begin() + 1, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 1, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            std::cout << s << " " << ft_s << " " << c << " " << ft_c << std::endl;
            for (size_t i = 0; i < v.size(); ++i)
            {
                
                // if (i == 14 || i == 15)
                // {
                //     std::cout << "==="<< std::endl;
                //     std::cout << v[i] << std::endl;
                // }
                str += v[i];
            }
            // std::cout << str << std::endl;
            for (size_t i = 0; i < ft_v.size(); ++i)
            {
                // if (i == 14 || i == 15)
                // {
                //     std::cout << "==="<< std::endl;
                //     std::cout << ft_v[i] << std::endl;
                // }
                ft_str += ft_v[i];
            }
            std::cout << "====" << std::endl << str << std::endl << ft_str << std::endl;
            // std::cout << (str == ft_str) << std::endl;
            // std::cout << (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
        }
}

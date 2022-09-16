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
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(1, "string2");
        std::vector<std::string> const v2(10, "string2");
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::Vector<std::string> ft_v1(10, "string2");
        ft::Vector<std::string> const ft_v2(10, "string2");
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        std::vector<std::string>::reverse_iterator it = v1.rbegin();
         std::cout <<  *(it);
      //   for (std::vector<std::string>::reverse_iterator rit = v1.rbegin(); rit != v1.rend(); ++rit) // fill res from v1
      //       res += *rit;
      //   for (std::vector<std::string>::const_reverse_iterator rit = v2.rbegin(); rit != v2.rend(); ++rit) // fill c_res from const v1
      //       c_res += *rit;

      //   for (ft::Vector<std::string>::reverse_iterator rit = ft_v1.rbegin(); rit != --ft_v1.rend(); ++rit) // fill ft_res from ft_v1
      //       ft_res += *rit;
      //   for (ft::Vector<std::string>::const_reverse_iterator rit = ft_v2.rbegin(); rit != ft_v2.rend(); ++rit) // fill c_ft_res from const ft_v1
      //       c_ft_res += *rit;


}

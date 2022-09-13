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
template <class T>
void to(T& a)
{
   a.~T();
}
class test
{
   public:
   int a;
   test(){a = 7;}
   ~test(){std::cout << "test destructor" << std::endl;}
};

int main()
{
      int t[11] = {0,1,2,3,100,5,6,7,8,9,10};
      int p[11] = {1,100,6,103,104,105,106,107,108,109,110};

   std::vector<int> v (t, t + 10);
   v.insert(v.end(), 252);
   // std::cout << v.begin().base() << std::endl;
   v.erase(--v.begin(), v.end());
   // std::cout << v.begin().base() << std::endl;
   // show(v);


   // std::cout << v.capacity() << std::endl;
   // std::cout << v.size() << std::endl;

}

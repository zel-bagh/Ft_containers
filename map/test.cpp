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

void hola(void)
{
   std::allocator<int> alo;
   int *p = new int[4];

}

int main()
{
   //    int t[11] = {0,1,2,3,100,5,6,7,8,9,10};
   //    int p[11] = {100,101,102,103,104,105,106,107,108,109,110};

   // std::vector<int> w(5,5);
   // w.insert(w.end(), 9);
   // std::vector<int> v(w);
   std::vector<int> v(5,5);
      std::cout << v.capacity() << std::endl;
   std::cout << v.size() << std::endl;
   show(v);
   v.insert(v.end(), 1);
         std::cout << v.capacity() << std::endl;
   std::cout << v.size() << std::endl;
   show(v);
   v.insert(v.begin(), 6);
         std::cout << v.capacity() << std::endl;
   std::cout << v.size() << std::endl;
   show(v);


   
   // 
   // std::vector<int> w(p, p+5);
   // std::vector<int>::iterator i = it;
   // v.insert(it , t, t+10);
   // std::vector<int>::iterator end = v.end();
   // std::vector<int>::iterator e = end;
   // std::cout << *(--e);
   // v.insert(v.end(), t, t+1);
   //    std::vector<int>::iterator oo;

   // v.insert(oo, t, t+1);

   // std::cout << *(--end);
   // --it;
   //  std::cout << "===" << *(v.end()) << std::endl;
   // std::cout << v.capacity() << std::endl;
   // std::cout << v.size() << std::endl;
   // it = (v.end());
   //  std::cout << *(it);
   // v.insert(it, t, t+1);
   // show(v);
   // std::cout << v.capacity() << std::endl;
   // std::cout << v.size() << std::endl;
}

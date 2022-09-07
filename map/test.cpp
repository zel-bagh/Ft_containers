#include<memory>
#include<iostream>
#include<map>
// #include"map.hpp"
#include<unistd.h>
#include<iterator>
#include<vector>
// #include"tools.hpp"

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
int main () {
  std::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);	// myvector: 0 1 2 3 4 5 6 7 8 9

  typedef std::vector<int>::iterator iter_type;

  std::reverse_iterator<iter_type> rev_it;

  rev_it = myvector.end();
//   std::cout << *(rev_it+1);
  std::cout << *rev_it;

  std::cout << "The fourth element from the end is: " << *rev_it << '\n';

  return 0;
}

// int main()
// {
//  std::map<int, int> m;
//  m.insert(std::pair<int, int>(1,1));
//  m.insert(std::pair<int, int>(2,2));
//  m.insert(std::pair<int, int>(3,3));
//  std::map<int, int>::reverse_iterator it(m.end());
//     it +3;
// //  std::cout << it->first;
// //  std::cout << (*it).second ;std::cout << "   " << (*it).first ;
// }
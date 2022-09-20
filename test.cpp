#include "map/map.hpp"












int main()
{
    ft::Map<int, int> m;
    for (int i = 0; i < 10; i++)
        m.insert(ft::make_pair(1,1));
    for (int i = 0; i <10; i++)
        m.erase(i);
    system("leaks a.out");
}
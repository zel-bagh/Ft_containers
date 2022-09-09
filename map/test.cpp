#include<memory>
#include<iostream>
#include<map>
#include"map.hpp"
#include<unistd.h>
#include<iterator>
#include<vector>
#include"tools.hpp"
#include<time.h>
#include <ctime>
#include <sys/time.h>

#define TIME_FAC 3
time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}
void testMapConstructors()
{
  
            time_t start, end, diff;
            /*------------------ std::maps ---------------------*/
            std::map<int, std::string> m1;
            ft::Map<int, std::string> ft_m1;
            for (size_t i = 0; i < 1e6; i++)
            {
                m1.insert(std::make_pair(i, "string2"));
                ft_m1.insert(std::make_pair(i, "string2"));
            }

            start = get_time();
            m1.lower_bound(1e5);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
            /*-----------------------------------------------------*/
            /*------------------ ft::Maps ---------------------*/
            ualarm(diff * 1e3, 0);
            ft_m1.lower_bound(1e5);
            ualarm(0, 0);
            /*----------------------------------------------------*/
}

int main()

{
  testMapConstructors();
}
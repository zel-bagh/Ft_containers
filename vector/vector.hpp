#ifndef VECTOR_HPP
#define VECTOR_HPP

#include<functional>
#include"tools.hpp"
#include<iostream>

namespace ft
{
template < class T, class Alloc = std::allocator<T> >
class vector
{
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef value_type& reference;
        typedef typename  allocator_type::const_reference const_reference;
        typedef typename  allocator_type::pointer pointer;
        typedef typename  allocator_type::pointer const_pointer;
        typedef size_t      size_type;
    private:
        pointer _begin;
        allocator_type _allocate;
    public:
    explicit vector(const allocator_type& alloc = allocator_type())
    {
        (void)alloc;
        _begin = NULL;
    }
    explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
    {
       _begin = ((allocator_type&)alloc).allocate(n);
        pointer tmp = _begin;
        for(int i = 0; i < n; i++)
        {
            // ((allocator_type&)alloc).construct(_begin, val, n);
            (value_type )*tmp = val;
            tmp++;
        }
        // pointer tmp = _begin;
        // for(int i = 0; i < n; i++)
        //     std::cout << (*tmp)++;
    }
    // template <class InputIterator>
    // vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
    // {
    //     int n = 0;
    //     pointer tmp;
    //     InputIterator tmp = first;
    //     while (tmp != last)
    //     {
    //         n++;
    //         tmp++;
    //     }
    //     _begin = alloc.allocate(n);
    //     tmp = _begin;
    //     while(first != last)
    //     {
    //         alloc.construct(_begin, *first);
            
    //     }
        
    // }
};
}




#endif
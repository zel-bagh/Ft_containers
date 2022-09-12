#ifndef VECTOR_HPP
#define VECTOR_HPP

#include<functional>
#include"tools.hpp"
#include<iostream>
#include<iterator>

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
        allocator_type _alloc;
        size_type       _size;
        size_type       _capacity;
    public:
    explicit vector(const allocator_type& alloc = allocator_type())
    {
        _alloc = alloc;
        _begin = NULL;
        _size = 0;
        _capacity = 0;
    }
    explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
    {
        _alloc = alloc;
       _begin = ((allocator_type&)alloc).allocate(n);
        for(int i = 0; i < n; i++)
            ((allocator_type&)alloc).construct(_begin + i, val);
        _size = n;
        _capacity = n;
    }
    template <class InputIterator>
    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
    {
        _alloc = alloc;
        int n = 0;
        InputIterator tmp = first;
        while (tmp != last)
        {
            n++;
            tmp++;
        }
        _begin = ((allocator_type&)alloc).allocate(n);
        int i = 0;
        while (first != last)
            ((allocator_type&)alloc).construct(_begin + i++, *(first++));
        _size = n;
        _capacity = n;
    }
    vector (const vector& x) {*this = x;}
    public:
    vector& operator=(const vector& x)
    {
        if (_begin)
            delete _begin;
        _begin = _alloc.allocate(x._size);
        if (!x._size)
            _begin = NULL;
        for(int i = 0; i < x._size; i++)
            _alloc.construct(_begin + i, *(x._begin + i));
        _size = x._size;
        _capacity = x._size;
        _alloc = x._alloc;
    }

    public:
    class iterator : public std::iterator<std::random_access_iterator_tag, value_type>
    {
        private:
        pointer element;
        public:
        iterator(void) {element = NULL;}
        iterator(value_type& obj) {element = &obj;}
        iterator(const iterator& obj) {*this = obj;}
        public:
        pointer base(void) {return element;}
        public:
        iterator& operator=(const iterator& obj) {element = obj.element;}
        bool operator==(const iterator& obj) const {return (element == obj.element);}
        bool operator!=(const iterator& obj) const {return (element != obj.element);}
        reference operator*(void) const {return (*element);}
        pointer operator->(void) const {return element;}
        iterator& operator++(void){element++; return *this;}
        iterator operator++(int){element++; return iterator(*(element - 1));}
        iterator& operator--(void){element--; return *this;}
        iterator operator--(int){element--; return iterator(*(element + 1));}
        iterator    operator+(typename iterator::difference_type n) const {return iterator(*(element + n));}
        iterator    operator-(typename iterator::difference_type n) const {return iterator(*(element - n));}
        iterator& operator+= (typename iterator::difference_type n)
        {
            element += n;
            return *this;
        }
        iterator& operator-= (typename iterator::difference_type n)
        {
            element -= n;
            return *this;
        }
        reference operator[] (typename iterator::difference_type n) const {return element[n];}
    };
    private:
        // insert_to_a_free_vec(const value_type& val);
    public:
        iterator insert (iterator position, const value_type& val);	
        void insert (iterator position, size_type n, const value_type& val);
        template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last);  
};

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(typename vector<T, Alloc>::iterator position, const typename vector<T, Alloc>::value_type& val)
{
    int i = 0;
    int j;
    if (_capacity == NULL)
    {
        _begin = ((allocator_type&)_alloc).allocate(1);
        ((allocator_type&)_alloc).construct(_begin, val);
        _capacity = 1;
        _size = 1;
        return iterator(*(_begin));
    }
    if (_capacity - _size < 1)
    {
        pointer tmp = ((allocator_type&)_alloc).allocate(_capacity * 2);
        for (; _begin + i != position.base() && i != _size; i++)
             ((allocator_type&)_alloc).construct(tmp + i, _begin + i);
        ((allocator_type&)_alloc).construct(tmp + i, val);
        for (j = _size - i; j > 0; j--)
        {
            ((allocator_type&)_alloc).construct(tmp + i + 1, _begin + i);
            i++;
        }
        ((allocator_type&)_alloc).deallocate(_begin, _capacity);
        _begin = tmp;
        _capacity *= 2;
        _size += 1;
        if (i == _size - 1);
            return iterator(*(_begin + _size - 1));
        return iterator(*(_begin + i));
    }
    while(_begin + i != position.base() && i != _size)
        i++;
    j = _size + 1;
    while (--j > i)
        ((allocator_type&)_alloc).construct(_begin + j, _begin + j - 1);
    ((allocator_type&)_alloc).construct(_begin + i, val);
    _size += 1;
    return iterator(*(_begin + i));
}
template <class T, class Alloc>
void vector<T, Alloc>::insert(typename vector<T, Alloc>::iterator position,typename vector<T, Alloc>::size_type n, const typename vector<T, Alloc>::value_type& val)
{
    int i = 0;
    int j;
    int k;
    pointer tmp;
    if (_capacity == NULL)
    {
        _begin = ((allocator_type&)_alloc).allocate(n);
        while (i < n);
            ((allocator_type&)_alloc).construct(_begin + 0, val);
        _capacity = n;
        _size = n;
        return ; 
    }
    if (_capacity - _size < n)
    {
        if ((_capacity * 2) - _size >= n)
            tmp = ((allocator_type&)_alloc).allocate(_capacity * 2);
        else
            tmp = ((allocator_type&)_alloc).allocate(_capacity + n);
        for (; _begin + i != position.base() && i != _size; i++)
             ((allocator_type&)_alloc).construct(tmp + i, _begin + i);
        for(j = n; j > 0; j--)
            ((allocator_type&)_alloc).construct(tmp + i++, val);
        j = i - n;
        for (k = _size - j; k > 0; k--)
            ((allocator_type&)_alloc).construct(tmp + i++, _begin + j++);
        ((allocator_type&)_alloc).deallocate(_begin, _capacity);
        _begin = tmp;
        if ((_capacity * 2) - _size >= n)
            _capacity *= 2;
        else
            _capacity += n;
        _size += n;
        if (i == _size - 1);
            return iterator(*(_begin + _size - 1));
        return iterator(*(_begin + i));
    }
    while(_begin + i != position.base() && i != _size)
        i++;
    j = _size + 1;
    while (--j > i)
        ((allocator_type&)_alloc).construct(_begin + j, _begin + j - 1);
    ((allocator_type&)_alloc).construct(_begin + i, val);
    _size += 1;
    return iterator(*(_begin + i));
}
template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::insert (typename vector<T, Alloc>::iterator position, InputIterator first, InputIterator last)
{

}

}




#endif
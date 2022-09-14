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
        {
            ((allocator_type&)alloc).construct(_begin + i++, *(first));
            first++;
        }
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
        iterator(value_type* obj) {element = obj;}
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
        iterator operator++(int){element++; return iterator((element - 1));}
        iterator& operator--(void){element--; return *this;}
        iterator operator--(int){element--; return iterator((element + 1));}
        iterator    operator+(typename iterator::difference_type n) const {return iterator((element + n));}
        iterator    operator-(typename iterator::difference_type n) const {return iterator((element - n));}
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
    public:
        typedef typename ft::const_iterator<iterator>           const_iterator;
        typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
        typedef typename ft::const_iterator<reverse_iterator>   const_reverse_iterator;
    public: //Modifiers:
        iterator insert (iterator position, const value_type& val);	
        void insert (iterator position, size_type n, const value_type& val);
        template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last);
        iterator erase (iterator position);
        iterator erase (iterator first, iterator last);
        template <class InputIterator>
            void assign (InputIterator first, InputIterator last);
        void assign (size_type n, const value_type& val);
        void pop_back();
        void push_back (const value_type& val);
        void swap (vector& x);
        void clear();
    public: //Iterators:
        iterator begin(void);
        const_iterator begin(void) const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;
    public: //Capacity:
        size_type size() const;
        size_type max_size() const;
        void resize (size_type n, value_type val = value_type());
        size_type capacity() const;
        bool empty() const;
        void reserve (size_type n);
        void shrink_to_fit();
    public: //Element access
        reference operator[] (size_type n);
        const_reference operator[] (size_type n) const;
        reference at (size_type n);
        const_reference at (size_type n) const;
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;
};
//Element access==============================================================================================================================>
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[] (typename vector<T, Alloc>::size_type n)
{
    return (_begin[n]);
}
template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[] (typename vector<T, Alloc>::size_type n) const
{
    return (_begin[n]);
}
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at (typename vector<T, Alloc>::size_type n)
{
    if (n < _size)
        return (_begin[n]);
    throw (std::out_of_range("element not found"));
}
template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at (typename vector<T, Alloc>::size_type n) const
{
    if (n < _size)
        return (_begin[n]);
    throw (std::out_of_range("element not found"));
}
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front (void)
{
    return (*_begin);
}
template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front (void) const
{
    return (*_begin);
}
template <class T, class Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back (void)
{
    return (_begin[_size - 1]);
}
template <class T, class Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back (void) const
{
    return (_begin[_size - 1]);
}
//Capacity==============================================================================================================================>
template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size(void) const
{
        return (_size);
}
template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size(void) const
{
        return _alloc.max_size();
}
template <class T, class Alloc>
void vector<T, Alloc>::resize(typename vector<T, Alloc>::size_type n, typename vector<T, Alloc>::value_type val)
{
    int i;
    pointer tmp;
    if (_capacity == NULL)
        insert(iterator(NULL), n, val);
    else if (_size >= n)
        for (int i = n; i < _size; i++)
            ((allocator_type&)_alloc).destroy(_begin + i);
    else
    {
        if (_capacity < n)
        {
            tmp = ((allocator_type&)_alloc).allocate(n);
            for (i = 0; i < _size; i++)
                ((allocator_type&)_alloc).construct(tmp + i, _begin + i);
            for(; i < n; i++)
                ((allocator_type&)_alloc).construct(tmp + i, val);
        }
        else
           for(i = _size; i < n; i++)
                ((allocator_type&)_alloc).construct(_begin + i, val);
    }
    _size = n;
}
template <class T, class Alloc>
bool vector<T, Alloc>::empty(void) const
{
        return (!_size);
}
template <class T, class Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity(void) const
{
        return (_capacity);
}
template <class T, class Alloc>
void vector<T, Alloc>::reserve (typename vector<T, Alloc>::size_type n)
{
    pointer tmp;
    if (_capacity < n)
    {
        tmp = ((allocator_type&)_alloc).allocate(n);
        for (int i = 0; i < _size; i++)
            ((allocator_type&)_alloc).construct(tmp + i, _begin + i);
        ((allocator_type&)_alloc).deallocate(_begin, _capacity);
        _begin = tmp;
        _capacity = n;
    }
}
template <class T, class Alloc>
void vector<T, Alloc>::shrink_to_fit(void)
{
    pointer tmp;
    if (_capacity > _size)
    {
        tmp = ((allocator_type&)_alloc).allocate(_size);
        for (int i = 0; i < _size; i++)
            ((allocator_type&)_alloc).construct(tmp + i, _begin + i);
        ((allocator_type&)_alloc).deallocate(_begin, _capacity);
        _begin = tmp;
        _capacity = _size;
    }
}
//Iterators==============================================================================================================================>
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin(void)
{
        return (iterator(_begin));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin(void) const
{
    return (const_iterator(iterator(_begin)));
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end(void)
{
    return (iterator(_begin + _size));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end(void) const
{
    return (const_iterator(iterator(_begin + _size)));
}

template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin(void)
{
    return (reverse_iterator(iterator(_begin + _size - 1)));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin(void) const
{
    return (const_reverse_iterator(iterator(_begin + _size - 1)));
}

template <class T, class Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend(void)
{
    return (reverse_iterator(iterator(_begin - 1)));
}

template <class T, class Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend(void) const
{
    return (const_reverse_iterator(iterator(_begin - 1)));                             
}

//Modifiers==============================================================================================================================>
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
        if (i == _size - 1)
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
        while (i < n)
            ((allocator_type&)_alloc).construct(_begin + i, val);
        _capacity = n;
    }
    else if (_capacity - _size < n)
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
    }
    else
    {
        while(_begin + i != position.base() && i != _size)
            i++;
        j = _size + n;
        k = _size - i;
        while (k > 0)
            ((allocator_type&)_alloc).construct(_begin + j, _begin + j - n);
        for (j = n; j > 0; j--)
            ((allocator_type&)_alloc).construct(_begin + i++, val);
    }
    _size += n;
}
template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::insert (typename vector<T, Alloc>::iterator position, InputIterator first, InputIterator last)
{
    int i = 0;
    int n = 0;
    int j;
    int k;
    pointer tmp;
    InputIterator t = first;
    while (t++ != last)
        n++;
    if (_capacity == NULL)
    {
        _begin = ((allocator_type&)_alloc).allocate(n);
        while (i < n)
            ((allocator_type&)_alloc).construct(_begin + i, (*first)++);
        _capacity = n;
    }
    else if (_capacity - _size < n)
    {
        if ((_capacity * 2) - _size >= n)
            tmp = ((allocator_type&)_alloc).allocate(_capacity * 2);
        else
            tmp = ((allocator_type&)_alloc).allocate(_capacity + n);
        for (; _begin + i != position.base() && i != _size; i++)
             ((allocator_type&)_alloc).construct(tmp + i, _begin + i);
        for(j = n; j > 0; j--)
            ((allocator_type&)_alloc).construct(tmp + i++, (*first)++);
        j = i - n;
        for (k = _size - j; k > 0; k--)
            ((allocator_type&)_alloc).construct(tmp + i++, _begin + j++);
        ((allocator_type&)_alloc).deallocate(_begin, _capacity);
        _begin = tmp;
        if ((_capacity * 2) - _size >= n)
            _capacity *= 2;
        else
            _capacity += n;
    }
    else
    {
        while(_begin + i != position.base() && i != _size)
            i++;
        j = _size + n;
        k = _size - i;
        while (k > 0)
            ((allocator_type&)_alloc).construct(_begin + j, _begin + j - n);
        for (j = n; j > 0; j--)
            ((allocator_type&)_alloc).construct(_begin + i++, (*first)++);
    }
    _size += n;
}
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position)
{
    int i = 0;
    int j;
    if (_begin)
    {
        while (_begin + i != position.base() && i != _size)
            i++;
        if (i != _size)
        {
            ((allocator_type&)_alloc).destroy(_begin + i);
            _size -= 1;
            j = i;
            i--;
            while (++i < _size - 1)
                ((allocator_type&)_alloc).construct(_begin + i, _begin + i + 1);
            return (iterator(_begin + j));
        }
    }
    return iterator(NULL);
}
template <class T, class Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
{
    int i = 0;
    int j;
    if (_begin)
    {
        while (_begin + i != first.base() && i != _size)
            i++;
        if (i != _size)
        {
            j = i;
            while (_begin + i != last.base() && i != _size)
                ((allocator_type&)_alloc).destroy(_begin + i++);
            if (j != i)
                while (i < _size)
                    ((allocator_type&)_alloc).construct(_begin + j++, _begin + i++);
            _size -= i - j;
            return iterator(first.base());
        }
    }
    return iterator(NULL);
}
template <class T, class Alloc>
template <class InputIterator>
void vector<T, Alloc>::assign(InputIterator first, InputIterator last)
{
    int n = 0;
    int i ;
    while (first != last)
        n++;
    if (_capacity < n)
    {
        if (_begin)
        {
           ((allocator_type&)_alloc).deallocate(_begin, _capacity);
           _begin = NULL;
           _capacity = NULL;
           _size = NULL;
        }
        insert(first, last); 
    }
    else
    {
        for (i = 0; i < _size; i++)
            ((allocator_type&)_alloc).destroy(_begin + i);
        for (i = 0; first != last; first++)
            ((allocator_type&)_alloc).allocate(_begin + i++, *first);
        _size = n;
    }
}
template <class T, class Alloc>
void vector<T, Alloc>::assign(size_type n, const value_type& val)
{
    int i;
    if (_capacity < n)
    {
        if (_begin)
        {
           ((allocator_type&)_alloc).deallocate(_begin, _capacity);
           _begin = NULL;
           _capacity = NULL;
           _size = NULL;
        }
        insert(iterator(NULL), n, val);
    }
    else
    {
        for (i = 0; i < _size; i++)
            ((allocator_type&)_alloc).destroy(_begin + i);
        for (i = 0; i < n; i++)
            ((allocator_type&)_alloc).allocate(_begin + i++, val);
        _size = n;
    }
}
template <class T, class Alloc>
void vector<T, Alloc>::push_back(const value_type& val)
{
    insert(end(), val);
}
template <class T, class Alloc>
void vector<T, Alloc>::pop_back()
{
    erase(end());
}
template <class T, class Alloc>
void vector<T, Alloc>::swap(vector& x)
{
    pointer tmp = _begin;
    size_type s = _size;
    _begin = x._begin;
    x._begin = tmp;
    _size = x._size;
    x._size = s;
    s = _capacity;
    _capacity = x._capacity;
    x._capacity = s;
}
template <class T, class Alloc>
void vector<T, Alloc>::clear()
{
    if (_begin)
    {
        (allocator_type&)_alloc.deallocate(_begin, _capacity);
        _begin = NULL;
        _capacity = 0;
        _size = 0;
    }
}
}




#endif
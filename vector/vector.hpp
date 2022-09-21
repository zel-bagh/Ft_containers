#ifndef Vector_HPP
#define Vector_HPP

#include<functional>
#include"../tools.hpp"
#include<iostream>
#include<iterator>
#include"enable_if.hpp"

namespace ft
{
template < class T, class Alloc = std::allocator<T> >
class Vector
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
    explicit Vector(const allocator_type& alloc = allocator_type())
    {
        _alloc = alloc;
        _begin = NULL;
        _size = 0;
        _capacity = 0;
    }
    explicit Vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
    {
        _alloc = alloc;
       _begin = ((allocator_type&)alloc).allocate(n);
        for(size_type i = 0; i < n; i++)
            ((allocator_type&)alloc).construct(_begin + i, val);
        _size = n;
        _capacity = n;
    }
    template <class InputIterator> 
    Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),  typename ft::enable_if< !ft::is_integral<InputIterator>::value, int>::type b = int())
    {
        (void)b;
        _alloc = alloc;
        size_type n = 0;
        InputIterator tmp = first;
        while (tmp != last)
        {
            n++;
            tmp++;
        }
        _begin = ((allocator_type&)alloc).allocate(n);
        size_type i = 0;
        while (first != last)
        {
            ((allocator_type&)alloc).construct(_begin + i++, *(first));
            first++;
        }
        _size = n;
        _capacity = n;
    }
    Vector (const Vector& x)
    {
        _begin = NULL;
        if (x._size)
            _begin = _alloc.allocate(x._size);
        for(size_type i = 0; i < x._size; i++)
            _alloc.construct(_begin + i, *(x._begin + i));
        _size = x._size;
        _capacity = x._size;
    }
    ~Vector()
    {
        if (_begin)
        {
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_begin + i);
            _alloc.deallocate(_begin, _capacity);
        }
    }
    public:
    Vector& operator=(const Vector& x)
    {
        if (_begin)
        {
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(_begin + i);
            _alloc.deallocate(_begin, _capacity);
            _begin = NULL;
        }
        if (x._size)
            _begin = _alloc.allocate(x._size);
        for(size_type i = 0; i < x._size; i++)
            _alloc.construct(_begin + i, *(x._begin + i));
        _size = x._size;
        _capacity = x._size;
        return *this;
    }

    friend bool operator== (const Vector& lhs, const Vector& rhs)
    {
      if (lhs._size != rhs._size)
          return 0;
      for(size_t i = 0; i < lhs._size; i++)
          if (lhs._begin[i] != rhs._begin[i])
              return 0;
      return 1;
    }
    friend bool operator!= (const Vector& lhs, const Vector& rhs)
    {
        return !(lhs == rhs);
    }
	
    friend bool operator< (const Vector& lhs, const Vector& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }


    friend bool operator<= (const Vector& lhs, const Vector& rhs)
    {
        return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }


    friend bool operator>  (const Vector& lhs, const Vector& rhs)
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }


    friend bool operator>= (const Vector& lhs, const Vector& rhs)
    {
        return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
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
        iterator& operator=(const iterator& obj) {element = obj.element; return *this;}
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
        bool operator>(const iterator& obj) const {return (element > obj.element);}
        bool operator>=(const iterator& obj) const {return (element >= obj.element);}
        bool operator<(const iterator& obj) const {return (element < obj.element);}
        bool operator<=(const iterator& obj) const {return (element <= obj.element);}
        typename iterator::difference_type operator-(const iterator& obj) const {return (element - obj.element);}
        friend iterator operator+ (typename iterator::difference_type n, const iterator& it) {return iterator(it.element + n);}
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
        void swap (Vector& x);
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
    public://Allocator
        allocator_type get_allocator() const;
};
//Element access==============================================================================================================================>
template <class T, class Alloc>
typename Vector<T, Alloc>::reference Vector<T, Alloc>::operator[] (typename Vector<T, Alloc>::size_type n)
{
    return (_begin[n]);
}
template <class T, class Alloc>
typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::operator[] (typename Vector<T, Alloc>::size_type n) const
{
    return (_begin[n]);
}
template <class T, class Alloc>
typename Vector<T, Alloc>::reference Vector<T, Alloc>::at (typename Vector<T, Alloc>::size_type n)
{
    if (n < _size)
        return (_begin[n]);
    throw (std::out_of_range("element not found"));
}
template <class T, class Alloc>
typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::at (typename Vector<T, Alloc>::size_type n) const
{
    if (n < _size)
        return (_begin[n]);
    throw (std::out_of_range("element not found"));
}
template <class T, class Alloc>
typename Vector<T, Alloc>::reference Vector<T, Alloc>::front (void)
{
    return (*_begin);
}
template <class T, class Alloc>
typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::front (void) const
{
    return (*_begin);
}
template <class T, class Alloc>
typename Vector<T, Alloc>::reference Vector<T, Alloc>::back (void)
{
    return (_begin[_size - 1]);
}
template <class T, class Alloc>
typename Vector<T, Alloc>::const_reference Vector<T, Alloc>::back (void) const
{
    return (_begin[_size - 1]);
}
//Capacity==============================================================================================================================>
template <class T, class Alloc>
typename Vector<T, Alloc>::size_type Vector<T, Alloc>::size(void) const
{
        return (_size);
}
template <class T, class Alloc>
typename Vector<T, Alloc>::size_type Vector<T, Alloc>::max_size(void) const
{
        return _alloc.max_size();
}
template <class T, class Alloc>
void Vector<T, Alloc>::resize(typename Vector<T, Alloc>::size_type n, typename Vector<T, Alloc>::value_type val)
{
    size_type i;
    pointer tmp;
    if (_capacity == 0)
        insert(iterator(NULL), n, val);
    else if (_size > n)
        for (size_type i = n; i < _size; i++)
            ((allocator_type&)_alloc).destroy(_begin + i);
    else
    {
        if (_capacity < n)
        {
            tmp = ((allocator_type&)_alloc).allocate(n);
            for (i = 0; i < _size; i++)
            {
                ((allocator_type&)_alloc).construct(tmp + i, *(_begin + i));
                ((allocator_type&)_alloc).destroy(_begin + i);
            }
            for(; i < n; i++)
                ((allocator_type&)_alloc).construct(tmp + i, val);
            ((allocator_type&)_alloc).deallocate(_begin, _capacity);
            _begin = tmp;
            _capacity = n;
        }
        else
           for(i = _size; i < n; i++)
                ((allocator_type&)_alloc).construct(_begin + i, val);
    }
    _size = n;
}
template <class T, class Alloc>
bool Vector<T, Alloc>::empty(void) const
{
        return (!_size);
}
template <class T, class Alloc>
typename Vector<T, Alloc>::size_type Vector<T, Alloc>::capacity(void) const
{
        return (_capacity);
}
template <class T, class Alloc>
void Vector<T, Alloc>::reserve (typename Vector<T, Alloc>::size_type n)
{
    pointer tmp;
    if (_capacity < n)
    {
        tmp = ((allocator_type&)_alloc).allocate(n);
        for (size_type i = 0; i < _size; i++)
        {
            ((allocator_type&)_alloc).construct(tmp + i, *(_begin + i));
            ((allocator_type&)_alloc).destroy(_begin + i);
        }
        if (_begin)
            ((allocator_type&)_alloc).deallocate(_begin, _capacity);
        _begin = tmp;
        _capacity = n;
    }
}
template <class T, class Alloc>
void Vector<T, Alloc>::shrink_to_fit(void)
{
    pointer tmp;

    if (_capacity > _size)
    {
        if (_size != 0)
            tmp = ((allocator_type&)_alloc).allocate(_size);
        else
            tmp = NULL;
        for (size_type i = 0; i < _size; i++)
        {
            ((allocator_type&)_alloc).construct(tmp + i, *(_begin + i));
            ((allocator_type&)_alloc).destroy(_begin + i);
        }
        ((allocator_type&)_alloc).deallocate(_begin, _capacity);
        _begin = tmp;
        _capacity = _size;
    }
}
//Iterators==============================================================================================================================>
template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::begin(void)
{
        return (iterator(_begin));
}

template <class T, class Alloc>
typename Vector<T, Alloc>::const_iterator Vector<T, Alloc>::begin(void) const
{
    return (const_iterator(iterator(_begin)));
}

template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::end(void)
{
    return (iterator(_begin + _size));
}

template <class T, class Alloc>
typename Vector<T, Alloc>::const_iterator Vector<T, Alloc>::end(void) const
{
    return (const_iterator(iterator(_begin + _size)));
}

template <class T, class Alloc>
typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rbegin(void)
{
    return (reverse_iterator(iterator(_begin + _size)));
}

template <class T, class Alloc>
typename Vector<T, Alloc>::const_reverse_iterator Vector<T, Alloc>::rbegin(void) const
{
    return (const_reverse_iterator(iterator(_begin + _size)));
}

template <class T, class Alloc>
typename Vector<T, Alloc>::reverse_iterator Vector<T, Alloc>::rend(void)
{
    return (reverse_iterator(iterator(_begin)));
}

template <class T, class Alloc>
typename Vector<T, Alloc>::const_reverse_iterator Vector<T, Alloc>::rend(void) const
{
    return (const_reverse_iterator(iterator(_begin)));                             
}

//Modifiers==============================================================================================================================>
template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::insert(typename Vector<T, Alloc>::iterator position, const typename Vector<T, Alloc>::value_type& val)
{
    size_type i = 0;
    size_type j;
    if (_capacity == 0)
    {
        _begin = ((allocator_type&)_alloc).allocate(1);
        ((allocator_type&)_alloc).construct(_begin, val);
        _capacity = 1;
        _size = 1;
        return iterator(_begin);
    }
    if (_capacity == _size)
    {
        pointer tmp = ((allocator_type&)_alloc).allocate(_capacity * 2);
        for (; _begin + i != position.base() && i != _size; i++)
             ((allocator_type&)_alloc).construct(tmp + i, *(_begin + i));
        j = i;
        ((allocator_type&)_alloc).construct(tmp + i, val);
        for (;i < _size; i++)
            ((allocator_type&)_alloc).construct(tmp + i + 1, *(_begin + i));
        {
            for (size_type i = 0; i < _size; i++)
                ((allocator_type&)_alloc).destroy(_begin + i);
            ((allocator_type&)_alloc).deallocate(_begin, _capacity);
        }
        _begin = tmp;
        _capacity *= 2;
        _size += 1;
        return iterator((_begin + j));
    }
    if (!(position.base() > _begin + _size - 1 && position.base() < _begin) )
        while(_begin + i != position.base())
            i++;
    else
        i = _size;
    j = _size + 1;
    while (--j > i)
    {
        if (j < _size)
            ((allocator_type&)_alloc).destroy(_begin + j);
        ((allocator_type&)_alloc).construct(_begin + j, *(_begin + j - 1));
    }
    if (i < _size)
        ((allocator_type&)_alloc).destroy(_begin + i);
    ((allocator_type&)_alloc).construct(_begin + i, val);
    _size += 1;
    return iterator((_begin + i));
}
template <class T, class Alloc>
void Vector<T, Alloc>::insert(typename Vector<T, Alloc>::iterator position,typename Vector<T, Alloc>::size_type n, const typename Vector<T, Alloc>::value_type& val)
{
    size_type i = 0;
    size_type j;
    pointer tmp;
    if (n != 0)
    {
        if (_capacity == 0)
        {
            _begin = ((allocator_type&)_alloc).allocate(n);
            while (i < n)
                ((allocator_type&)_alloc).construct(_begin + i++, val);
            _capacity = n;
        }
        else if (_capacity - _size < n)
        {
            if ((_capacity * 2) - _size >= n)
                tmp = ((allocator_type&)_alloc).allocate(_capacity * 2);
            else
                tmp = ((allocator_type&)_alloc).allocate(_capacity + n);
            for (; _begin + i != position.base() && i != _size; i++)
                 ((allocator_type&)_alloc).construct(tmp + i, *(_begin + i));
            for(j = n; j > 0; j--)
                ((allocator_type&)_alloc).construct(tmp + i++, val);
            j = i - n;
            for (; j < _size; j++)
                ((allocator_type&)_alloc).construct(tmp + i++, *(_begin + j));
            {
                for (size_type i = 0; i < _size; i++)
                    ((allocator_type&)_alloc).destroy(_begin + i);
                ((allocator_type&)_alloc).deallocate(_begin, _capacity);
            }
            _begin = tmp;
            if ((_capacity * 2) - _size >= n)
                _capacity *= 2;
            else
                _capacity += n;
        }
        else
        {
            if (!(position.base() > _begin + _size - 1 && position.base() < _begin) )
                while(_begin + i != position.base())
                    i++;
            else
                i = _size;
            j = _size + n - 1;
            while (j != i + n - 1)
            {
                if (j - n < _size)
                    ((allocator_type&)_alloc).destroy(_begin + j - n);               
                ((allocator_type&)_alloc).construct(_begin + j, *(_begin + j - n));
                j--;
            }
            for (j = n; j > 0; j--)
            {
                if (i < _size)
                    ((allocator_type&)_alloc).destroy(_begin + i);    
                ((allocator_type&)_alloc).construct(_begin + i++, val);
            }
        }
        _size += n;
    }
}
template <class T, class Alloc>
template <class InputIterator>
void Vector<T, Alloc>::insert (typename Vector<T, Alloc>::iterator position, InputIterator first, InputIterator last)
{
    size_type i = 0;
    size_type n = 0;
    size_type j;
    pointer tmp;
    InputIterator t = first;
    while (t++ != last)
        n++;
    if (n != 0)
    {
        if (_capacity == 0)
        {
            _begin = ((allocator_type&)_alloc).allocate(n);
            while (i < n)
            {
                ((allocator_type&)_alloc).construct(_begin + i++, (*first));
                first++;
            }
            _capacity = n;
        }
        else if (_capacity - _size < n)
        {
            if ((_capacity * 2) - _size >= n)
                tmp = ((allocator_type&)_alloc).allocate(_capacity * 2);
            else
                tmp = ((allocator_type&)_alloc).allocate(_capacity + n);
            for (; _begin + i != position.base() && i != _size; i++)
                 ((allocator_type&)_alloc).construct(tmp + i, *(_begin + i));
            for(j = n; j > 0; j--)
            {
                ((allocator_type&)_alloc).construct(tmp + i++, (*first));
                first++;
            }
            j = i - n;
            for (; j < _size; j++)
                ((allocator_type&)_alloc).construct(tmp + i++, *(_begin + j));
            {
                for (size_type i = 0; i < _size; i++)
                    ((allocator_type&)_alloc).destroy(_begin + i);
                ((allocator_type&)_alloc).deallocate(_begin, _capacity);
            }
            _begin = tmp;
            if ((_capacity * 2) - _size >= n)
                _capacity *= 2;
            else
                _capacity += n;
        }
        else
        {
            if (!(position.base() > _begin + _size - 1 && position.base() < _begin) )
                while(_begin + i != position.base())
                    i++;
            else
                i = _size;
            j = _size + n - 1;
            while (j != i + n - 1)
            {
                if (j - n < _size)
                    ((allocator_type&)_alloc).destroy(_begin + j - n);       
                ((allocator_type&)_alloc).construct(_begin + j, *(_begin + j - n));
                j--;
            }
            for (j = n; j > 0; j--)
            {
                if (i < _size)
                    ((allocator_type&)_alloc).destroy(_begin + i);  
                ((allocator_type&)_alloc).construct(_begin + i++, (*first));
                first++;
            }
        }
        _size += n;
    }
}
template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator position)
{
    size_type i = 0;
    size_type j;

    if (_begin && position.base() >= _begin && position.base() <= _begin + _size - 1)
    {
        while (_begin + i != position.base())
            i++;
        ((allocator_type&)_alloc).destroy(_begin + i);
        j = i;
        i--;
        while (++i < _size - 1)
        {
            ((allocator_type&)_alloc).construct(_begin + i, *(_begin + i + 1));
            ((allocator_type&)_alloc).destroy(_begin + i + 1);
        }
        _size -= 1;
        return (iterator(_begin + j));

    }
    return iterator(NULL);
}
template <class T, class Alloc>
typename Vector<T, Alloc>::iterator Vector<T, Alloc>::erase(iterator first, iterator last)
{
    size_type i = 0;
    size_type j;

    if (_begin && first.base() >= _begin && first.base() <= _begin + _size - 1)
    {
        while (_begin + i != first.base())
            i++;
        j = i;
        while (_begin + i != last.base() && i != _size)
            ((allocator_type&)_alloc).destroy(_begin + i++);
        if (j != i)
        {
            while (i < _size)
            {
                ((allocator_type&)_alloc).construct(_begin + j++, *(_begin + i));
                ((allocator_type&)_alloc).destroy(_begin + i++);
            }
        }
        _size -= i - j;
        return iterator(first.base());
    }
    return iterator(NULL);
}
template <class T, class Alloc>
template <class InputIterator>
void Vector<T, Alloc>::assign(InputIterator first, InputIterator last)
{
    size_type n = 0;
    size_type i  = 0;
    InputIterator tmp = first;
    while (tmp++ != last)
        n++;
    if (_capacity < n)
    {
        if (_begin)
        {
            while(i < _size)
                ((allocator_type&)_alloc).destroy(_begin + i++);
           ((allocator_type&)_alloc).deallocate(_begin, _capacity);
           _begin = NULL;
           _capacity = 0;
           _size = 0;
        }
        insert(iterator(NULL), first, last);
    }
    else
    {
        for (; i < _size; i++)
            ((allocator_type&)_alloc).destroy(_begin + i);
        for (i = 0; first != last; first++)
            ((allocator_type&)_alloc).construct(_begin + i++, *first);
        _size = n;
    }
}
template <class T, class Alloc>
void Vector<T, Alloc>::assign(size_type n, const value_type& val)
{
    size_type i = 0;
    if (_capacity < n)
    {
        if (_begin)
        {
            while(i < _size)
                ((allocator_type&)_alloc).destroy(_begin + i++);
           ((allocator_type&)_alloc).deallocate(_begin, _capacity);
           _begin = NULL;
           _capacity = 0;
           _size = 0;
        }
        insert(iterator(NULL), n, val);
    }
    else
    {
        for (; i < _size; i++)
            ((allocator_type&)_alloc).destroy(_begin + i);
        for (i = 0; i < n; i++)
            ((allocator_type&)_alloc).construct(_begin + i, val);
        _size = n;
    }
}
template <class T, class Alloc>
void Vector<T, Alloc>::push_back(const value_type& val)
{
    insert(end(), val);
}
template <class T, class Alloc>
void Vector<T, Alloc>::pop_back()
{
    erase(--end());
}
template <class T, class Alloc>
void Vector<T, Alloc>::swap(Vector& x)
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
void Vector<T, Alloc>::clear()
{
    for (size_type i = 0; i < _size; i++)
        ((allocator_type&)_alloc).destroy(_begin + i);
    _size = 0;
}
template <class T, class Alloc>
void swap (ft::Vector<T,Alloc>& x, ft::Vector<T,Alloc>& y)
{
    x.swap(y);
}
template <class T, class Alloc>
typename ft::Vector<T, Alloc>::allocator_type Vector<T, Alloc>::get_allocator() const
{
    return Alloc();
}
}




#endif
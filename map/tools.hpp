#ifndef TOOLS_HPP
#define TOOLS_HPP
namespace ft 
{
    template <typename T>
    struct iterator_traits
    {
        typedef typename T::difference_type        difference_type;
        typedef typename T::value_type             value_type;
        typedef typename T::pointer                pointer;
        typedef typename T::reference             reference;
        typedef typename T::iterator_category     iterator_category;
    };

    template<class Iterator>
    class reverse_iterator
    {
        public:
        typedef Iterator                                                iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference           reference;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;
        private:
            iterator_type it;
        public:
        reverse_iterator(void){};
        reverse_iterator(const reverse_iterator& obj){*this = obj;}
        reverse_iterator(const iterator_type& obj){it = obj;}
        ~reverse_iterator(void){};
        public:
        iterator_type base() const {return (iterator_type(it));}
        public:
        reverse_iterator& operator=(const reverse_iterator& obj){it = obj.it; return *this;}
        pointer     operator->(void) const 
        {
            iterator_type tmp(it);
            return (&(*(--tmp)));
        }
        reference   operator*(void) const 
        {
            iterator_type tmp(it);
            return (*(--tmp));
        }
        reverse_iterator&    operator++(void){--it; return *this;}
        reverse_iterator&    operator--(void){++it; return *this;}
        reverse_iterator    operator++(int){return reverse_iterator(it--);}
        reverse_iterator    operator--(int){return reverse_iterator(it++);}
        reverse_iterator    operator+(difference_type n) const
        {
            return reverse_iterator(it-n);
        }
        reverse_iterator    operator-(difference_type n) const
        {
            return reverse_iterator(it+n);
        }
        reverse_iterator& operator+= (difference_type n)
        {
            it -= n;
            return *this;
        }
        reverse_iterator& operator-= (difference_type n)
        {
            it += n;
            return *this;
        }
        reference operator[] (difference_type n) const
        {
            return it[-n-1];
        }
        bool    operator==(const reverse_iterator& obj) const {return (it == obj.it);}
        bool    operator!=(const reverse_iterator& obj) const {return (it != obj.it);}
    };

    template<class Iterator>
    class const_iterator
    {
        public:
        typedef Iterator                                                iterator_type;
        typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename iterator_traits<Iterator>::pointer             pointer;
        typedef typename iterator_traits<Iterator>::reference	        reference;
        typedef typename iterator_traits<Iterator>::difference_type     difference_type;
        private:
            iterator_type it;
        public:
        iterator_type base() const {return (iterator_type(it));}
        public:
        const_iterator(void){};
        const_iterator(const const_iterator& obj){*this = obj;}
        const_iterator(const iterator_type& obj){it = obj;}
        ~const_iterator(void){};
        public:
        const_iterator& operator=(const const_iterator& obj){it = obj.it; return *this;}
        const pointer     operator->(void) const {return (&(*it));}
        const reference   operator*(void) const {return (*it);}
        const_iterator&    operator++(void){++it; return *this;}
        const_iterator&    operator--(void){--it; return *this;}
        const_iterator    operator++(int){return const_iterator(it++);}
        const_iterator    operator--(int){return const_iterator(it--);}
        const_iterator    operator+(difference_type n) const
        {
            return const_iterator(it+n);
        }
        const_iterator    operator-(difference_type n) const
        {
            return const_iterator(it-n);
        }
        const_iterator& operator+= (difference_type n)
        {
            it += n;
            return *this;
        }
        const_iterator& operator-= (difference_type n)
        {
            it -= n;
            return *this;
        }
        const reference operator[] (difference_type n) const
        {
            return base()[-n-1];
        }
        bool    operator==(const const_iterator& obj) const {return (it == obj.it);}
        bool    operator!=(const const_iterator& obj) const {return (it != obj.it);}
    };
}   
#endif
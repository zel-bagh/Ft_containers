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
        reverse_iterator(void){}
        reverse_iterator(const reverse_iterator& obj){*this = obj;}
        reverse_iterator(const iterator_type& obj){it = obj;}
        ~reverse_iterator(void){};
        public:
        iterator_type base() const {return it;}
        public:
        reverse_iterator& operator=(const reverse_iterator& obj){it = obj.it; return *this;}
        pointer     operator->(void) const 
        {
           iterator_type tmp = it;
            tmp--;
            return &(*(tmp));
        }
        reference   operator*(void) const 
        {
            iterator_type tmp = it;
            tmp--;
            return	*(tmp);
        }
        reverse_iterator&    operator++(void){--it; return *this;}
        reverse_iterator&    operator--(void){++it; return *this;}
        reverse_iterator    operator++(int){return (reverse_iterator(it--));}
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
        friend bool operator== (const reverse_iterator& lhs,
                       const reverse_iterator& rhs) {return (lhs.it == rhs.it);}

        friend bool operator!= (const reverse_iterator& lhs,
                       const reverse_iterator& rhs) {return (lhs.it != rhs.it);}

        friend bool operator<  (const reverse_iterator<Iterator>& lhs,
                       const reverse_iterator& rhs) {return (lhs.it > rhs.it);}

        friend bool operator<= (const reverse_iterator& lhs,
                       const reverse_iterator& rhs) {return (lhs.it >= rhs.it);}

        friend bool operator>  (const reverse_iterator& lhs,
                       const reverse_iterator& rhs) {return (lhs.it < rhs.it);}

        friend bool operator>= (const reverse_iterator& lhs,
                       const reverse_iterator& rhs) {return (lhs.it <= rhs.it);}

        friend reverse_iterator operator+ (typename reverse_iterator::difference_type n,
                 const reverse_iterator& rev_it) {return reverse_iterator(rev_it.it-n);}

        friend typename reverse_iterator::difference_type operator- (const reverse_iterator& lhs,
            const reverse_iterator& rhs) {return (rhs.it - lhs.it);}
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
            return it[n];
        }

        friend bool operator== (const const_iterator& lhs,
                       const const_iterator& rhs) {return (lhs.it == rhs.it);}
        friend bool operator!= (const const_iterator& lhs,
                       const const_iterator& rhs) {return (lhs.it != rhs.it);}
        friend bool operator<  (const const_iterator& lhs,
                       const const_iterator& rhs) {return (lhs.it < rhs.it);}
        friend bool operator<= (const const_iterator& lhs,
                       const const_iterator& rhs) {return (lhs.it <= rhs.it);}
        friend bool operator>  (const const_iterator& lhs,
                       const const_iterator& rhs) {return (lhs.it > rhs.it);}
        friend bool operator>= (const const_iterator& lhs,
                       const const_iterator& rhs) {return (lhs.it >= rhs.it);}
        friend const_iterator operator+ (typename const_iterator::difference_type n,
                 const const_iterator& rev_it) {return const_iterator(rev_it.it+n);}
        friend typename const_iterator::difference_type operator- (const const_iterator& lhs,
            const const_iterator& rhs) {return (lhs.it - rhs.it);}
    };


template < class InputIterator1, class InputIterator2>
bool    lexicographical_compare(InputIterator1 first1, InputIterator1 last1
		,InputIterator2 first2, InputIterator2 last2)
{
	while(first1!=last1){
		if (first2==last2 || *first2<*first1) return false;
		else if (*first1<*first2) return true;
		++first1;
		++first2;
	}
	return (first2!=last2);
};
}

#endif
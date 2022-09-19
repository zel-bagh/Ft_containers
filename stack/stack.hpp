#ifndef STACK_HPP
#define STACK_HPP


#include"../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = ft::Vector<T> >
    class Stack
    {
        public:
        typedef T value_type;
        typedef Container container_type;
        typedef size_t size_type;
        private:
        container_type c;
        public:
        explicit Stack (const container_type& ctnr = container_type()) : c(ctnr){}
        ~Stack(){}
        bool empty() const {return c.empty();}
        size_type size() const {return c.size();}
        value_type& top() {return c.back();}
        const value_type& top() const {return c.back();}
        void push (const value_type& val){c.push_back(val);}
        void pop() {c.pop_back();}
        public:
        Stack& operator=(const Stack& x) {c = x.c;}
        public:
        friend    bool operator== (const Stack& lhs, const Stack& rhs)
            {return lhs.c == rhs.c;}

        friend    bool operator!= (const Stack& lhs, const Stack& rhs)
            {return lhs.c != rhs.c;}

        friend    bool operator<  (const Stack& lhs, const Stack& rhs)
            {return lhs.c < rhs.c;}

        friend    bool operator<= (const Stack& lhs, const Stack& rhs)
            {return lhs.c <= rhs.c;}

        friend    bool operator>  (const Stack& lhs, const Stack& rhs)
            {return lhs.c > rhs.c;}
    
        friend    bool operator>= (const Stack& lhs, const Stack& rhs)
            {return lhs.c >= rhs.c;}
    };
}
#endif
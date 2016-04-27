#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <limits>
#include <memory>
#include <cstddef>
template <typename T, typename A=std::allocator<T> >
class list  ///template container list class
{
private:
    struct node                                                 /// node element
    {
        node(const T& _data, node* _prev=0, node* _next=0)          /// creating node
        : data(_data), prev(_prev),  next(_next) {};     
        T data;
        node* prev;
        node* next;
    };

public:
    template <typename T2, typename B>
    friend std::ostream& operator<<(std::ostream& os, list& l); /// need to print it somewhere

    list();                                                     /// zero initializing ctor
    list(const list<T, A>& other);
    ~list();                                                    /// dtor to prevent memory leaks
    void push_back(const T& data);                                 /// adds item on the list's ending
    void push_front(const T& data);                             /// adds item on the list's begining

    class iterator : public std::iterator<std::forward_iterator_tag, T>                                              /// iterator class needed for iteration
    {
    public:
        iterator(node* _ptr)                                    /// constructs the iterator
        : ptr(_ptr) {}
        iterator& operator++() { ptr = ptr->next; return *this; }       /// needed to iterate using ++OBJECT
        iterator operator++(int)                                        /// needed to iterate using OBJECT++
        {
            iterator tmp(ptr);
            ptr = ptr->next;
            return tmp;
        }
        T& operator*() { return ptr->data; }                            /// returns value hidden under iterator
        bool operator!=(const iterator& other)                          /// needed to compare begin() and end()
        { return ptr != other.ptr; }
    private:
        node* ptr;
    };
    iterator begin() const { return iterator(_head); }                  /// returns begining of iteration
    iterator end() const { return iterator(0); }                    /// returns end of iteration
private:
    

    node* create_node(const T& node);

    node* _head;
    node* _tail;
    typename A::template rebind<node>::other _allocator;
};
#include "list.inl"


#endif /* end of include guard: LIST_H */


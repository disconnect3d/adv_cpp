#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <limits>
#include <memory>
#include <cstddef>

// compilation define flags:
// DEBUG - launches DEBUG mode, which verboses all operations - none of the options below work without this
//
// DEBUG_TIMER - adds timer to the debug (unfortunately, it's just in seconds atm; change debugGetCurrentTime() if you want to implement micro/miliseconds)
// DEBUG_FULL_DSC - adds template description (basically uses __PRETTY_FUNCTION__ - non-standard macro defined by gcc, instead of __func__)
//
// DEBUG_ITER - launches DEBUG mode for iterators, DOES NOT work without DEBUG flag
// DEBUG_NODE - launches DEBUG mode for nodes, DOES NOT work without DEBUG flag
//

#ifdef DEBUG

// you can define your own debug output, it's defaulted to std::cerr
#ifndef DEBUG_OUT
#define DEBUG_OUT std::cerr 
#endif // #ifndef DEBUG_OUT

#ifdef DEBUG_TIMER
#include <ctime>
time_t __DEBUG_GCT_time_t;  // time_t that helds seconds till 1970 or sth like that
struct tm __DEBUG_GCT_tm;   // tm struct holding localtime
char __DEBUG_GCT_char[80];  // buffer storing char[] time representation

const inline std::string debugGetCurrentTime()
{
    // create a micro/milisecond timer here if you want..
    __DEBUG_GCT_time_t = time(0);
    __DEBUG_GCT_tm = *localtime(&__DEBUG_GCT_time_t);
    strftime(__DEBUG_GCT_char, sizeof(__DEBUG_GCT_char), "%Y-%m-%d %X", &__DEBUG_GCT_tm);
    
    return __DEBUG_GCT_char;
}

#define DEBUG_GCT '[' << debugGetCurrentTime() << "] "
#else
#define DEBUG_GCT "" 
#endif // ifdef DEBUG_TIMER

////// QUESTION : ifndef __PRETTY_FUNCTION__ seems not to work. Does gcc defines this macro "later"?
#ifndef DEBUG_FULL_DSC
#define __PRETTY_FUNCTION__ __func__
#endif // ifndef DEBUG_FULL_DSC

int __DEBUG_FUNC_DEPTH = 0;
const inline std::string debugGetCurrentFuncDepth(bool increment)
{
    if (increment)
        ++__DEBUG_FUNC_DEPTH;

    std::string result = "";
    for(int i=__DEBUG_FUNC_DEPTH; i>=0; --i)
        result += " ";
    
    if (!increment)
        --__DEBUG_FUNC_DEPTH;

    return result;
}
// GCFD = GetCurrentFuncDepth
#define DEBUG_LOG_GCFD  debugGetCurrentFuncDepth(true)
#define DEBUG_DELOG_GCFD debugGetCurrentFuncDepth(false)

#define LOG  DEBUG_OUT << DEBUG_LOG_GCFD << DEBUG_GCT << __PRETTY_FUNCTION__ << std::endl

#define LOG_ARG(x) DEBUG_OUT << DEBUG_LOG_GCFD << DEBUG_GCT << __PRETTY_FUNCTION__ << ", args = {" << x << "}" << std::endl

#define DELOG DEBUG_OUT << DEBUG_DELOG_GCFD << DEBUG_GCT << "exitting " << __PRETTY_FUNCTION__ << std::endl


#ifdef DEBUG_ITER
#define LOG_ITER LOG
#define DELOG_ITER DELOG
#else
#define LOG_ITER
#define DELOG_ITER
#endif // ifdef DEBUG_ITER


#ifdef DEBUG_NODE
#define LOG_NODE LOG
#define DELOG_NODE DELOG
#else
#define LOG_NODE
#define DELOG_NODE
#endif // ifdef DEBUG_NODE


#else
#define LOG
#define LOG_ARG(x)
#define DELOG
#define LOG_ITER
#define DELOG_ITER
#define LOG_NODE
#define DELOG_NODE
#endif


#include "listBase.h"           // T and A types are typedefed in listBase
class list : public listBase  ///template container list class
{
private:
    struct node                                                 /// node element
    {
        node(const T& _data, node* _prev=0, node* _next=0)          /// creating node
        : data(_data), prev(_prev),  next(_next)
        {
            LOG_NODE;
            DELOG_NODE;
        };     
        T data;
        node* prev;
        node* next;
    };

public:
    friend std::ostream& operator<<(std::ostream& os, list& l); /// need to print it somewhere

    list();                                                     /// zero initializing ctor
    list(const list& other);
    ~list();                                                    /// dtor to prevent memory leaks
    void push_back(const T& data) override;                                 /// adds item on the list's ending
    void push_front(const T& data) override;                             /// adds item on the list's begining

    class iterator : public std::iterator<std::forward_iterator_tag, T>                                              /// iterator class needed for iteration
    {
    public:
        iterator(node* _ptr)                    /// constructs the iterator
        : ptr(_ptr)
        {
            LOG_ITER;
            DELOG_ITER;
        }
        iterator& operator++()                  /// needed to iterate using ++OBJECT
        {
            LOG_ITER;
            ptr = ptr->next; return *this;
            DELOG_ITER;
        }

        iterator operator++(int)                /// needed to iterate using OBJECT++
        {
            LOG_ITER;
            iterator tmp(ptr);
            ptr = ptr->next;
            DELOG_ITER;
            return tmp;
        }

        T& operator*()                          /// returns value hidden under iterator

        {
            LOG_ITER;
            DELOG_ITER;
            return ptr->data;
        }

        bool operator!=(const iterator& other)  /// needed to compare begin() and end()
        {
            LOG_ITER;
            DELOG_ITER;
            return ptr != other.ptr;
        }
    private:
        node* ptr;
    };
    iterator begin() const                      /// returns begining of iteration

    {
        LOG_ITER;
        DELOG_ITER;
        return iterator(_head);
    }                    

    iterator end() const                        /// returns end of iteration
    {
        LOG_ITER;
        DELOG_ITER;
        return iterator(0);
    }                  

private:
    node* create_node(const T& node);

    node* _head;
    node* _tail;
    A::rebind<node>::other _allocator;
};

#endif /* end of include guard: LIST_H */


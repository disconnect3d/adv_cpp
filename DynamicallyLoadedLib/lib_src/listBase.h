#ifndef LISTBASE_H
#define LISTBASE_H

typedef int T;
typedef std::allocator<T> A;

class listBase
{
public:
    listBase() = default;
    listBase(const listBase&) = default;
    virtual void push_back(const T& data) = 0;
    virtual void push_front(const T& data) = 0;
    virtual ~listBase() {}
};

#endif /* end of include guard: LISTBASE_H */


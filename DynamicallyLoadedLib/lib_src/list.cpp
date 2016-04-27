#include "list.h"

std::ostream& operator<<(std::ostream& os, const list& l)
{
    LOG;
    os << "List = [";
    for(list::iterator i = l.begin(); i != l.end(); ++i)
        os << *i << ", ";
    os << "\b\b]\n";

    DELOG;
    return os;
}

list::list()
: _head(0), _tail(0)
{
    LOG;
    DELOG;
}

list::~list()
{
    LOG;
    node* tmp = _head;
    while (tmp)
    {
        tmp = tmp->next;
        _allocator.destroy(_head);
        _allocator.deallocate(_head, 1);
        _head = tmp;
    }
    //_allocator.destroy(tmp);
    //_allocator.deallocate(tmp, 1);
    _head = 0;
    _tail = 0;
    DELOG;
}

list::list(const list& other)
: _head(0), _tail(0)
{
    LOG_ARG(other);
    node *tmp = other._head;
    while (tmp->next)
    {
        push_back(tmp->data);
        tmp = tmp->next;
    }
    push_back(tmp->data);
    DELOG;
}

void list::push_back(const T& data)
{
    LOG_ARG(data);
    if (!_head)
    {
        _head = create_node(data);
        _tail = _head;
    }
    else
    {
        node* tmp = create_node(data);
        tmp->prev = _tail;
        _tail->next = tmp;
        _tail = tmp;
    }
    DELOG;
}

void list::push_front(const T& data)
{
    LOG_ARG(data);
    if (!_head)
    {
        _head = create_node(data);
        _tail = _head;
    }
    else
    {
        node* tmp = create_node(data);
        tmp->next = _head;
        _head->prev = tmp;
        _head = tmp;
    }
    DELOG;
}
typename list::node* list::create_node(const T& data)
{
    LOG_ARG(data);
    node* result = _allocator.allocate(1);
    _allocator.construct(result, data);
    DELOG;
    return result;
}

extern "C"
{
    list* getNewList()
    {
#ifdef DEBUG
LOG;
DELOG;
#endif // #ifdef DEBUG
return new list;
    }

    void delList(list* L)
    {
#ifdef DEBUG
        LOG_ARG(L);
#endif // #ifdef DEBUG

        delete L;
#ifdef DEBUG
        DELOG;
#endif // #ifdef DEBUG
    }
    

    void printList(list* p)
    {
#ifdef DEBUG
        LOG_ARG(p);
#endif // #ifdef DEBUG
        std::cout << "List = [";
        for(list::iterator i = p->begin(); i != p->end(); ++i)
            std::cout << *i << ", ";
        std::cout << "\b\b]" << std::endl;
#ifdef DEBUG
        DELOG;
#endif // #ifdef DEBUG
    }
    
    
}

template <typename T2, typename B>
std::ostream& operator<<(std::ostream& os, const list<T2, B>& l)
{
    os << "List = [";
    for(typename list<T2>::iterator i = l.begin(); i != l.end(); ++i)
        os << *i << ", ";
    os << "\b\b]\n";
    return os;
}

template <typename T, typename A>
list<T, A>::list()
: _head(0), _tail(0)
{}

template <typename T, typename A>
list<T, A>::~list()
{
    node* tmp = _head;
    while (tmp->next)
    {
        tmp = tmp->next;
        _allocator.destroy(_head);
        _allocator.deallocate(_head, 1);
        _head = tmp;
    }
    _allocator.destroy(tmp);
    _allocator.deallocate(tmp, 1);
    _head = 0;
    _tail = 0;
}

template <typename T, typename A>
list<T, A>::list(const list<T, A>& other)
: _head(0), _tail(0)
{
    node *tmp = other._head;
    while (tmp->next)
    {
        push_back(tmp->data);
        tmp = tmp->next;
    }
    push_back(tmp->data);
}

template <typename T, typename A>
void list<T, A>::push_back(const T& data)
{
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
}

template <typename T, typename A>
void list<T, A>::push_front(const T& data)
{
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
}
template <typename T, typename A>
typename list<T, A>::node* list<T, A>::create_node(const T& data)
{
    node* result = _allocator.allocate(1);
    _allocator.construct(result, data);
    return result;
}
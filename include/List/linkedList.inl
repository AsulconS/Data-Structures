template <typename T> // Prefix
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
{
    this->current = this->current->rightChild;
    return (*this);
}

template <typename T> // Postfix
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    LinkedList<T>::Iterator it(this->current);
    this->current = this->current->rightChild;
    return it;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator+(uint32 offset) const
{
    LinkedList<T>::Iterator it(*this);
    while(offset--)
    {
        if(it.current != nullptr)
            it.current = it.current->rightChild;
        else break;
    }
    return it;
}

template <typename T>
void LinkedList<T>::print() const
{
    std::cout << "[ ";
    LinkedList<T>::Iterator it;
    for(it = _begin; it != _end; ++it)
        std::cout << (*it)->data << ' ';
    std::cout << ']' << std::endl;
}

template <typename T>
T LinkedList<T>::get(const LinkedList<T>::Iterator& pos) const
{
    return (pos.current != nullptr) ? (pos.current)->data : T {} ;
}

template <typename T>
template <typename TArg>
typename LinkedList<T>::Iterator LinkedList<T>::find(TArg&& v0) const
{
    LinkedList<T>::Iterator it;
    for(it = _begin; it != _end; ++it)
        if((*it)->data == v0)
            return it;

    return _end;
}

template <typename T>
void LinkedList<T>::swap(const std::size_t pos)
{
    LinkedList<T>::Iterator prev = _begin + (pos - 1);
    LinkedList<T>::Iterator current = prev + 1;
    LinkedList<T>::Iterator next = current + 1;

    (*prev)->rightChild = (*current)->rightChild;
    (*current)->rightChild = (*next)->rightChild;
    (*next)->rightChild = (*current);
}

template <typename T>
template <typename TArg>
void LinkedList<T>::push_front(TArg&& v0)
{
    if(!_size)
    {
        head = new GenericNode<T>(std::forward<TArg>(v0));
        last = head;
        _begin.current = head;
        ++_size;
        return;
    }

    GenericNode<T>* node = new GenericNode<T>(std::forward<TArg>(v0));
    node->rightChild = head;
    head = node;
    _begin.current = head;

    ++_size;
}

template <typename T>
template <typename TArg>
void LinkedList<T>::push_back(TArg&& v0)
{
    if(!_size)
    {
        head = new GenericNode<T>(std::forward<TArg>(v0));
        last = head;
        _begin.current = head;
        ++_size;
        return;
    }

    GenericNode<T>* node = new GenericNode<T>(std::forward<TArg>(v0));
    last->rightChild = node;
    last = node;

    ++_size;
}

template <typename T>
void LinkedList<T>::pop_front()
{
    if(!_size)
        return;
    
    if(_size == 1)
    {
        clear();
        return;
    }

    GenericNode<T>* nodeToDelete = head;
    head = head->rightChild;
    _begin.current = head;

    delete nodeToDelete;
    --_size;
}

template <typename T>
void LinkedList<T>::pop_back()
{
    if(!_size)
        return;
    
    if(_size == 1)
    {
        clear();
        return;
    }

    LinkedList<T>::Iterator it = _begin + (_size - 2);
    delete (*it)->rightChild;
    (*it)->rightChild = nullptr;
    last = (*it);

    --_size;
}

template <typename T>
void LinkedList<T>::erase(const LinkedList<T>::Iterator& pos)
{
    if(!_size)
        return;
    
    if(_size == 1)
    {
        clear();
        return;
    }

    GenericNode<T>* nodeToDelete = (*pos)->rightChild;
    (*pos)->rightChild = nodeToDelete->rightChild;

    delete nodeToDelete;
    --_size;
}

template <typename T>
void LinkedList<T>::clear()
{
    LinkedList<T>::Iterator it;
    for(it = _begin; it != _end; ++it)
        delete (*it);
    head = nullptr;
    last = nullptr;
    _begin.current = nullptr;
    _size = 0;
}

template <typename T> // Prefix
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
    this->current = this->current->rightChild;
    return (*this);
}

template <typename T> // Postfix
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
    List<T>::Iterator it(this->current);
    this->current = this->current->rightChild;
    return it;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator+(uint32 offset) const
{
    List<T>::Iterator it(*this);
    while(offset--)
        it.current = it.current->rightChild;

    return it;
}

template <typename T> // Prefix
typename List<T>::Iterator& List<T>::Iterator::operator--()
{
    this->current = this->current->leftChild;
    return (*this);
}

template <typename T> // Postfix
typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
    List<T>::Iterator it(this->current);
    this->current = this->current->leftChild;
    return it;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator-(uint32 offset) const
{
    List<T>::Iterator it(*this);
    while(offset--)
    {
        if(it.current != nullptr)
            it.current = it.current->leftChild;
        else break;
    }
    return it;
}

template <typename T>
List<T>::List(std::initializer_list<T>&& l) : List<T>()
{
    for(const auto& v : l)
        push_back(v);
}

template <typename T>
List<T>::List(BSTree<T>& bst) : List<T>()
{
    std::vector<T> data;
    bst.getTraverseInOrder(data);
    for(const auto& v : data)
        push_back(v);
}

template <typename T>
void List<T>::print() const
{
    std::cout << "[ ";
    List<T>::Iterator it;
    std::size_t counter { _size };
    for(it = _begin; (it != _end) && (counter--) ; ++it)
        std::cout << (*it)->data << ' ';
    std::cout << ']' << std::endl;
}

template <typename T>
T List<T>::get(const List<T>::Iterator& pos) const
{
    return (pos.current != nullptr) ? (pos.current)->data : T {} ;
}

template <typename T>
template <typename TArg>
typename List<T>::Iterator List<T>::find(TArg&& v0) const
{
    List<T>::Iterator it;
    std::size_t counter { _size };
    for(it = _begin; (it != _end) && (counter--); ++it)
        if((*it)->data == v0)
            return it;

    return _end;
}

template <typename T>
void List<T>::swap(const List<T>::Iterator& pos)
{
    List<T>::Iterator prev = pos - 1;
    List<T>::Iterator next = pos + 2;

    List<T>::Iterator current01 = pos;
    List<T>::Iterator current02 = pos + 1;

    (*prev)->rightChild = (*current02);
    (*current02)->rightChild = (*current01);
    (*current01)->rightChild = (*next);

    (*next)->leftChild = (*current01);
    (*current01)->leftChild = (*current02);
    (*current02)->leftChild = (*prev);
}

template <typename T>
template <typename TArg>
void List<T>::push_front(TArg&& v0)
{
    if(!_size)
    {
        head = new GenericNode<T>(std::forward<TArg>(v0));
        head->rightChild = head;
        head->leftChild = head;

        last = head;
        _begin.current = head;
        ++_size;
        return;
    }

    GenericNode<T>* node = new GenericNode<T>(std::forward<TArg>(v0));
    node->rightChild = head;
    head->leftChild  = node;
    head = node;
    head->leftChild = last;
    _begin.current = head;

    ++_size;
}

template <typename T>
template <typename TArg>
void List<T>::push_back(TArg&& v0)
{
    if(!_size)
    {
        head = new GenericNode<T>(std::forward<TArg>(v0));
        head->rightChild = head;
        head->leftChild = head;

        last = head;
        _begin.current = head;
        ++_size;
        return;
    }

    GenericNode<T>* node = new GenericNode<T>(std::forward<TArg>(v0));
    last->rightChild = node;
    node->leftChild  = last;
    last = node;
    last->rightChild = head;

    ++_size;
}

template <typename T>
template <typename TArg>
void List<T>::insert(TArg&& v0, const List<T>::Iterator& pos)
{
    if(!_size)
    {
        head = new GenericNode<T>(std::forward<TArg>(v0));
        head->rightChild = head;
        head->leftChild = head;

        last = head;
        _begin.current = head;
        ++_size;
        return;
    }

    if(pos.current == last)
    {
        push_back(v0);
        return;
    }

    List<T>::Iterator it = pos;
    GenericNode<T>* node = new GenericNode<T>(std::forward<TArg>(v0));
    node->rightChild = (*it)->rightChild;
    (*it)->rightChild = node;
    ++_size;
}

template <typename T>
void List<T>::pop_front()
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
    head->leftChild = last;
    _begin.current = head;

    delete nodeToDelete;
    --_size;
}

template <typename T>
void List<T>::pop_back()
{
    if(!_size)
        return;
    
    if(_size == 1)
    {
        clear();
        return;
    }

    last = last->leftChild;
    delete last->rightChild;
    last->rightChild = head;

    --_size;
}

template <typename T>
void List<T>::erase(const List<T>::Iterator& pos)
{
    if(!_size)
        return;
    
    if(_size == 1)
    {
        clear();
        return;
    }

    if(pos.current == last)
    {
        pop_back();
        return;
    }

    GenericNode<T>* nodeToDelete = (*pos)->rightChild;
    (*pos)->rightChild->rightChild->leftChild = (*pos);
    (*pos)->rightChild = (*pos)->rightChild->rightChild;

    delete nodeToDelete;
    --_size;
}

template <typename T>
void List<T>::clear()
{
    List<T>::Iterator it;
    std::size_t counter { _size };
    for(it = _begin; (it != _end) && (counter--); ++it)
        delete (*it);
    head = nullptr;
    last = nullptr;
    _begin.current = nullptr;
    _size = 0;
}

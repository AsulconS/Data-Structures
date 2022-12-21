template <typename T> // Prefix
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
    ++this->current;
    return (*this);
}

template <typename T> // Postfix
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
{
    Vector<T>::Iterator it(this->current);
    ++this->current;
    return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+(uint32 offset) const
{
    return Vector<T>::Iterator {this->current + offset};
}

template <typename T>
Vector<T>::Vector() : size(0), _begin(Vector<T>::Iterator(nullptr)), _end(Vector<T>::Iterator(nullptr))
{
    data = new T[0];
    size = 0;
}

template <typename T>
Vector<T>::Vector(const Vector& o) : size(o.size), _begin(o._begin), _end(o._end)
{
    data = new T[o.size];
    size = o.size;
    for(int i = 0; i < size; ++i)
        data[i] = o.data[i];
}

template <typename T>
Vector<T>::Vector(const T* nData, const int nSize)
{
    data = new T[nSize];
    size = nSize;
    for(int i = 0; i < size; ++i)
        data[i] = nData[i];
    
    _begin = Vector<T>::Iterator(data);
    _end = Vector<T>::Iterator(data + size);
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T>& l) : Vector<T>()
{
    for(const auto& v : l)
        push_back(v);
}

template <typename T>
void Vector<T>::push_back(const T& v)
{
    resize(size + 1);
    data[size - 1] = v;
    _begin = Vector<T>::Iterator(data);
}

template <typename T>
void Vector<T>::insert(const int pos, const T& v)
{
    if(pos >= 0 && pos <= size)
    {
        resize(size + 1);
        for(int i = size - 1; i > pos; --i)
            data[i] = data[i - 1];
        data[pos] = v;
    }
    else
    {
        std::cerr << "Invalid insertion!" << std::endl;
    }
}

template <typename T>
void Vector<T>::erase(const int pos)
{
    if(pos >= 0 && pos < size)
    {
        for(int i = pos; i < size - 1; ++i)
            data[i] = data[i + 1];
        resize(size - 1);
    }
    else
    {
        std::cerr << "Invalid erase!" << std::endl;
    }
}

template <typename T>
void Vector<T>::clear()
{
    _begin = Vector<T>::Iterator(nullptr);
    resize(0);
    _end = Vector<T>::Iterator(nullptr);
}

template <typename T>
T& Vector<T>::operator[](const int i)
{
    return data[i];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v)
{
    if(size != v.size)
    {
        std::cerr << "Invalid asignation between different sizes arrays!" << std::endl;
        return *this;
    }
    for(int i = 0; i < size; ++i)
        data[i] = v.data[i];
    return *this;
}

template <typename T>
void Vector<T>::resize(const int nSize)
{
    T* nData = new T[nSize];
    int minSize = (nSize > size) ? size : nSize;
    for(int i = 0; i < minSize; ++i)
        nData[i] = data[i];
    delete[] data;
    data = nData;
    size = nSize;

    if(nSize)
        _end = Vector<T>::Iterator(data + size);
}

template <typename T>
std::ostream& operator<<(std::ostream& o, const Vector<T>& v)
{
    std::cout << "[ ";
    typename Vector<T>::Iterator it;
    for(it = v.begin(); it != v.end(); ++it)
        o << *(*it) << ' ';
    std::cout << ']';
    return o;
}

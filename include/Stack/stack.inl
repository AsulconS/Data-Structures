template <typename T>
Stack<T>::Stack() : m_size(0), m_capacity(2)
{
    m_data = new T[2];
}

template <typename T>
Stack<T>::Stack(const std::size_t t_capacity) : m_size(0), m_capacity(t_capacity)
{
    m_data = new T[m_capacity];
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] m_data;
}

template <typename T>
void Stack<T>::push(const T& val)
{
    if(m_size >= m_capacity)
    {
        realloc();
    }
    m_data[m_size++] = val;
}

template <typename T>
T Stack<T>::top()
{
    if(!empty())
    {
        return m_data[m_size - 1];
    }
    return T {};
}

template <typename T>
T Stack<T>::pop()
{
    if(!empty())
    {
        return m_data[--m_size];
    }
    return T {};
}

template <typename T>
std::string Stack<T>::getStr()
{
    std::stringstream sStr;
    sStr << m_size << " [ ";
    for(int i = 0; i < m_size; ++i)
    {
        sStr << (int)m_data[i] << ' ';
    }
    sStr << " ]";

    return sStr.str();
}

template <typename T>
std::string Stack<T>::getStrN()
{
    std::stringstream sStr;
    sStr << m_size << " [ ";
    for(int i = 0; i < m_size; ++i)
    {
        sStr << m_data[i]->data << ' ';
    }
    sStr << " ]";

    return sStr.str();
}

template <typename T>
void Stack<T>::realloc()
{
    m_capacity <<= 1;
    T* data = new T[m_capacity];
    for(size_t i = 0; i < m_size; ++i)
        data[i] = m_data[i];
    delete[] m_data;
    m_data = data;
}

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template <typename T>
class Vector
{
public:
    class Iterator : public IIterator<Vector<T>::Iterator, T>
    {
    public:
        explicit Iterator() : IIterator<Vector<T>::Iterator, T>() {}
        explicit Iterator(T* _current) : IIterator<Vector<T>::Iterator, T>(_current) {}
        virtual ~Iterator() {}

        virtual Iterator& operator=(const Iterator& o) override { this->current = o.current; return (*this); }

        virtual Iterator& operator++() override; // Prefix
        virtual Iterator operator++(int) override; // Postfix
        virtual Iterator operator+(uint32 offset) const override;
    };

public:
    Vector();
    Vector(const Vector& o);
    Vector(const T* nData, const int nSize);
    virtual ~Vector() { delete[] data; }

    Vector(const std::initializer_list<T>& l);

    void push_back(const T& v);
    void insert(const int pos, const T& v);
    void erase(const int pos);
    void clear();

    inline const Vector<T>::Iterator& begin() const & { return this->_begin; }
    inline const Vector<T>::Iterator& end() const & { return this->_end; }

    inline const std::size_t getSize() const { return size; }

    inline T* get(const int pos) { return (pos >= 0 && pos < size) ? &data[pos] : NULL; }
    inline const T* get(const int pos) const { return (pos >= 0 && pos < size) ? &data[pos] : NULL; }

    T& operator[](const int i);
    Vector& operator=(const Vector& v);

private:
    T* data;
    std::size_t size;

    Vector<T>::Iterator _begin;
    Vector<T>::Iterator _end;

    void resize(const int newSize);
};

#endif // VECTOR_HPP

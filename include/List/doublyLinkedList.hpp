#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "core/common.hpp"
#include "core/iterator.hpp"
#include "core/genericNode.hpp"

#include "BST/BST.hpp"

template <typename T>
class List
{
public:
    class Iterator : public IIterator<List<T>::Iterator, GenericNode<T>>
    {
    public:
        explicit Iterator() : IIterator<List<T>::Iterator, GenericNode<T>>() {}
        explicit Iterator(GenericNode<T>* _current) : IIterator<List<T>::Iterator, GenericNode<T>>(_current) {}
        virtual ~Iterator() {}

        virtual Iterator& operator=(const Iterator& o) override { this->current = o.current; return (*this); }

        virtual Iterator& operator++() override; // Prefix
        virtual Iterator operator++(int) override; // Postfix
        virtual Iterator operator+(uint32 offset) const override;

        Iterator& operator--(); // Prefix
        Iterator operator--(int); // Postfix
        Iterator operator-(uint32 offset) const;
    };

public:
    explicit List() : head(nullptr), last(nullptr), _size(0), _begin(List<T>::Iterator(nullptr)), _end(List<T>::Iterator(nullptr)) {}
    explicit List(const T& _head) : head(new GenericNode<T>(_head)), last(head), _size(1), _begin(List<T>::Iterator(head)), _end(List<T>::Iterator(nullptr)) {}
    virtual ~List() { clear(); }

    List(const List& o) : head(o.head), last(o.last), _size(o._size), _begin(o._begin), _end(o._end) {}

    List(std::initializer_list<T>&& l);

    List(BSTree<T>& bst);

    inline const List<T>::Iterator& begin() const & { return this->_begin; }
    inline const List<T>::Iterator& end() const & { return this->_end; }

    void print() const;
    inline std::size_t size() const { return this->_size; }
    inline bool empty() const { return !this->_size; }

    T get(const List<T>::Iterator& pos) const;
    inline T front() { return *head; }
    inline T back() { return *last; }
    template <typename TArg> List<T>::Iterator find(TArg&& v0) const;

    void swap(const List<T>::Iterator& pos);

    template <typename TArg> void push_front(TArg&& v0);
    template <typename TArg> void push_back(TArg&& v0);
    template <typename TArg> void insert(TArg&& v0, const typename List<T>::Iterator& pos);

    void pop_front();
    void pop_back();
    void erase(const List<T>::Iterator& pos);
    void clear();
    
protected:
    GenericNode<T>* head;
    GenericNode<T>* last;
    std::size_t _size;

    List<T>::Iterator _begin;
    List<T>::Iterator _end;
};

#endif // DOUBLY_LINKED_LIST_H

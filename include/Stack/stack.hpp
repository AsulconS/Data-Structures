#ifndef STACK_H
#define STACK_H

#include <sstream>

#include "core/common.hpp"

template <typename T>
class Stack
{
public:
    Stack();
    Stack(const std::size_t t_capacity);
    virtual ~Stack();

    void clear() { m_size = 0; }

    inline bool empty() { return !m_size; }
    inline std::size_t getSize() { return m_size; }

    void push(const T& val);

    T top();
    T pop();

    std::string getStr();
    std::string getStrN();

private:
    T* m_data;

    std::size_t m_size;
    std::size_t m_capacity;

    void realloc();
};

#endif // STACK_H

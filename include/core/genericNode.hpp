#ifndef GENERIC_NODE_HPP
#define GENERIC_NODE_HPP

#include "core/common.hpp"

template <typename T>
struct GenericNode
{
public:
    T data;
    GenericNode<T>* left;
    GenericNode<T>* right;

    std::string label;
};

#endif // GENERIC_NODE_HPP

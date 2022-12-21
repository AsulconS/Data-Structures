#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP

#include "core/common.hpp"

template <typename T>
struct AVLNode
{
public:
    T data;
    int8 height;
    AVLNode<T>* left;
    AVLNode<T>* right;

    std::string label;
};

#endif // AVL_NODE_HPP

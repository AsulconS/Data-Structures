#ifndef RED_BLACK_NODE_HPP
#define RED_BLACK_NODE_HPP

#include "core/common.hpp"

#define c_red true
#define c_black false

template <typename T>
struct RedBlackNode
{
public:
    T data;
    bool color;
    RedBlackNode<T>* left;
    RedBlackNode<T>* right;

    std::string label;
};

#endif // RED_BLACK_NODE_HPP

#ifndef BST_HPP
#define BST_HPP

#include <string>

#include "core/common.hpp"
#include "core/genericNode.hpp"
#include "BST/iBST.hpp"

template <typename T>
class BST : public IBST<T, GenericNode<T>>
{
    using Node = GenericNode<T>;
    using IBST<T, GenericNode<T>>::m_root;
    using IBST<T, GenericNode<T>>::m_nodes;
    using IBST<T, GenericNode<T>>::find;
    using IBST<T, GenericNode<T>>::findMinNode;

public:
    BST() : IBST<T, Node>() {}
    BST(Node* t_root) : IBST<T, Node>(t_root) {}
    BST(const std::initializer_list<T>& l);
    virtual ~BST() {}

    virtual void insertNode(const T& value) override;
    virtual void insertNode(const T& value, Node*& root) override;

    virtual void deleteNode(const T& value) override;
    virtual void deleteNode(const T& value, Node*& root) override;

protected:
    virtual void labelNode(Node* node) override;
    virtual const char* thisName() override { return "BST"; }
};

#endif // BST_HPP

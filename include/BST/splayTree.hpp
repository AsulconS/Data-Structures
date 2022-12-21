#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP

#include <string>
#include <vector>

#include "core/common.hpp"
#include "core/genericNode.hpp"
#include "BST/iBST.hpp"

template <typename T>
class SplayTree : public IBST<T, GenericNode<T>>
{
    using Node = GenericNode<T>;
    using IBST<T, GenericNode<T>>::m_root;
    using IBST<T, GenericNode<T>>::m_nodes;
    using IBST<T, GenericNode<T>>::find;
    using IBST<T, GenericNode<T>>::findMinNode;
    using IBST<T, GenericNode<T>>::findMaxNode;
    using IBST<T, GenericNode<T>>::debugMode;

public:
    SplayTree() : IBST<T, Node>() {}
    SplayTree(Node* t_root) : IBST<T, Node>(t_root) {}
    SplayTree(const std::vector<T>& data);
    SplayTree(const std::initializer_list<T>& l);
    virtual ~SplayTree() {}

    virtual Node* find(const T& value) override;

    virtual void insertNode(const T& value) override;
    virtual void insertNode(const T& value, Node*& root) override;

    virtual void deleteNode(const T& value) override;
    virtual void deleteNode(const T& value, Node*& root) override;

protected:
    virtual void labelNode(Node* node) override;
    virtual const char* thisName() override { return "SplayTree"; }

private:
    void splay(Node*& root, Node* leaf);

    void rotateZig(Node*& root);
    void rotateZag(Node*& root);
    void rotateZigZig(Node*& root);
    void rotateZagZag(Node*& root);
    void rotateZigZag(Node*& root);
    void rotateZagZig(Node*& root);

    Stack<Node*> m_predecessors;
};

#endif // SPLAY_TREE_HPP

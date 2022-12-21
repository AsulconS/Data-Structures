#ifndef AVL_HPP
#define AVL_HPP

#include <string>
#include <vector>

#include "core/common.hpp"
#include "core/avlNode.hpp"
#include "BST/iBST.hpp"

constexpr int8 IMBALANCE_CONSTANT {1};

template <typename T>
class AVL : public IBST<T, AVLNode<T>>
{
    using Node = AVLNode<T>;
    using IBST<T, AVLNode<T>>::m_root;
    using IBST<T, AVLNode<T>>::m_nodes;
    using IBST<T, AVLNode<T>>::find;
    using IBST<T, AVLNode<T>>::findMinNode;
    using IBST<T, AVLNode<T>>::findMaxNode;
    using IBST<T, AVLNode<T>>::debugMode;

public:
    AVL() : IBST<T, Node>() {}
    AVL(Node* t_root) : IBST<T, Node>(t_root) {}
    AVL(const std::vector<T>& data);
    AVL(const std::initializer_list<T>& l);
    virtual ~AVL() {}

    virtual void insertNode(const T& value) override;
    virtual void insertNode(const T& value, Node*& root) override;

    virtual void deleteNode(const T& value) override;
    virtual void deleteNode(const T& value, Node*& root) override;

protected:
    virtual void labelNode(Node* node) override;
    virtual const char* thisName() override { return "AVL"; }

private:
    int8 height(Node* node);
    void balance(Node*& root, Node* leaf);

    void rotateLeft(Node*& root);
    void rotateRight(Node*& root);
    void rotateLeftRight(Node*& root);
    void rotateRightLeft(Node*& root);
};

#endif // AVL_HPP

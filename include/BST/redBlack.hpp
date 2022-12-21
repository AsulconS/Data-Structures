#ifndef RED_BLACK_HPP
#define RED_BLACK_HPP

#include <string>
#include <vector>

#include "core/common.hpp"
#include "core/redBlackNode.hpp"
#include "BST/iBST.hpp"

template <typename T>
class RedBlack : public IBST<T, RedBlackNode<T>>
{
    using Node = RedBlackNode<T>;
    using IBST<T, RedBlackNode<T>>::m_root;
    using IBST<T, RedBlackNode<T>>::m_nodes;
    using IBST<T, RedBlackNode<T>>::findMinNode;
    using IBST<T, RedBlackNode<T>>::findMaxNode;
    using IBST<T, RedBlackNode<T>>::debugMode;

public:
    RedBlack() : IBST<T, Node>() {}
    RedBlack(Node* t_root) : IBST<T, Node>(t_root) {}
    RedBlack(const std::vector<T>& data);
    RedBlack(const std::initializer_list<T>& l);
    virtual ~RedBlack() {}

    virtual void insertNode(const T& value) override;
    virtual void insertNode(const T& value, Node*& root) override;

    virtual void deleteNode(const T& value) override;
    virtual void deleteNode(const T& value, Node*& root) override;

protected:
    virtual void labelNode(Node* node) override;
    virtual const char* thisName() override { return "RedBlack"; }

private:
    bool color(Node* node);
    void swapColor(Node* lNode, Node* rNode);
    void recolorPU(Node* grandParent);
    void balance(Node*& root, Node* leaf);

    void rotateLeft(Node*& root);
    void rotateRight(Node*& root);
    void rotateLeftRight(Node*& root);
    void rotateRightLeft(Node*& root);
};

#endif // RED_BLACK_HPP


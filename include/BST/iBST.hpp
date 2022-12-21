#ifndef IBST_HPP
#define IBST_HPP

#include <string>
#include <fstream>
#include <iostream>

#include "core/common.hpp"
#include "core/genericNode.hpp"
#include "Stack/stack.hpp"

template <typename T, typename Node>
class IBST
{
public:
    IBST() : m_root(nullptr) {}
    IBST(Node* t_root) : m_root(t_root) { labelNode(m_root); }
    virtual ~IBST();

    void makeEmpty();
    void makeEmpty(Node* root);

    virtual Node* find(const T& value);
    virtual Node* find(const T& value, Node*& root);

    Node* findMinNode();
    Node* findMinNode(Node*& root);

    Node* findMaxNode();
    Node* findMaxNode(Node*& root);

    virtual void insertNode(const T& value) = 0;
    virtual void insertNode(const T& value, Node*& root) = 0;

    virtual void deleteNode(const T& value) = 0;
    virtual void deleteNode(const T& value, Node*& root) = 0;

    void traverseInOrder();
    void traversePreOrder();
    void traversePostOrder();

    void traverseInOrder(Node* root);
    void traversePreOrder(Node* root);
    void traversePostOrder(Node* root);

    void recursiveTInOrder();
    void recursiveTPreOrder();
    void recursiveTPostOrder();
    
    void recursiveTInOrder(Node* root);
    void recursiveTPreOrder(Node* root);
    void recursiveTPostOrder(Node* root);

    void exportToFile(const std::string& title);

    static void setDebugMode(const bool mode) { debugMode = mode; }

    static uint32 getFilesCount() { return filesCount; };

protected:
    virtual void labelNode(Node* node) = 0;
    virtual const char* thisName() = 0;

    Node* m_root;
    Stack<Node*> m_nodes;

    static bool debugMode;

private:
    static uint32 filesCount;
};

#endif // IBST_HPP

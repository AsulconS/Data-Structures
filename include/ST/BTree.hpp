#ifndef BTREE_HPP
#define BTREE_HPP

#include <fstream>

#include <queue>
#include <unordered_map>

#include "core/BTreeNode.hpp"

template <typename T, int N>
class BTree
{
    using Node = BTreeNode<T, N>;

public:
    BTree();
    BTree(Node* t_root);
    BTree(const std::vector<AttachedPair<T>>& data);
    BTree(const std::initializer_list<AttachedPair<T>>& l);
    virtual ~BTree();

    void makeEmpty();
    void makeEmpty(Node* root);

    virtual Node* find(const AttachedPair<T>& value, int& index);
    virtual Node* find(const AttachedPair<T>& value, Node*& root, int& index);

    virtual void insertKey(const AttachedPair<T>& value);
    virtual void insertKey(const AttachedPair<T>& value, Node*& root);

    virtual void updateKey(const Node* node);

    virtual void deleteKey(const AttachedPair<T>& value);
    virtual void deleteKey(const AttachedPair<T>& value, Node*& root);

    void loadAll();
    void loadAll(Node*& root);

    void exportToFile(const std::string& title, bool isFinal = false);

    static void setDebugMode(const bool mode) { m_debugMode = mode; }

    static uint32 getFilesCount() { return m_filesCount; };

protected:
    virtual void labelNode(Node* node);
    virtual const char* thisName() { return "BTree"; };

    void splitChild(Node* node, const std::size_t index);
    void insertKeyNonFull(const AttachedPair<T>& value, Node*& root);

    void clearFile();
    void createFileIfNotExists();

    void diskWrite(const Node* node);
    void diskRead(Node*& node, const std::size_t index);

    std::size_t allocate();
    std::size_t getRootIndex();

    void setRootIndex(const std::size_t index);
    void setTransactionState(const char state);

    Node* m_root;
    Stack<Node*> m_nodes;
    std::fstream m_file;
    std::fstream m_bkFile;
    std::fstream m_flagsFile;

    std::fstream* m_writeTarget;

    bool m_lockPhase;
    std::unordered_map<int, std::queue<std::pair<char, int>>> m_lockTable;

    std::size_t m_nextIndex;

    static bool m_debugMode;

private:
    static uint32 m_filesCount;
};

#endif // BTREE_HPP

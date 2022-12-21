#ifndef B_TREE_HPP
#define B_TREE_HPP

#include "core/common.hpp"
#include "core/utils.hpp"
#include "core/attachedPair.hpp"

#define sizeof_BTNRelevantData(T, N) offsetof(unparentheses_type((BTreeNode<T, N>)), children)

template <typename T, int N>
struct BTreeNode
{
public:
    // Relevant Data
    // -------------
    AttachedPair<T> data[N - 1];
    std::size_t size;

    std::size_t index;
    std::size_t childrenIndices[N];

    bool isLeaf;
    // -------------

    BTreeNode<T, N>* children[N];
    std::string label;
};

template <typename T, int N>
void operator>>(BTreeNode<T, N>& node, const std::size_t index)
{
    for(std::size_t i = node.size + 1; i > index + 1; --i)
    {
        node.children[i] = node.children[i - 1];
        node.childrenIndices[i] = node.childrenIndices[i - 1];
    }
    for(std::size_t i = node.size; i > index; --i)
    {
        node.data[i] = node.data[i - 1];
    }
    ++node.size;
}

#endif // B_TREE_HPP

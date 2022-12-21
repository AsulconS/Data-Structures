#include <random>
#include <iostream>

#define DSTR_IMPLEMENTATION
#include "dataStructures.hpp"

int main()
{
    /*
    std::random_device rd;
    std::mt19937_64 mt(rd());
    std::uniform_real_distribution<double> distPK(0, 1024);
    std::uniform_real_distribution<double> distC1(0, 64);
    std::vector<AttachedPair<int>> randomData;
    for(int i = 0; i < 64; ++i)
    {
        randomData.push_back({(int)distPK(mt), (int)distC1(mt)});
    }
    */

    BTree<int, 4> bTree {};

    int index {};
    BTreeNode<int, 4>* node = bTree.find({361, 18}, index);
    node->data[index].body = 16;

    bTree.updateKey(node);

    bTree.exportToFile("Path B-Tree");
    bTree.exportToFile("Final B-Tree", true);

    return 0;
}

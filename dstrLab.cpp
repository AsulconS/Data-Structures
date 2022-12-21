#define  DSTR_IMPLEMENTATION
#include "dataStructures.hpp"

int main()
{
    BSTree<int> bsTree {10, 5, 16, 2, 8, 1, 9, 12, 11, 14};

    std::cout << "In-Order Traversal:" << std::endl;
    std::cout << "Iterative: "; bsTree.traverseInOrder(); std::cout << std::endl;
    std::cout << "Recursive: "; bsTree.recursiveTInOrder(); std::cout << '\n' << std::endl;

    std::cout << "Pr-Order Traversal:" << std::endl;
    std::cout << "Iterative: "; bsTree.traversePreOrder(); std::cout << std::endl;
    std::cout << "Recursive: "; bsTree.recursiveTPreOrder(); std::cout << '\n' << std::endl;

    std::cout << "Post-Order Traversal:" << std::endl;
    std::cout << "Iterative: "; bsTree.traversePostOrder(); std::cout << std::endl;
    std::cout << "Recursive: "; bsTree.recursiveTPostOrder(); std::cout << '\n' << std::endl;

    std::cout << "Is value 10? " << bsTree.search(10) << std::endl;
    std::cout << "Is value 7 ? " << bsTree.search(7)  << std::endl;
    std::cout << "Is value 1 ? " << bsTree.search(1)  << std::endl;
    std::cout << "Is value 13? " << bsTree.search(13) << std::endl;
    std::cout << "Is value 9 ? " << bsTree.search(9)  << std::endl;
    std::cout << "Is value 20? " << bsTree.search(20) << std::endl;
    std::cout << "Is value 11? " << bsTree.search(11) << std::endl;
    std::cout << "Is value 0 ? " << bsTree.search(0)  << std::endl;

    List<int> ordered(bsTree);

    ordered.print();

    return 0;
}

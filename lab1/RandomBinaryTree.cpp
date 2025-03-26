#include <iostream>
#include "RandomBinaryTree.h"


int main()
{
    RandomizedBinarySearchTree<int, int> rtree;

    const int n = 98765;
    const int k = 1234;

    for (int i = 1;i <= n;i++) {
        rtree.add(i, i);
    }

    std::cout << "Tree height: " << rtree.height() << "\n";
    std::cout << "Tree size: " << rtree.size() << " / " << n << "\n";

    int counter = 0;
    for (int i = 1;i <= n;i++) {
        if (i != rtree.get(i))
            std::cout << i << " " << rtree.get(i) << "\n";
        else
            counter++;
    }
    std::cout << "Nodes found: " << counter << " / " << n << "\n";

    for (int i = 1;i <= k;i++) {
        rtree.remove(i);
    }
    std::cout << "Removed " << k << " nodes\n";

    std::cout << "Tree height: " << rtree.height() << "\n";
    std::cout << "Tree size: " << rtree.size() << " / " << n-k << "\n";

    counter = 0;
    for (int i = 1;i <= n;i++) {
        if (i == rtree.get(i))
            counter++;
    }
    std::cout << "Nodes found: " << counter << " / " << n-k << "\n";
}

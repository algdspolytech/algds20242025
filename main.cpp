#include "functions.h"
#include "tests.h"
#define cnt 1000

int main() {
    TESTS();
    testBinaryTree(cnt);
    testAVLTree(cnt);
    return 0;
}

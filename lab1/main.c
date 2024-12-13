#include <stdio.h>
#include "functions.h"
#include "test.h"

//int main() {
//    TreeNode* root = NULL;
//
//    // Insert words into the tree
//    insert(&root, "hello");
//    insert(&root, "world");
//    insert(&root, "binary");
//    insert(&root, "tree");
//    insert(&root, "example");
//    insert(&root, "test");
//    insert(&root, "words");
//    insert(&root, "programming");
//    // Calculate widths of subtrees
//    calculateWidths(root);
//
//    // Print the tree with computed widths
//    printf("Binary Tree with Subtree Widths:\n");
//    printTree(root, 0);
//
//    // Free the allocated memory
//    freeTree(root);
//
//    return 0;
//}

int main() {
    printf("Running Tests:\n\n");
    test_empty_tree();
    test_single_node();
    test_left_skewed_tree();
    test_right_skewed_tree();
    test_duplicate_length_words();
    test_long_words();
    test_balanced_tree();
    test_special_characters();
    test_words_with_spaces();
    test_large_tree();
    printf("All tests completed.\n");
    return 0;
}
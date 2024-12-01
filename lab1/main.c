#include <stdio.h>
#include "functions.h"

int main() {
    TreeNode* root = NULL;

    // Insert words into the tree
    insert(&root, "hello");
    insert(&root, "world");
    insert(&root, "binary");
    insert(&root, "tree");
    insert(&root, "example");
    insert(&root, "test");
    insert(&root, "words");
    insert(&root, "programming");
    //=======================TESTS=======================
    // --------Empty Tree--------   1

    // --------Single Node--------  2
 
    // --------Left-Skewed Tree--------  3
    /*insert(&root, "longword");
    insert(&root, "longer");
    insert(&root, "long");
    insert(&root, "mid");
    insert(&root, "hi");
    insert(&root, "a");*/
 
    // --------Right-Skewed Tree--------  4
    /*insert(&root, "a");
    insert(&root, "hi");
    insert(&root, "mid");
    insert(&root, "long");
    insert(&root, "longer");
    insert(&root, "longword");*/

    // --------ree with Duplicate Length Words--------  5
    /*insert(&root, "cat");
    insert(&root, "dog");
    insert(&root, "bat");
    insert(&root, "owl");
    insert(&root, "ant");*/

    // --------Tree with Long Words--------  6
    /*insert(&root, "supercalifragilisticexpialidocious");
    insert(&root, "pneumonoultramicroscopicsilicovolcanoconiosis");
    insert(&root, "hippopotomonstrosesquipedaliophobia");*/

    // --------Balanced Tree--------  7
    /*insert(&root, "m");
    insert(&root, "c");
    insert(&root, "t");
    insert(&root, "a");
    insert(&root, "e");
    insert(&root, "p");
    insert(&root, "y");*/

    // --------Words with Special Characters--------  8
    /*insert(&root, "hello!");
    insert(&root, "what's");
    insert(&root, "up?");
    insert(&root, "@home");
    insert(&root, "#1");
    insert(&root, "%done");*/

    // --------Words with Spaces (Simulating Phrases)--------  9
    /*insert(&root, "good morning");
    insert(&root, "hi there");
    insert(&root, "how are you");
    insert(&root, "greetings");
    insert(&root, "salutations");*/

    // --------Very Large Tree--------  10
    /*char *words[] = {"delta", "alpha", "epsilon", "beta", "gamma", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu", "nu", "xi", "omicron", "pi", "rho", "sigma", "tau", "upsilon"};
    for (int i = 0; i < 20; i++) {
          insert(&root, words[i]);
    }*/
 
    //=======================TESTS=======================

    // Calculate widths of subtrees
    calculateWidths(root);

    // Print the tree with computed widths
    printf("Binary Tree with Subtree Widths:\n");
    printTree(root, 0);

    // Free the allocated memory
    freeTree(root);

    return 0;
}
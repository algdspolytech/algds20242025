#include <stdio.h>
#include "functions.h"
#include "test.h"

void test_empty_tree() {
    printf("Test 1: Empty Tree\n");
    TreeNode* root = NULL;
    calculateWidths(root);
    printTree(root, 0);
    printf("\n----------------------------\n\n");
}

void test_single_node() {
    printf("Test 2: Single Node\n");
    TreeNode* root = NULL;
    insert(&root, "single");
    calculateWidths(root);
    printTree(root, 0);
    freeTree(root);
    printf("\n----------------------------\n\n");
}

void test_left_skewed_tree() {
    printf("Test 3: Left-Skewed Tree\n");
    TreeNode* root = NULL;
    insert(&root, "longword");
    insert(&root, "longer");
    insert(&root, "long");
    insert(&root, "mid");
    insert(&root, "hi");
    insert(&root, "a");
    calculateWidths(root);
    printTree(root, 0);
    freeTree(root);
    printf("\n----------------------------\n\n");
}

void test_right_skewed_tree() {
    printf("Test 4: Right-Skewed Tree\n");
    TreeNode* root = NULL;
    insert(&root, "a");
    insert(&root, "hi");
    insert(&root, "mid");
    insert(&root, "long");
    insert(&root, "longer");
    insert(&root, "longword");
    calculateWidths(root);
    printTree(root, 0);
    freeTree(root);
    printf("\n----------------------------\n\n");
}

void test_duplicate_length_words() {
    printf("Test 5: Duplicate Length Words\n");
    TreeNode* root = NULL;
    insert(&root, "cat");
    insert(&root, "dog");
    insert(&root, "bat");
    insert(&root, "owl");
    insert(&root, "ant");
    calculateWidths(root);
    printTree(root, 0);
    freeTree(root);
    printf("\n----------------------------\n\n");
}

void test_long_words() {
    printf("Test 6: Tree with Long Words\n");
    TreeNode* root = NULL;
    insert(&root, "supercalifragilisticexpialidocious");
    insert(&root, "pneumonoultramicroscopicsilicovolcanoconiosis");
    insert(&root, "hippopotomonstrosesquipedaliophobia");
    calculateWidths(root);
    printTree(root, 0);
    freeTree(root);
    printf("\n----------------------------\n\n");
}

void test_balanced_tree() {
    printf("Test 7: Balanced Tree\n");
    TreeNode* root = NULL;
    insert(&root, "m");
    insert(&root, "c");
    insert(&root, "t");
    insert(&root, "a");
    insert(&root, "e");
    insert(&root, "p");
    insert(&root, "y");
    calculateWidths(root);
    printTree(root, 0);
    freeTree(root);
    printf("\n----------------------------\n\n");
}

void test_special_characters() {
    printf("Test 8: Words with Special Characters\n");
    TreeNode* root = NULL;
    insert(&root, "hello!");
    insert(&root, "what's");
    insert(&root, "up?");
    insert(&root, "@home");
    insert(&root, "#1");
    insert(&root, "%done");
    calculateWidths(root);
    printTree(root, 0);
    freeTree(root);
    printf("\n----------------------------\n\n");
}

void test_words_with_spaces() {
    printf("Test 9: Words with Spaces\n");
    TreeNode* root = NULL;
    insert(&root, "good morning");
    insert(&root, "hi there");
    insert(&root, "how are you");
    insert(&root, "greetings");
    insert(&root, "salutations");
    calculateWidths(root);
    printTree(root, 0);
    freeTree(root);
    printf("\n----------------------------\n\n");
}

void test_large_tree() {
    printf("Test 10: Very Large Tree\n");
    TreeNode* root = NULL;
    char* words[] = { "delta", "alpha", "epsilon", "beta", "gamma", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu", "nu", "xi", "omicron", "pi", "rho", "sigma", "tau", "upsilon" };
    for (int i = 0; i < 20; i++) {
        insert(&root, words[i]);
    }
    calculateWidths(root);
    printTree(root, 0);
    freeTree(root);
    printf("\n----------------------------\n\n");
}
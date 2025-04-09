#include "pch.h"
#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>


extern "C" {
#include "..\Printtree\printtree.h"
#include "..\Printtree\printtree.c"
}

TEST(PrintTreeTest, Test1) {
    node* left = createnode(1, NULL, NULL);
    node* right = createnode(2, NULL, NULL);
    node* root = createnode(3, left, right);

    EXPECT_EQ(root->x, 3);
    EXPECT_EQ(root->left->x, 1);
    EXPECT_EQ(root->right->x, 2);

    freetree(root);
}

TEST(PrintTreeTest, Test2) {
    node* left = createnode(1, NULL, NULL);
    node* right = createnode(2, NULL, NULL);
    node* root = createnode(3, left, right);

    EXPECT_NO_THROW(freetree(root));  
}

TEST(PrintTreeTest, Test3) {
    node* deeptree = createnode(3, createnode(1, NULL, NULL), createnode(2, NULL, NULL));
    EXPECT_EQ(getdepth(deeptree), 2);

    freetree(deeptree);
}

TEST(PrintTreeTest, Test4) {
    FILE* testfile = tmpfile();
    fprintf(testfile, "1 2 3 4 5 6 7");
    rewind(testfile);

    node* root = readtree(testfile);
    EXPECT_EQ(root->x, 1); 
    EXPECT_EQ(getdepth(root), 3);

    freetree(root);
    fclose(testfile);
}

TEST(PrintTreeTest, Test5) {
    FILE* testfile = tmpfile();
    rewind(testfile);

    node* root = readtree(testfile);
    EXPECT_EQ(root, nullptr); 

    fclose(testfile);
}

TEST(PrintTreeTest, Test6) {
    node* left = createnode(1, NULL, NULL);
    node* right = createnode(2, NULL, NULL);
    node* root = createnode(3, left, right);

    FILE* testfile = tmpfile();
    displaytree1(testfile, root);


    char buffer[256];
    rewind(testfile);
    fgets(buffer, sizeof(buffer), testfile);
    EXPECT_TRUE(buffer[0] != '\0');

    freetree(root);
    fclose(testfile);
}

TEST(PrintTreeTest, Test7) {
    node* left = createnode(1, NULL, NULL);
    node* right = createnode(2, NULL, NULL);
    node* root = createnode(3, left, right);

    FILE* testfile = tmpfile();
    displaytree2(testfile, root);

    char buffer[256];
    rewind(testfile);
    fgets(buffer, sizeof(buffer), testfile);
    EXPECT_TRUE(buffer[0] != '\0');

    freetree(root);
    fclose(testfile);
}

TEST(PrintTreeTest, Test8) {
    node* left = createnode(1, NULL, NULL);
    node* right = createnode(2, NULL, NULL);
    node* root = createnode(3, left, right);
    FILE* testfile = tmpfile();
    displaytree1(testfile, root);
    rewind(testfile);

    char buffer[256];
    fgets(buffer, sizeof(buffer), testfile);  
    EXPECT_TRUE(buffer[0] != '\0');
    EXPECT_NE(strstr(buffer, "3"), nullptr);

    fgets(buffer, sizeof(buffer), testfile); 
    EXPECT_NE(strstr(buffer, "1"), nullptr); 
    EXPECT_NE(strstr(buffer, "2"), nullptr); 

    freetree(root);
    fclose(testfile);
}

TEST(PrintTreeTest, Test9) {
    node* root = createnode(1, NULL, NULL);

    EXPECT_EQ(getdepth(root), 1);

    freetree(root);
}

TEST(PrintTreeTest, Test10) {
    //         5
    //       /   \
    //     3      8
    //    / \    /  \
    //   1   4  7    9

    node* left_left = createnode(1, NULL, NULL);
    node* left_right = createnode(4, NULL, NULL);
    node* right_left = createnode(7, NULL, NULL);
    node* right_right = createnode(9, NULL, NULL);
    node* left = createnode(3, left_left, left_right);
    node* right = createnode(8, right_left, right_right);
    node* root = createnode(5, left, right);

    EXPECT_EQ(root->x, 5);
    EXPECT_EQ(root->left->x, 3);
    EXPECT_EQ(root->right->x, 8);
    EXPECT_EQ(root->left->left->x, 1);
    EXPECT_EQ(root->left->right->x, 4);
    EXPECT_EQ(root->right->left->x, 7);
    EXPECT_EQ(root->right->right->x, 9);

    EXPECT_EQ(root->left->left->left, nullptr);
    EXPECT_EQ(root->left->left->right, nullptr);
    EXPECT_EQ(root->left->right->left, nullptr);
    EXPECT_EQ(root->left->right->right, nullptr);
    EXPECT_EQ(root->right->left->left, nullptr);
    EXPECT_EQ(root->right->left->right, nullptr);
    EXPECT_EQ(root->right->right->left, nullptr);
    EXPECT_EQ(root->right->right->right, nullptr);

    freetree(root);
}

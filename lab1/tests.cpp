
#include <gtest/gtest.h>  
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string.h>
#include "algos1.h"

TEST(CreateNodeTest, CreateNode_ValidName_no1) {
    Node* node = create_node("root");
    ASSERT_STREQ(node->name, "root");
    free_tree(node);
}

TEST(CreateNodeTest, CreateNode_ChildCountZero_no2) {
    Node* node = create_node("root");
    ASSERT_EQ(node->child_count, 0);
    free_tree(node);
}


TEST(CreateNodeTest, CreateNode_EmptyName_no3) {
    Node* node = create_node("");
    ASSERT_STREQ(node->name, "");
    free_tree(node);
}

TEST(CreateNodeTest, CreateNode_LongName_no4) {
    const char* long_name = "verylongfoldernameexceedingmaxlength";
    Node* node = create_node(long_name);
    ASSERT_EQ(strlen(node->name), MAX_NAME_LENGTH - 1);
    free_tree(node);
}


TEST(AddPathTest, AddPath_SingleLevel_no5) {
    Node* root = create_node("root");
    add_path(root, "folder1");
    ASSERT_STREQ(root->children[0]->name, "folder1");
    free_tree(root);
}


TEST(AddPathTest, AddPath_ChildCount_no6) {
    Node* root = create_node("root");
    add_path(root, "folder1");
    ASSERT_EQ(root->child_count, 1);
    free_tree(root);
}

TEST(AddPathTest, AddPath_LongName_no7) {
    const char* long_name = "verylongfoldernameexceedingmaxlength";
    Node* root = create_node("root");
    add_path(root, long_name);

    ASSERT_EQ(strlen(root->children[0]->name), MAX_NAME_LENGTH - 1);
    free_tree(root);
}

TEST(CompareTest, Compare_NodeComparation_no8) {
    Node* node1 = create_node("abca");
    Node* node2 = create_node("abcd");

    EXPECT_LT(compare(&node1, &node2), 0);

    free(node1);
    free(node2);
}

TEST(PrintTreeTest, PrintTree_SortedChildrenCheckOrder_no9) {
    Node* root = create_node("root");
    add_path(root, "folderB/folderD");
    add_path(root, "folderA/folderC");

    FILE* temp_file = tmpfile();
    print_tree(root, 0, temp_file);
    rewind(temp_file);
    char buffer[100];
    fgets(buffer, sizeof(buffer), temp_file);
    ASSERT_STREQ(buffer, "folderA/\n");

    free_tree(root);
    fclose(temp_file);
}


TEST(FreeTreeTest, AddPath_MultipleLevelsFreeMemory_no10) {
    Node* root = create_node("root");
    add_path(root, "folder1/folder2/folder3");
    ASSERT_NO_THROW(free_tree(root));
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
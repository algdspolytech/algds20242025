#include <stdio.h>
#include <gtest/gtest.h>

extern "C" {
#include <tree.h>
}

FILE* tmp(const char* name, const char* data) {
    FILE* f = fopen(name, "w");
    fprintf(f, "%s", data);
    fclose(f);

    f = fopen(name, "r");
    return f;
}

TEST(CreateTreeFromFile, TreeNo1) {
    FILE* f1 = tmp("tree1.txt",
    "3 \
         10 20 30 \
         0 1 1 \
         1 0 2 \
         2 0 -1");

    /*
    #       30(6)
    #      /
    #    20(4)
    #   /
    # 10(2)
    */

    std::vector<int> expectedReq = {2, 4, 6};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    std::vector<TREE_Node_t*> stack;
    stack.push_back(root);

    while(!stack.empty()) {
        TREE_Node_t* node = stack.back();
        stack.pop_back();

        assert(node->reqCnt == expectedReq[node->id]);

        if(node->left != NULL)
            stack.push_back(node->left);
        if(node->right != NULL)
            stack.push_back(node->right);
    }
}

TEST(CreateTreeFromFile, TreeNo2) {
    FILE* f1 = tmp("tree1.txt",
    "5\
    1 2 3 4 5\
    0 1 2\
    1 0 2\
    2 1 4\
    3 0 4\
    4 0 -1");

    /*
    #         5(5)
    #       /   \
    #     3(3)    4(1)
    #    /    \
    #   1(1)   2(1)
    */

    std::vector<int> expectedReq = {1, 1, 3, 1, 5};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    std::vector<TREE_Node_t*> stack;
    stack.push_back(root);

    while(!stack.empty()) {
        TREE_Node_t* node = stack.back();
        stack.pop_back();

        assert(node->reqCnt == expectedReq[node->id]);

        if(node->left != NULL)
            stack.push_back(node->left);
        if(node->right != NULL)
            stack.push_back(node->right);
    }
}

TEST(CreateTreeFromFile, TreeNo3) {
    FILE* f1 = tmp("tree1.txt",
    "1\
    100\
    0 0 -1");

    /*
    # 100(3)
    */

    std::vector<int> expectedReq = {3};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    std::vector<TREE_Node_t*> stack;
    stack.push_back(root);

    while(!stack.empty()) {
        TREE_Node_t* node = stack.back();
        stack.pop_back();

        assert(node->reqCnt == expectedReq[node->id]);

        if(node->left != NULL)
            stack.push_back(node->left);
        if(node->right != NULL)
            stack.push_back(node->right);
    }
}

TEST(CreateTreeFromFile, TreeNo4) {
    FILE* f1 = tmp("tree1.txt",
    "7\
    5 10 15 20 25 30 35\
    0 1 2\
    1 0 2\
    2 1 6\
    3 1 4\
    5 0 4\
    4 0 6\
    6 0 -1");

    /*
    #          35(13)
    #       /         \
    #     15(5)        25(6)
    #    /    \        /    \
    #   5(1)   10(2)  20(2) 30(2)
    #
    */

    std::vector<int> expectedReq = {1, 2, 5, 2, 6, 2, 13};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    std::vector<TREE_Node_t*> stack;
    stack.push_back(root);

    while(!stack.empty()) {
        TREE_Node_t* node = stack.back();
        stack.pop_back();

        assert(node->reqCnt == expectedReq[node->id]);

        if(node->left != NULL)
            stack.push_back(node->left);
        if(node->right != NULL)
            stack.push_back(node->right);
    }
}

TEST(CreateTreeFromFile, TreeNo5) {
    FILE* f1 = tmp("tree1.txt",
    "0");

    /*
    # Empty
    */

    std::vector<int> expectedReq = {0};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    assert(root == NULL);
}

TEST(CreateTreeFromFile, TreeNo6) {
    FILE* f1 = tmp("tree1.txt",
    "4\
    10 20 30 40\
    0 0 1\
    1 0 2\
    2 0 3\
    3 0 -1");

    /*
    # 40(8)
    #  \
    #   30(6)
    #    \
    #     20(4)
    #      \
    #       10(2)
    */

    std::vector<int> expectedReq = {2, 4, 6, 8};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    std::vector<TREE_Node_t*> stack;
    stack.push_back(root);

    while(!stack.empty()) {
        TREE_Node_t* node = stack.back();
        stack.pop_back();

        assert(node->reqCnt == expectedReq[node->id]);

        if(node->left != NULL)
            stack.push_back(node->left);
        if(node->right != NULL)
            stack.push_back(node->right);
    }
}

TEST(CreateTreeFromFile, TreeNo7) {
    FILE* f1 = tmp("tree1.txt",
    "6\
    3 -6 9 12 15 18\
    0 1 2\
    1 0 2\
    2 1 4\
    3 0 4\
    4 1 5\
    5 0 -1");

    /*
    #         18(10)
    #       /
    #     15(8)
    #     /   \
    #   9(4)   12(2)
    #  /   \
    # 3(1)  -6(2)
    */

    std::vector<int> expectedReq = {1, 2, 4, 2, 8, 10};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    std::vector<TREE_Node_t*> stack;
    stack.push_back(root);

    while(!stack.empty()) {
        TREE_Node_t* node = stack.back();
        stack.pop_back();

        assert(node->reqCnt == expectedReq[node->id]);

        if(node->left != NULL)
            stack.push_back(node->left);
        if(node->right != NULL)
            stack.push_back(node->right);
    }
}

TEST(CreateTreeFromFile, InvalidBecauseOfCycleNo8) {
    FILE* f1 = tmp("tree1.txt",
    "3\
    10 20 30\
    0 1 1\
    1 0 2\
    2 1 0");

    /*
    # Empty
    */

    std::vector<int> expectedReq = {};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    assert(root == NULL);
}

TEST(CreateTreeFromFile, InvalidBecauseOfDoubleAssignNo9) {
    FILE* f1 = tmp("tree1.txt",
    "4\
    10 20 30 40\
    0 1 1\
    1 0 2\
    1 1 3\
    3 0 -1");

    /*
    # Empty
    */

    std::vector<int> expectedReq = {};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    assert(root == NULL);
}

TEST(CreateTreeFromFile, InvalidBecauseOfAssignToTheSameEdgeNo9) {
    FILE* f1 = tmp("tree1.txt",
    "4\
    10 20 30 40\
    0 1 1\
    1 1 2\
    2 1 1\
    3 0 -1");

    /*
    # Empty
    */

    std::vector<int> expectedReq = {};
    TREE_Node_t* root = TREE_CreateTreeFromFile(f1);

    assert(root == NULL);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
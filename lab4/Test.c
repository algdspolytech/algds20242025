#include "min_height_of_subtrees.h"


int ASSERT_EQ(int expected, int actual, const char* message, char* test_name) {
    if (expected != actual) {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %d, Actual: %d\n", expected, actual);
        return 0;
    }
    return 1;
}

int ASSERT_NE(int expected, int actual, const char* message, char* test_name) {
    if (expected == actual) {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %d, Actual: %d\n", expected, actual);
        return 0;
    }
    return 1;
}

int ASSERT_EQ_NULL(TreeNode* expected, TreeNode* actual, const char* message, char* test_name) {
    if (expected != actual) {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %d, Actual: %d\n", expected, actual);
        return 0;
    }
    return 1;
}

int ASSERT_STR_EQ(char* expected, char* actual, const char* message, char* test_name) {
    if (strcmp(expected, actual) != 0) {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %s, Actual: %s\n", expected, actual);
        return 0;
    }
    return 1;
}

void print_result_testing(int status, char* test_name) {
    if (status) {
        printf("%s - Success\n", test_name);
    }
    else {
        printf("%s - Failed\n", test_name);
    }
}


int Test_CreateNode_no1() {
    TreeNode* node = createNode(1);
    int status = 1;
    status *= ASSERT_EQ(node->value, 1, "Node value should be 1", "Test_CreateNode_no1");
    status *= ASSERT_EQ(node->min_leaf_height, -1, "min_leaf_height should be -1", "Test_CreateNode_no1");
    status *= ASSERT_EQ_NULL(node->left, NULL, "Left child should be NULL", "Test_CreateNode_no1");
    status *= ASSERT_EQ_NULL(node->right, NULL, "Right child should be NULL", "Test_CreateNode_no1");
    free(node);
    print_result_testing(status, "Test_CreateNode_no1");
    return status;
}


int Test_CalculateMinLeafHeight_EmptyTree_no2() {
    TreeNode* root = NULL;
    int status = 1;
    status *= ASSERT_EQ(calculateMinLeafHeight(root), -1, "Min leaf height for empty tree should be -1", "Test_CalculateMinLeafHeight_EmptyTree_no2");
    print_result_testing(status, "Test_CalculateMinLeafHeight_EmptyTree_no2");
    return status;
}


int Test_CalculateMinLeafHeight_SingleNodeTree_no3() {
    TreeNode* root = createNode(1);
    int status = 1;
    status *= ASSERT_EQ(calculateMinLeafHeight(root), 0, "Min leaf height for single node tree should be 0", "Test_CalculateMinLeafHeight_SingleNodeTree_no3");
    status *= ASSERT_EQ(root->min_leaf_height, 0, "min_leaf_height should be 0", "Test_CalculateMinLeafHeight_SingleNodeTree_no3");
    free(root);
    print_result_testing(status, "Test_CalculateMinLeafHeight_SingleNodeTree_no3");
    return status;
}


int Test_CalculateMinLeafHeight_MultipleNodesTree_no4() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    int status = 1;
    status *= ASSERT_EQ(calculateMinLeafHeight(root), 1, "Min leaf height for multiple nodes tree should be 1", "Test_CalculateMinLeafHeight_MultipleNodesTree_no4");
    status *= ASSERT_EQ(root->min_leaf_height, 1, "min_leaf_height should be 1", "Test_CalculateMinLeafHeight_MultipleNodesTree_no4");
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);
    print_result_testing(status, "Test_CalculateMinLeafHeight_MultipleNodesTree_no4");
    return status;
}


int Test_CreateHeightTree_EmptyTree_no5() {
    TreeNode* root = NULL;
    TreeNode* heightTree = createHeightTree(root);
    int status = 1;
    status *= ASSERT_EQ_NULL(heightTree, NULL, "Height tree for empty tree should be NULL", "Test_CreateHeightTree_EmptyTree_no5");
    print_result_testing(status, "Test_CreateHeightTree_EmptyTree_no5");
    return status;
}


int Test_CreateHeightTree_SingleNodeTree_no6() {
    TreeNode* root = createNode(1);
    calculateMinLeafHeight(root);
    TreeNode* heightTree = createHeightTree(root);
    int status = 1;
    status *= ASSERT_EQ(heightTree->value, 0, "Height tree root value should be 0", "Test_CreateHeightTree_SingleNodeTree_no6");
    status *= ASSERT_EQ_NULL(heightTree->left, NULL, "Height tree left child should be NULL", "Test_CreateHeightTree_SingleNodeTree_no6");
    status *= ASSERT_EQ_NULL(heightTree->right, NULL, "Height tree right child should be NULL", "Test_CreateHeightTree_SingleNodeTree_no6");
    free(root);
    free(heightTree);
    print_result_testing(status, "Test_CreateHeightTree_SingleNodeTree_no6");
    return status;
}


int Test_CreateHeightTree_MultipleNodesTree_no7() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    calculateMinLeafHeight(root);
    TreeNode* heightTree = createHeightTree(root);
    int status = 1;
    status *= ASSERT_EQ(heightTree->value, 1, "Height tree root value should be 1", "Test_CreateHeightTree_MultipleNodesTree_no7");
    status *= ASSERT_EQ(heightTree->left->value, 1, "Height tree left child value should be 1", "Test_CreateHeightTree_MultipleNodesTree_no7");
    status *= ASSERT_EQ(heightTree->right->value, 0, "Height tree right child value should be 0", "Test_CreateHeightTree_MultipleNodesTree_no7");
    free(root->left->left);
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);
    free(heightTree->left->left);
    free(heightTree->left->right);
    free(heightTree->left);
    free(heightTree->right);
    free(heightTree);
    print_result_testing(status, "Test_CreateHeightTree_MultipleNodesTree_no7");
    return status;
}


int Test_CalculateMinLeafHeight_UnbalancedTree_no8() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->left->left = createNode(3);
    root->left->left->left = createNode(4);
    int status = 1;
    status *= ASSERT_EQ(calculateMinLeafHeight(root), 0, "Min leaf height for unbalanced tree should be 0", "Test_CalculateMinLeafHeight_UnbalancedTree_no8");
    status *= ASSERT_EQ(root->min_leaf_height, 0, "min_leaf_height should be 0", "Test_CalculateMinLeafHeight_UnbalancedTree_no8");
    free(root->left->left->left);
    free(root->left->left);
    free(root->left);
    free(root);
    print_result_testing(status, "Test_CalculateMinLeafHeight_UnbalancedTree_no8");
    return status;
}


int Test_CreateHeightTree_UnbalancedTree_no9() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->left->left = createNode(3);
    root->left->left->left = createNode(4);
    calculateMinLeafHeight(root);
    TreeNode* heightTree = createHeightTree(root);
    int status = 1;
    status *= ASSERT_EQ(heightTree->value, 0, "Height tree root value should be 0", "Test_CreateHeightTree_UnbalancedTree_no9");
    status *= ASSERT_EQ(heightTree->left->value, 0, "Height tree left child value should be 0", "Test_CreateHeightTree_UnbalancedTree_no9");
    status *= ASSERT_EQ(heightTree->left->left->value, 0, "Height tree left-left child value should be 0", "Test_CreateHeightTree_UnbalancedTree_no9");
    status *= ASSERT_EQ(heightTree->left->left->left->value, 0, "Height tree left-left-left child value should be 0", "Test_CreateHeightTree_UnbalancedTree_no9");
    free(root->left->left->left);
    free(root->left->left);
    free(root->left);
    free(root);
    free(heightTree->left->left->left);
    free(heightTree->left->left);
    free(heightTree->left);
    free(heightTree);
    print_result_testing(status, "Test_CreateHeightTree_UnbalancedTree_no9");
    return status;
}


int Test_CalculateMinLeafHeight_SingleLeafTree_no10() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->left->right = createNode(3);
    int status = 1;
    status *= ASSERT_EQ(calculateMinLeafHeight(root), 0, "Min leaf height for single leaf tree should be 0", "Test_CalculateMinLeafHeight_SingleLeafTree_no10");
    status *= ASSERT_EQ(root->min_leaf_height, 0, "min_leaf_height should be 0", "Test_CalculateMinLeafHeight_SingleLeafTree_no10");
    free(root->left->right);
    free(root->left);
    free(root);
    print_result_testing(status, "Test_CalculateMinLeafHeight_SingleLeafTree_no10");
    return status;
}


int Test_CreateHeightTree_SingleLeafTree_no11() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->left->right = createNode(3);
    calculateMinLeafHeight(root);
    TreeNode* heightTree = createHeightTree(root);
    int status = 1;
    status *= ASSERT_EQ(heightTree->value, 0, "Height tree root value should be 0", "Test_CreateHeightTree_SingleLeafTree_no11");
    status *= ASSERT_EQ(heightTree->left->value, 0, "Height tree left child value should be 0", "Test_CreateHeightTree_SingleLeafTree_no11");
    status *= ASSERT_EQ(heightTree->left->right->value, 0, "Height tree left-right child value should be 0", "Test_CreateHeightTree_SingleLeafTree_no11");
    free(root->left->right);
    free(root->left);
    free(root);
    free(heightTree->left->right);
    free(heightTree->left);
    free(heightTree);
    print_result_testing(status, "Test_CreateHeightTree_SingleLeafTree_no11");
    return status;
}

int main() {
    int result_testing = 1;
    result_testing *= Test_CreateNode_no1();
    result_testing *= Test_CalculateMinLeafHeight_EmptyTree_no2();
    result_testing *= Test_CalculateMinLeafHeight_SingleNodeTree_no3();
    result_testing *= Test_CalculateMinLeafHeight_MultipleNodesTree_no4();
    result_testing *= Test_CreateHeightTree_EmptyTree_no5();
    result_testing *= Test_CreateHeightTree_SingleNodeTree_no6();
    result_testing *= Test_CreateHeightTree_MultipleNodesTree_no7();
    result_testing *= Test_CalculateMinLeafHeight_UnbalancedTree_no8();
    result_testing *= Test_CreateHeightTree_UnbalancedTree_no9();
    result_testing *= Test_CalculateMinLeafHeight_SingleLeafTree_no10();
    result_testing *= Test_CreateHeightTree_SingleLeafTree_no11();

    if (result_testing == 1) {
        printf("All tests passed!\n");
    }
    else {
        printf("Some tests failed\n");
    }
    return 0;
}
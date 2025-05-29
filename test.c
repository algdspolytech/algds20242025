#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


int ASSERT_EQ(long long expected, long long actual, const char* message, char* test_name) {
    if (expected != actual) {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %lld, Actual: %lld\n", expected, actual);
        return 0;
    }
    return 1;
}

int ASSERT_NE(long long expected, long long actual, const char* message, char* test_name) {
    if (expected == actual) {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %lld, Actual: %lld\n", expected, actual);
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

// ���� 1: �������� ����
int Test_CreateNode_no1() {
    Node* node = createNode(5, 10);
    int status = 1;
    status *= ASSERT_EQ(node->x, 5, "node->x should be 5", "Test_CreateNode_no1");
    status *= ASSERT_EQ(node->c, 10, "node->c should be 10", "Test_CreateNode_no1");
    status *= ASSERT_EQ(node->sum, 10, "node->sum should be 10", "Test_CreateNode_no1");
    status *= ASSERT_EQ((long long)node->left, (long long)NULL, "node->left should be NULL", "Test_CreateNode_no1");
    status *= ASSERT_EQ((long long)node->right, (long long)NULL, "node->right should be NULL", "Test_CreateNode_no1");
    free(node);
    print_result_testing(status, "Test_CreateNode_no1");
    return status;
}

// ���� 2: ������� � ������ ������
int Test_InsertToEmptyTree_no2() {
    Node* root = NULL;
    insert(&root, 5, 10);
    int status = 1;
    status *= ASSERT_EQ(root->x, 5, "root->x should be 5", "Test_InsertToEmptyTree_no2");
    status *= ASSERT_EQ(root->c, 10, "root->c should be 10", "Test_InsertToEmptyTree_no2");
    status *= ASSERT_EQ(root->sum, 10, "root->sum should be 10", "Test_InsertToEmptyTree_no2");
    freeTree(root);
    print_result_testing(status, "Test_InsertToEmptyTree_no2");
    return status;
}

// ���� 3: ���������� ����� ����� �������
int Test_UpdateSum_no3() {
    Node* root = NULL;
    insert(&root, 1, 5);
    insert(&root, 2, 3);
    int status = 1;
    status *= ASSERT_EQ(root->sum, 8, "root->sum should be 8", "Test_UpdateSum_no3");
    freeTree(root);
    print_result_testing(status, "Test_UpdateSum_no3");
    return status;
}

// ���� 4: ����� � ��������� ��� ������� ������
int Test_RangeSumEmptyTree_no4() {
    Node* root = NULL;
    long long sum = rangeSum(root, 1, 5);
    int status = 1;
    status *= ASSERT_EQ(sum, 0, "rangeSum should return 0 for empty tree", "Test_RangeSumEmptyTree_no4");
    freeTree(root);
    print_result_testing(status, "Test_RangeSumEmptyTree_no4");
    return status;
}

// ���� 5: ����� � ��������� ��� ������ ��������
int Test_RangeSumSingleElement_no5() {
    Node* root = NULL;
    insert(&root, 3, 7);
    long long sum = rangeSum(root, 2, 4);
    int status = 1;
    status *= ASSERT_EQ(sum, 7, "rangeSum should return 7 for single element in range", "Test_RangeSumSingleElement_no5");
    freeTree(root);
    print_result_testing(status, "Test_RangeSumSingleElement_no5");
    return status;
}

// ���� 6: ����� � ��������� ��� ���������� ���������
int Test_RangeSumMultipleElements_no6() {
    Node* root = NULL;
    insert(&root, 1, 5);
    insert(&root, 3, 2);
    insert(&root, 5, 8);
    long long sum = rangeSum(root, 1, 4);
    int status = 1;
    status *= ASSERT_EQ(sum, 7, "rangeSum should return 7 for range [1, 4)", "Test_RangeSumMultipleElements_no6");
    freeTree(root);
    print_result_testing(status, "Test_RangeSumMultipleElements_no6");
    return status;
}

// ���� 7: ����� ��� ���������
int Test_RangeSumOutOfRange_no7() {
    Node* root = NULL;
    insert(&root, 5, 10);
    long long sum = rangeSum(root, 1, 3);
    int status = 1;
    status *= ASSERT_EQ(sum, 0, "rangeSum should return 0 for range outside elements", "Test_RangeSumOutOfRange_no7");
    freeTree(root);
    print_result_testing(status, "Test_RangeSumOutOfRange_no7");
    return status;
}

// ���� 8: ������� ���� ��������
int Test_Merge_no8() {
    Node* left = createNode(1, 5);
    Node* right = createNode(3, 7);
    Node* merged = merge(left, right);
    int status = 1;
    status *= ASSERT_EQ(merged->sum, 12, "merged->sum should be 12", "Test_Merge_no8");
    freeTree(merged);
    print_result_testing(status, "Test_Merge_no8");
    return status;
}

// ���� 9: ���������� ������
int Test_Split_no9() {
    Node* root = NULL;
    insert(&root, 1, 5);
    insert(&root, 3, 7);
    Node* left, * right;
    split(root, 2, &left, &right);
    int status = 1;
    status *= ASSERT_EQ(left->sum, 5, "left->sum should be 5", "Test_Split_no9");
    status *= ASSERT_EQ(right->sum, 7, "right->sum should be 7", "Test_Split_no9");
    freeTree(left);
    freeTree(right);
    print_result_testing(status, "Test_Split_no9");
    return status;
}

// ���� 10: ������������ ������
int Test_FreeTree_no10() {
    Node* root = NULL;
    insert(&root, 1, 5);
    insert(&root, 3, 7);
    freeTree(root);
    int status = 1;
    print_result_testing(status, "Test_FreeTree_no10");
    return status;
}

int main() {
    int result_testing = 1;
    result_testing *= Test_CreateNode_no1();
    result_testing *= Test_InsertToEmptyTree_no2();
    result_testing *= Test_UpdateSum_no3();
    result_testing *= Test_RangeSumEmptyTree_no4();
    result_testing *= Test_RangeSumSingleElement_no5();
    result_testing *= Test_RangeSumMultipleElements_no6();
    result_testing *= Test_RangeSumOutOfRange_no7();
    result_testing *= Test_Merge_no8();
    result_testing *= Test_Split_no9();
    result_testing *= Test_FreeTree_no10();

    if (result_testing == 1) {
        printf("All tests passed!\n");
    }
    else {
        printf("Some tests failed\n");
    }
    return 0;
}
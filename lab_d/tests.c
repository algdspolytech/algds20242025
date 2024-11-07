#include <stdio.h>
#include "functions.h"

void printTestResult(const char* testName, const char* method, int expected[], int expected_size, int result[], int result_size) {
    printf("Test (%s) (%s):\n", testName, method);
    printf("Expected: ");
    if (expected_size == 0) {
        printf("0\n");
    }
    else {
        for (int i = 0; i < expected_size; i++) {
            printf("%d ", expected[i]);
        }
        printf("\n");
    }

    printf("Got: ");
    if (result_size == 0) {
        printf("0\n");
    }
    else {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    if (compareArrays(expected, expected_size, result, result_size)) {
        printf("Test Passed\n\n");
    }
    else {
        printf("Test Failed\n\n");
    }
}

void testSubsetSumDP(int arr[], int n, int S, int expected[], int expected_size, const char* testName) {
    bool dp[MAX_NUMBERS + 1][MAX_NUMBERS + 1];
    int subset[MAX_NUMBERS];
    int subset_size = 0;

    if (isSubsetSum(arr, n, S, dp)) {
        getSubset(arr, n, S, dp, subset, &subset_size);
        printTestResult(testName, "DP", expected, expected_size, subset, subset_size);
    }
    else {
        printTestResult(testName, "DP", expected, expected_size, subset, 0);
    }
}

void testDFS(int arr[], int n, int S, int expected[], int expected_size, const char* testName) {
    int subset[MAX_NUMBERS];
    int subset_size = 0;

    if (dfs(arr, n, S, 0, 0, subset, &subset_size)) {
        printTestResult(testName, "DFS", expected, expected_size, subset, subset_size);
    }
    else {
        printTestResult(testName, "DFS", expected, expected_size, subset, 0);
    }
}

void test_several_outputs_dp_1() {
    int arr[] = { 1, 2, 3, 4 };
    int n = 4;
    int S = 5;
    int expected[] = { 3, 2 };
    int expected_size = 2;
    testSubsetSumDP(arr, n, S, expected, expected_size, "Test 1: several answers dp");
}

void test_several_outputs_dfs_2() {
    int arr[] = { 1, 2, 3, 4 };
    int n = 4;
    int S = 5;
    int expected[] = { 1, 4 };
    int expected_size = 2;
    testDFS(arr, n, S, expected, expected_size, "Test 2: several answers dfs");
}

void test_only_element_dp_3() {
    int arr[] = { 1 };
    int n = 1;
    int S = 2;
    int expected[] = { 0 };
    int expected_size = 0;
    testSubsetSumDP(arr, n, S, expected, expected_size, "Test 3: only element in input, no answer, dp");
}

void test_only_element_dfs_4() {
    int arr[] = { 1 };
    int n = 1;
    int S = 2;
    int expected[] = { 0 };
    int expected_size = 0;
    testDFS(arr, n, S, expected, expected_size, "Test 4: only element in input, no answer, dfs");
}

void test_only_element_is_answer_dp_5() {
    int arr[] = { 1 };
    int n = 1;
    int S = 1;
    int expected[] = { 1 };
    int expected_size = 1;
    testSubsetSumDP(arr, n, S, expected, expected_size, "Test 5: only element is answer, dp");
}

void test_only_element_is_answer_dfs_6() {
    int arr[] = { 1 };
    int n = 1;
    int S = 1;
    int expected[] = { 1 };
    int expected_size = 1;
    testDFS(arr, n, S, expected, expected_size, "Test 6: only element is answer, dfs");
}

void test_several_elements_no_answer_dp_7() {
    int arr[] = { 1, 1 };
    int n = 2;
    int S = 0;
    int expected[] = { 0 };
    int expected_size = 0;
    testSubsetSumDP(arr, n, S, expected, expected_size, "Test 7: several elements,  no answer, dp");
}

void test_several_elements_no_answer_dfs_8() {
    int arr[] = { 1, 1 };
    int n = 2;
    int S = 0;
    int expected[] = { 0 };
    int expected_size = 0;
    testDFS(arr, n, S, expected, expected_size, "Test 8: several elements,  no answer, dfs");
}

void test_all_elements_are_answer_dp_9() {
    int arr[] = { 1, 2, 3 };
    int n = 3;
    int S = 6;
    int expected[] = { 3, 2, 1 };
    int expected_size = 3;
    testSubsetSumDP(arr, n, S, expected, expected_size, "Test 9: all elements are answer, dp");
}

void test_all_elements_are_answer_dfs_10() {
    int arr[] = { 1, 2, 3 };
    int n = 3;
    int S = 6;
    int expected[] = { 1, 2, 3 };
    int expected_size = 3;
    testDFS(arr, n, S, expected, expected_size, "Test 10: all elements are answer, dfs");
}

int main() {
    test_several_outputs_dp_1();
    test_several_outputs_dfs_2();
    test_only_element_dp_3();
    test_only_element_dfs_4();
    test_only_element_is_answer_dp_5();

    test_only_element_is_answer_dfs_6();
    test_several_elements_no_answer_dp_7();
    test_several_elements_no_answer_dfs_8();

    test_all_elements_are_answer_dp_9();
    test_all_elements_are_answer_dfs_10();
    return 0;
}

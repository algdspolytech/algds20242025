#pragma warning(disable:4996)
#include "../LabD/Source.h"
#include <string.h>



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

int ASSERT_CHAR_EQ(char expected, char actual, const char* message, char* test_name) {
    if (expected != actual) {
        printf("Failed %s\n", test_name);
        printf("Assertion failed: %s\n", message);
        printf("Expected: %c, Actual: %c\n", expected, actual);
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

int Test_InitQueue_no1() {
    Queue queue;
    initQueue(&queue, 10);
    int status = 1;
    status *= ASSERT_EQ(queue.front, -1, "queue.front should be -1", "Test_InitQueue_no1");
    status *= ASSERT_EQ(queue.rear, -1, "queue.rear should be -1", "Test_InitQueue_no1");
    status *= ASSERT_EQ(queue.capacity, 10, "queue.capacity should be 10", "Test_InitQueue_no1");
    freeQueue(&queue);
    print_result_testing(status, "Test_InitQueue_no1");
    return status;
}

int Test_IsEmptyForEmptyQueue_no2() {
    Queue queue;
    initQueue(&queue, 10);
    int status = 1;
    status *= ASSERT_EQ(isEmpty(&queue), 1, "isEmpty should return 1 for empty queue", "Test_IsEmptyForEmptyQueue_no2");
    freeQueue(&queue);
    print_result_testing(status, "Test_IsEmptyForEmptyQueue_no2");
    return status;
}

int Test_IsEmptyForNonEmptyQueue_no3() {
    Queue queue;
    initQueue(&queue, 10);
    enqueue(&queue, 1);
    int status = 1;
    status *= ASSERT_EQ(isEmpty(&queue), 0, "isEmpty should return 0 for non-empty queue", "Test_IsEmptyForNonEmptyQueue_no3");
    freeQueue(&queue);
    print_result_testing(status, "Test_IsEmptyForNonEmptyQueue_no3");
    return status;
}

int Test_EnqueueToEmptyQueue_no4() {
    Queue queue;
    initQueue(&queue, 10);
    enqueue(&queue, 1);
    int status = 1;
    status *= ASSERT_EQ(queue.data[queue.rear], 1, "queue.data[queue.rear] should be 1", "Test_EnqueueToEmptyQueue_no4");
    freeQueue(&queue);
    print_result_testing(status, "Test_EnqueueToEmptyQueue_no4");
    return status;
}

int Test_DequeueFromNonEmptyQueue_no5() {
    Queue queue;
    initQueue(&queue, 10);
    enqueue(&queue, 1);
    int dequeued = dequeue(&queue);
    int status = 1;
    status *= ASSERT_EQ(dequeued, 1, "dequeued value should be 1", "Test_DequeueFromNonEmptyQueue_no5");
    status *= ASSERT_EQ(queue.front, -1, "queue.front should be -1 after dequeue", "Test_DequeueFromNonEmptyQueue_no5");
    freeQueue(&queue);
    print_result_testing(status, "Test_DequeueFromNonEmptyQueue_no5");
    return status;
}

int Test_GreedyColoring_no6() {
    int n = 3, k = 2;
    int** adj_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        adj_matrix[i] = (int*)calloc(n, sizeof(int));
    }
    adj_matrix[0][1] = 1;
    adj_matrix[1][0] = 1;
    adj_matrix[1][2] = 1;
    adj_matrix[2][1] = 1;

    int* colors = (int*)malloc(n * sizeof(int));
    int result = greedy_coloring(adj_matrix, n, k, colors);
    int status = 1;
    status *= ASSERT_EQ(result, 0, "greedy_coloring should return 0 for successful coloring", "Test_GreedyColoring_no6");
    status *= ASSERT_EQ(colors[0], 0, "Vertex 0 should be colored with color 0", "Test_GreedyColoring_no6");
    status *= ASSERT_EQ(colors[1], 1, "Vertex 1 should be colored with color 1", "Test_GreedyColoring_no6");
    status *= ASSERT_EQ(colors[2], 0, "Vertex 2 should be colored with color 0", "Test_GreedyColoring_no6");
    free_matrix(adj_matrix, n);
    free(colors);
    print_result_testing(status, "Test_GreedyColoring_no6");
    return status;
}

int Test_CheckColoring_no7() {
    int colors[] = { 0, 1, 0 };
    int status = 1;
    status *= ASSERT_EQ(check_coloring(3, colors), 1, "check_coloring should return 1 for valid coloring", "Test_CheckColoring_no7");
    print_result_testing(status, "Test_CheckColoring_no7");
    return status;
}

int Test_FreeMatrix_no8() {
    int n = 3;
    int** adj_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        adj_matrix[i] = (int*)calloc(n, sizeof(int));
    }
    free_matrix(adj_matrix, n);
    int status = 1;
    print_result_testing(status, "Test_FreeMatrix_no8");
    return status;
}

int Test_IsFullForFullQueue_no9() {
    Queue queue;
    initQueue(&queue, 2);
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    int status = 1;
    status *= ASSERT_EQ(queue.rear, 1, "queue.rear should be 1 for full queue", "Test_IsFullForFullQueue_no9");
    freeQueue(&queue);
    print_result_testing(status, "Test_IsFullForFullQueue_no9");
    return status;
}

int Test_IsFullForNonFullQueue_no10() {
    Queue queue;
    initQueue(&queue, 2);
    enqueue(&queue, 1);
    int status = 1;
    status *= ASSERT_EQ(queue.rear, 0, "queue.rear should be 0 for non-full queue", "Test_IsFullForNonFullQueue_no10");
    freeQueue(&queue);
    print_result_testing(status, "Test_IsFullForNonFullQueue_no10");
    return status;
}

int main() {
    int result_testing = 1;
    result_testing *= Test_InitQueue_no1();
    result_testing *= Test_IsEmptyForEmptyQueue_no2();
    result_testing *= Test_IsEmptyForNonEmptyQueue_no3();
    result_testing *= Test_EnqueueToEmptyQueue_no4();
    result_testing *= Test_DequeueFromNonEmptyQueue_no5();
    result_testing *= Test_GreedyColoring_no6();
    result_testing *= Test_CheckColoring_no7();
    result_testing *= Test_FreeMatrix_no8();
    result_testing *= Test_IsFullForFullQueue_no9();
    result_testing *= Test_IsFullForNonFullQueue_no10();

    if (result_testing == 1) {
        printf("All tests passed!\n");
    }
    else {
        printf("Some tests failed\n");
    }
    return 0;
}
#include <stdio.h>

void run_test(int test_number, const char* text_list, const char* text_matrix){
    FILE *file_list;
    FILE *file_matrix;

    file_list = fopen("test_list.txt", "w");
    fprintf(file_list, text_list);
    fclose(file_list);

    file_matrix = fopen("test_matrix.txt", "w");
    fprintf(file_matrix, text_matrix);
    fclose(file_matrix);

    printf("Test %d (Simple identical graphs): %s\n",test_number, compare_graphs("test_list.txt", "test_matrix.txt") ? "Passed" : "Failed");

    remove("test_list.txt");
    remove("test_matrix.txt");
}

int main() {
    run_test(1, "2\n1 1\n1 0\n", "2\n0 1\n1 0\n");
    run_test(2, "3\n1 1\n0\n0\n", "2\n0 1\n1 0\n");
    run_test(3, "3\n2 1 2\n1 0\n1 0\n", "3\n0 1 1\n1 0 0\n1 0 0\n");
    run_test(4, "3\n2 1 2\n1 0\n0\n", "3\n0 1 1\n1 0 1\n0 1 0\n");
    run_test(5, "0\n", "0\n");
    run_test(6, "1\n0\n", "1\n0\n");
    run_test(7, "3\n1 1\n1 2\n1 0\n", "3\n0 1 0\n0 0 1\n1 0 0\n");
    run_test(8, "3\n0\n0\n0\n", "3\n0 0 0\n0 0 0\n0 0 0\n");
    run_test(9, "5\n2 1 2\n2 0 3\n2 0 4\n1 1\n1 2\n", "5\n0 1 1 0 0\n1 0 0 1 0\n1 0 0 0 1\n0 1 0 0 0\n0 0 1 0 0\n");
    run_test(10, "4\n1 1\n1 0\n0\n0\n", "3\n0 1 0\n1 0 0\n0 0 0\n");

    return 0;
}

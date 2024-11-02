#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define MAX_PATH_LEN 256

void strip_whitespace(char* str) {
    char* end;
    while ((end = strchr(str, '\r')) || (end = strchr(str, '\n')) || (end = strchr(str, ' '))) {
        *end = '\0';
    }
}

void run_test(const char* test_name, const char* input_data, const char* expected_output) {
    FILE* input = fopen("input_temp.txt", "w");
    FILE* expected = fopen("expected_output_temp.txt", "w");

    fputs(input_data, input);
    fclose(input);

    fputs(expected_output, expected);
    fclose(expected);

    build_directory_tree("input_temp.txt", "output_temp.txt");

    FILE* output = fopen("output_temp.txt", "r");
    FILE* expected_output_file = fopen("expected_output_temp.txt", "r");

    int is_correct = 1;
    char output_line[256];
    char expected_line[256];

    while (fgets(output_line, sizeof(output_line), output) && fgets(expected_line, sizeof(expected_line), expected_output_file)) {
        strip_whitespace(output_line);
        strip_whitespace(expected_line);

        if (strcmp(output_line, expected_line) != 0) {
            is_correct = 0;
            printf("Mismatch in test '%s':\n", test_name);
            printf("Output line:    '%s'\n", output_line);
            printf("Expected line:  '%s'\n", expected_line);
            break;
        }
    }

    if (is_correct) {
        if (fgets(output_line, sizeof(output_line), output) != NULL || fgets(expected_line, sizeof(expected_line), expected_output_file) != NULL) {
            is_correct = 0;
            printf("Test '%s' failed: File lengths differ\n", test_name);
        }
    }

    if (is_correct) {
        printf("Test '%s' passed\n", test_name);
    }

    fclose(output);
    fclose(expected_output_file);

    remove("input_temp.txt");
    remove("output_temp.txt");
    remove("expected_output_temp.txt");
}

int main() {
     run_test("Test 1 - Single level tree",
        "3\nroot\\folder1\nroot\\folder2\nroot\\folder3\n",
        "root\n folder1\n folder2\n folder3\n");

    run_test("Test 2 - Two level structure",
        "4\nroot\\folder1\nroot\\folder1\\subfolder1\nroot\\folder2\nroot\\folder2\\subfolder2\n",
        "root\n folder1\n  subfolder1\n folder2\n  subfolder2\n");

    run_test("Test 3 - Multiple levels of nesting",
        "1\nroot\\A\\B\\C\\D\n",
        "root\n A\n  B\n   C\n    D\n");

    run_test("Test 4 - Multiple subdirectories at same level",
        "3\nroot\\A\\B\nroot\\A\\C\nroot\\A\\D\n",
        "root\n A\n  B\n  C\n  D\n");

    run_test("Test 5 - Empty tree",
        "0\n",
        "root\n");

    run_test("Test 6 - Duplicate paths",
        "4\nroot\\A\nroot\\A\\B\nroot\\A\nroot\\A\\B\n",
        "root\n A\n  B\n");

    run_test("Test 7 - Unsorted paths",
        "3\nroot\\folderB\nroot\\folderA\nroot\\folderC\n",
        "root\n folderA\n folderB\n folderC\n");

    run_test("Test 8 - Long folder names",
        "1\nroot\\abcdefgh\n",
        "root\n abcdefgh\n");

    run_test("Test 9 - Empty lines in input",
        "3\nroot\\folder1\n\nroot\\folder2\n",
        "root\n folder1\n folder2\n");

    run_test("Test 10 - Nested folders with same names",
        "4\nroot\\folder1\nroot\\folder1\\subfolder\nroot\\folder2\nroot\\folder2\\subfolder\n",
        "root\n folder1\n  subfolder\n folder2\n  subfolder\n");
    return 0;
}

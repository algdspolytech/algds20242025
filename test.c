#include "sudoku_solver.h"
#include <string.h>
#include <stdio.h>

void run_test(const char *test_name, const char *input, const char *expected_output, bool expect_solution) {
    printf("=== %s ===\n", test_name);
    
    // Create input file
    FILE *input_file = fopen("test_input.txt", "w");
    fprintf(input_file, "%s", input);
    fclose(input_file);
    
    // Run solver
    Sudoku sudoku;
    read_input(&sudoku, "test_input.txt");
    bool solved = solve_sudoku(&sudoku);
    write_output(&sudoku, "test_output.txt");
    
    // Check if solution exists as expected
    if (expect_solution != solved) {
        printf("FAIL: Expected %s but got %s\n", 
               expect_solution ? "solution" : "no solution", 
               solved ? "solution" : "no solution");
        return;
    }
    
    // If solution was expected, verify it
    if (expect_solution) {
        FILE *output_file = fopen("test_output.txt", "r");
        char output[1000];
        size_t len = fread(output, 1, sizeof(output), output_file);
        output[len] = '\0';
        fclose(output_file);
        
        if (strcmp(output, expected_output) != 0) {
            printf("FAIL: Output doesn't match expected solution\n");
            printf("Expected:\n%s\nGot:\n%s\n", expected_output, output);
        } else {
            printf("PASS\n");
        }
    } else {
        printf("PASS\n");
    }
    printf("\n");
}
int main() {
    // Test 1: Standard 3x3 sudoku (from example)
    run_test(
        "Standard 3x3 sudoku",
        "3\n"
        "0 0 5 3 0 0 0 0 0\n"
        "8 0 0 0 0 0 0 2 0\n"
        "0 7 0 0 1 0 5 0 0\n"
        "4 0 0 0 0 5 3 0 0\n"
        "0 1 0 0 7 0 0 0 6\n"
        "0 3 2 0 0 0 0 8 0\n"
        "0 6 0 5 0 0 0 0 9\n"
        "0 0 4 0 0 0 0 3 0\n"
        "0 0 0 0 0 9 7 0 0\n",
        "1 4 5 3 2 7 6 9 8\n"
        "8 3 9 6 5 4 1 2 7\n"
        "6 7 2 9 1 8 5 4 3\n"
        "4 9 6 1 8 5 3 7 2\n"
        "2 1 8 4 7 3 9 5 6\n"
        "7 5 3 2 9 6 4 8 1\n"
        "3 6 7 5 4 2 8 1 9\n"
        "9 8 4 7 6 1 2 3 5\n"
        "5 2 1 8 3 9 7 6 4\n",
        true
    );
    
    // Test 2: Already solved sudoku
    run_test(
        "Already solved sudoku",
        "3\n"
        "1 4 5 3 2 7 6 9 8\n"
        "8 3 9 6 5 4 1 2 7\n"
        "6 7 2 9 1 8 5 4 3\n"
        "4 9 6 1 8 5 3 7 2\n"
        "2 1 8 4 7 3 9 5 6\n"
        "7 5 3 2 9 6 4 8 1\n"
        "3 6 7 5 4 2 8 1 9\n"
        "9 8 4 7 6 1 2 3 5\n"
        "5 2 1 8 3 9 7 6 4\n",
        "1 4 5 3 2 7 6 9 8\n"
        "8 3 9 6 5 4 1 2 7\n"
        "6 7 2 9 1 8 5 4 3\n"
        "4 9 6 1 8 5 3 7 2\n"
        "2 1 8 4 7 3 9 5 6\n"
        "7 5 3 2 9 6 4 8 1\n"
        "3 6 7 5 4 2 8 1 9\n"
        "9 8 4 7 6 1 2 3 5\n"
        "5 2 1 8 3 9 7 6 4\n",
        true
    );
    
    // Test 3: Unsolvable sudoku
    run_test(
        "Unsolvable sudoku",
        "3\n"
        "1 1 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n",
        "0\n",
        false
    );
    
    // Test 4: Empty 2x2 sudoku
    run_test(
        "Empty 2x2 sudoku",
        "2\n"
        "0 0 0 0\n"
        "0 0 0 0\n"
        "0 0 0 0\n"
        "0 0 0 0\n",
        "1 2 3 4\n"
        "3 4 1 2\n"
        "2 1 4 3\n"
        "4 3 2 1\n",
        true
    );
    
    // Test 5: Minimal 3x3 sudoku with one solution
    run_test(
        "Minimal 3x3 sudoku",
        "3\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 3 0 8 5\n"
        "0 0 1 0 2 0 0 0 0\n"
        "0 0 0 5 0 7 0 0 0\n"
        "0 0 4 0 0 0 1 0 0\n"
        "0 9 0 0 0 0 0 0 0\n"
        "5 0 0 0 0 0 0 7 3\n"
        "0 0 2 0 1 0 0 0 0\n"
        "0 0 0 0 4 0 0 0 9\n",
        "9 8 7 6 5 4 3 2 1\n"
        "2 4 6 1 7 3 9 8 5\n"
        "3 5 1 9 2 8 7 4 6\n"
        "1 2 8 5 3 7 6 9 4\n"
        "6 3 4 8 9 2 1 5 7\n"
        "7 9 5 4 6 1 8 3 2\n"
        "5 1 9 2 8 6 4 7 3\n"
        "4 7 2 3 1 9 5 6 8\n"
        "8 6 3 7 4 5 2 1 9\n",
        true
    );
    
    // Test 6: 4x4 sudoku
    run_test(
        "4x4 sudoku",
        "4\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n",
        "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16\n"
        "3 4 1 2 7 8 5 6 11 12 9 10 15 16 13 14\n"
        "2 1 4 3 6 5 8 7 10 9 12 11 14 13 16 15\n"
        "4 3 2 1 8 7 6 5 12 11 10 9 16 15 14 13\n"
        "5 6 7 8 9 10 11 12 13 14 15 16 1 2 3 4\n"
        "7 8 5 6 11 12 9 10 15 16 13 14 3 4 1 2\n"
        "6 5 8 7 10 9 12 11 14 13 16 15 2 1 4 3\n"
        "8 7 6 5 12 11 10 9 16 15 14 13 4 3 2 1\n"
        "9 10 11 12 13 14 15 16 1 2 3 4 5 6 7 8\n"
        "11 12 9 10 15 16 13 14 3 4 1 2 7 8 5 6\n"
        "10 9 12 11 14 13 16 15 2 1 4 3 6 5 8 7\n"
        "12 11 10 9 16 15 14 13 4 3 2 1 8 7 6 5\n"
        "13 14 15 16 1 2 3 4 5 6 7 8 9 10 11 12\n"
        "15 16 13 14 3 4 1 2 7 8 5 6 11 12 9 10\n"
        "14 13 16 15 2 1 4 3 6 5 8 7 10 9 12 11\n"
        "16 15 14 13 4 3 2 1 8 7 6 5 12 11 10 9\n",
        true
    );
    
    // Test 7: Sudoku with multiple solutions (should find one)
    run_test(
        "Sudoku with multiple solutions",
        "3\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n",
        "", // Any solution is acceptable
        true
    );
    
    // Test 8: Sudoku with invalid size (N=1)
    run_test(
        "Invalid size (N=1)",
        "1\n"
        "1\n",
        "0\n",
        false
    );
    
    // Test 9: Sudoku with maximum size (N=9)
    run_test(
        "Maximum size (N=9)",
        "9\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n",
        "", // Any solution is acceptable
        true
    );
    
    // Test 10: Sudoku with some constraints but not enough for unique solution
    run_test(
        "Underconstrained sudoku",
        "3\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 1 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n",
        "", // Any solution is acceptable
        true
    );
    
    return 0;
}
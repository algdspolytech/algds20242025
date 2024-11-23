#include "gtest/gtest.h"
extern "C" {
    #include "expressions.h"
}

TEST(ExpressionSolverTest, EvaluateSimpleExpression_no1) {
    ASSERT_EQ(evaluate_expression("1+2"), 3);
}

TEST(ExpressionSolverTest, EvaluateMultipleOperators_no2) {
    ASSERT_EQ(evaluate_expression("10+2*6"), 22);
}

TEST(ExpressionSolverTest, DivisionByZero_no3) {
    ASSERT_DEATH(evaluate_expression("10/0"), ".*");
}

TEST(ExpressionSolverTest, EvaluateWithSpaces_no4) {
    ASSERT_EQ(evaluate_expression(" 2 + 3 "), 5);
}

TEST(ExpressionSolverTest, GenerateCombinationSingleDigit_no5) {
    char result[MAX_LENGTH * 2] = "";
    ASSERT_TRUE(generate_combinations("2", 0, result, 0, 2, result));
    ASSERT_STREQ(result, "2");
}

TEST(ExpressionSolverTest, GenerateCombinationBasic_no6) {
    char result[MAX_LENGTH * 2] = "";
    ASSERT_TRUE(generate_combinations("23", 0, result, 0, 5, result));
    ASSERT_STREQ(result, "2+3");
}

TEST(ExpressionSolverTest, GenerateCombinationComplex_no7) {
    char result[MAX_LENGTH * 2] = "";
    ASSERT_TRUE(generate_combinations("123", 0, result, 0, 6, result));
    ASSERT_STREQ(result, "1+2+3");
}

TEST(ExpressionSolverTest, SolveTaskValid_no8) {
    solve_task("test_input_valid.txt", "test_output_valid.txt");
    FILE* file = fopen("test_output_valid.txt", "r");
    char output[MAX_LENGTH];
    fscanf(file, "%s", output);
    fclose(file);
    ASSERT_STREQ(output, "12+34-5*6");
}

TEST(ExpressionSolverTest, SolveTaskInvalid_no9) {
    solve_task("test_input_invalid.txt", "test_output_invalid.txt");
    FILE* file = fopen("test_output_invalid.txt", "r");
    char output[MAX_LENGTH];
    fscanf(file, "%s", output);
    fclose(file);
    ASSERT_STREQ(output, "0");
}
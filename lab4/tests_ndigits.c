#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "ndigits.h"

// Тесты для evaluate_expression

void TestEvaluateExpression_SimpleAddition_returnValidVal() {
    assert(evaluate_expression("3+2") == 5);
}

void TestEvaluateExpression_SimpleSubtraction_returnValidVal() {
    assert(evaluate_expression("10-7") == 3);
}

void TestEvaluateExpression_SimpleMultiplication_returnValidVal() {
    assert(evaluate_expression("4*3") == 12);
}

void TestEvaluateExpression_SimpleDivision_returnValidVal() {
    assert(evaluate_expression("8/2") == 4);
}

void TestEvaluateExpression_DivisionByZero_returnMaxVal() {
    assert(evaluate_expression("5/0") == LLONG_MAX);
}

void TestEvaluateExpression_MixedOperations_returnValidVal() {
    assert(evaluate_expression("2+3*4-6/2") == 11);
}

// Тесты для generate_expressions

void TestGenerateExpressions_SimpleCase_returnValidExpr() {
    char result[MAX_EXPR_LEN];
    assert(generate_expressions("12", 0, (char[MAX_EXPR_LEN]){0}, 0, 3, result) == 1);
}

void TestGenerateExpressions_NoValidExpression_returnZero() {
    char result[MAX_EXPR_LEN];
    assert(generate_expressions("5", 0, (char[MAX_EXPR_LEN]){0}, 0, 100, result) == 0);
}

void TestGenerateExpressions_LongNumber_returnValidExpr() {
    char result[MAX_EXPR_LEN];
    assert(generate_expressions("123", 0, (char[MAX_EXPR_LEN]){0}, 0, 6, result) == 1);
}

void TestGenerateExpressions_MultipleSolutions_returnValidExpr() {
    char result[MAX_EXPR_LEN];
    assert(generate_expressions("222", 0, (char[MAX_EXPR_LEN]){0}, 0, 6, result) == 1);
}

// Запуск всех тестов
int main() {
    TestEvaluateExpression_SimpleAddition_returnValidVal();
    TestEvaluateExpression_SimpleSubtraction_returnValidVal();
    TestEvaluateExpression_SimpleMultiplication_returnValidVal();
    TestEvaluateExpression_SimpleDivision_returnValidVal();
    TestEvaluateExpression_DivisionByZero_returnMaxVal();
    TestEvaluateExpression_MixedOperations_returnValidVal();
    TestGenerateExpressions_SimpleCase_returnValidExpr();
    TestGenerateExpressions_NoValidExpression_returnZero();
    TestGenerateExpressions_LongNumber_returnValidExpr();
    TestGenerateExpressions_MultipleSolutions_returnValidExpr();

    printf("All tests passed!\n");
    return 0;
}

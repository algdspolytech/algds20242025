#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "ndigits.h"

// Тесты для evaluate_expression

void TestEvaluateExpression_SimpleAddition_returnValidVal_no1() {
    assert(evaluate_expression("3+2") == 5);
}

void TestEvaluateExpression_SimpleSubtraction_returnValidVal_no2() {
    assert(evaluate_expression("10-7") == 3);
}

void TestEvaluateExpression_SimpleMultiplication_returnValidVal_no3() {
    assert(evaluate_expression("4*3") == 12);
}

void TestEvaluateExpression_SimpleDivision_returnValidVal_no4() {
    assert(evaluate_expression("8/2") == 4);
}

void TestEvaluateExpression_DivisionByZero_returnMaxVal_no5() {
    assert(evaluate_expression("5/0") == LLONG_MAX);
}

void TestEvaluateExpression_MixedOperations_returnValidVal_no6() {
    assert(evaluate_expression("2+3*4-6/2") == 11);
}

// Тесты для generate_expressions

void TestGenerateExpressions_SimpleCase_returnValidExpr_no7() {
    char result[MAX_EXPR_LEN];
    assert(generate_expressions("12", 0, (char[MAX_EXPR_LEN]){0}, 0, 3, result) == 1);
}

void TestGenerateExpressions_NoValidExpression_returnZero_no8() {
    char result[MAX_EXPR_LEN];
    assert(generate_expressions("5", 0, (char[MAX_EXPR_LEN]){0}, 0, 100, result) == 0);
}

void TestGenerateExpressions_LongNumber_returnValidExpr_no9() {
    char result[MAX_EXPR_LEN];
    assert(generate_expressions("123", 0, (char[MAX_EXPR_LEN]){0}, 0, 6, result) == 1);
}

void TestGenerateExpressions_MultipleSolutions_returnValidExpr_no10() {
    char result[MAX_EXPR_LEN];
    assert(generate_expressions("222", 0, (char[MAX_EXPR_LEN]){0}, 0, 6, result) == 1);
}


int main() {
    TestEvaluateExpression_SimpleAddition_returnValidVal_no1();
    TestEvaluateExpression_SimpleSubtraction_returnValidVal_no2();
    TestEvaluateExpression_SimpleMultiplication_returnValidVal_no3();
    TestEvaluateExpression_SimpleDivision_returnValidVal_no4();
    TestEvaluateExpression_DivisionByZero_returnMaxVal_no5();
    TestEvaluateExpression_MixedOperations_returnValidVal_no6();
    TestGenerateExpressions_SimpleCase_returnValidExpr_no7();
    TestGenerateExpressions_NoValidExpression_returnZero_no8();
    TestGenerateExpressions_LongNumber_returnValidExpr_no9();
    TestGenerateExpressions_MultipleSolutions_returnValidExpr_no10();

    printf("All tests passed!\n");
    return 0;
}

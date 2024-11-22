#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

// ����: ���������� �������� ��������� � ���������
void TestEvalExpression_Addition_no1() {
    const char* expr = "1+2";
    long long result = eval_expression(expr);
    printf("TestEvalExpression_Addition_no1 = %s\n", result == 3 ? "Pass" : "Fail");
}

// ����: ���������� ��������� � ����������
void TestEvalExpression_Subtraction_no2() {
    const char* expr = "5-3";
    long long result = eval_expression(expr);
    printf("TestEvalExpression_Subtraction_no2 = %s\n", result == 2 ? "Pass" : "Fail");
}

// ����: ���������� ��������� � ����������
void TestEvalExpression_Multiplication_no3() {
    const char* expr = "3*4";
    long long result = eval_expression(expr);
    printf("TestEvalExpression_Multiplication_no3 = %s\n", result == 12 ? "Pass" : "Fail");
}

// ����: ���������� ��������� � ��������
void TestEvalExpression_Division_no4() {
    const char* expr = "10/2";
    long long result = eval_expression(expr);
    printf("TestEvalExpression_Division_no4 = %s\n", result == 5 ? "Pass" : "Fail");
}

// ����: ������� �� ����
void TestEvalExpression_DivisionByZero_no5() {
    const char* expr = "10/0";
    long long result = eval_expression(expr);
    printf("TestEvalExpression_DivisionByZero_no5 = %s\n", result == LLONG_MAX ? "Pass" : "Fail");
}

// ����: ��������� � ����������� �������
void TestFindExpression_SameNumbers_no6() {
    const char* A = "111111"; // ��� ����� ���������
    int B = 111111; // ������� ��������
    char result[2 * MAX_LEN] = { 0 };

    int test_result = find_expression(A, B, result);

    // �������� ������������
    printf("TestfindExpression_SameNumbers_no6 = %s\n", test_result ? "Pass" : "Fail");
}

// ����: �������� ����������� ���������� ���������
void TestFindExpression_ValidExpression_no7() {
    const char* A = "123";
    int B = 6;
    char result[2 * MAX_LEN] = { 0 };
    printf("TestFindExpression_ValidExpression_no7 = %s\n", find_expression(A, B, result) && strcmp(result, "1+2+3") == 0 ? "Pass" : "Fail");

}

// ����: �������� ���������, ������� �� ����� ���� �������
void TestFindExpression_NoSolution_no8() {
    const char* A = "12345";
    int B = 100;
    char result[2 * MAX_LEN] = { 0 };
    printf("TestFindExpression_NoSolution_no8 = %s\n", (!find_expression(A, B, result)) ? "Pass" : "Fail");
}

// ����: ����� ��������� ��� �������� ����������
void TestFindExpression_ZeroResult_no9() {
    char A[MAX_LEN] = "123";
    int B = 0;
    char result[2 * MAX_LEN] = { 0 };
    printf("TestFindExpression_ZeroResult_no9 = %s\n", find_expression(A, B, result) ? "Pass" : "Fail");
}


// ����: �������� �� ������ � ������ �������
void TestFindExpression_EmptyString_no10() {
    char A[MAX_LEN] = "";
    int B = 0;
    char result[2 * MAX_LEN] = { 0 };
    printf("TestFindExpression_EmptyString_no10 = %s\n", find_expression(A, B, result) ? "Pass" : "Fail");
}



void RunAllTests() {
    TestEvalExpression_Addition_no1();
    TestEvalExpression_Subtraction_no2();
    TestEvalExpression_Multiplication_no3();
    TestEvalExpression_Division_no4();
    TestEvalExpression_DivisionByZero_no5();
    TestFindExpression_SameNumbers_no6();
    TestFindExpression_ValidExpression_no7();
    TestFindExpression_NoSolution_no8();
    TestFindExpression_ZeroResult_no9();
    TestFindExpression_EmptyString_no10();
}

int main() {
    RunAllTests();
    return 0;
}
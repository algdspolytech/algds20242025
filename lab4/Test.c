#include "Header.h"

void TestMerge_no1() {
    char* expr = "1 2+7 8";
    char* result = merge(expr);
    if (result[0] == '1' && result[1] == '2' && result[2] == '+' && result[3] == '7' && result[4] == '8') {
        printf("Test1 - passed\n");
    }
    else {
        printf("Test1 - not passed\n");
    } 
}

void TestInsertOperator_no2() {
    char expression[MAX_EXPRESSION] = "";
    strcat(expression, "12");
    char* new_expression = insert_operator(expression, '+', 0);
    if (new_expression[0] == '1' && new_expression[1] == '+' && new_expression[2] == '2') {
        printf("Test2 - passed\n");
    }
    else {
        printf("Test2 - not passed\n");
    }
}

void TestCalculate_multiplication_no3() {
    char* expr = "3*4";
    long long result = calculate(expr);
    if (result == 12) {
        printf("Test3 - passed\n");
    }
    else {
        printf("Test3 - not passed\n");
    }
}

void TestCalculate_division_no4() {
    char* expr = "30/3";
    long long result = calculate(expr);
    if(result == 10) {
        printf("Test4 - passed\n");
    }
    else {
        printf("Test4 - not passed\n");
    }
}

void TestCalculate_division_by_zero_no5() {
    char* expr = "45/0";
    long long result = calculate(expr);
    if (result == -1) {
        printf("Test5 - passed\n");
    }
    else {
        printf("Test5 - not passed\n");
    }
}

void TestCalculate_division_with_remainder_no6() {
    char* expr = "45/13";
    long long result = calculate(expr);
    if (result == -1) {
        printf("Test6 - passed\n");
    }
    else {
        printf("Test6 - not passed\n");
    }
}
 
void TestCalculate_addition_no7() {
    char* expr = "45+13";
    long long result = calculate(expr);
    if (result == 58) {
        printf("Test7 - passed\n");
    }
    else {
        printf("Test7 - not passed\n");
    }
}


void TestCalculate_subtraction_no8() {
    char* expr = "45-13";
    long long result = calculate(expr);
    if (result == 32) {
        printf("Test8 - passed\n");
    }
    else {
        printf("Test8 - not passed\n");
    }

}

void TestCalculate_with_priority_no9(){
   char* expr = "45-13*2+21/3";
    long long result = calculate(expr);
    if (result == 26) {
        printf("Test9 - passed\n");
    }
    else {
        printf("Test9 - not passed\n");
    }
}

void TestGenerateExpr_no10() {
    char A[MAX_DIGITS] = "123";
    int B = 0;
    FILE* output_file = fopen("output.txt", "w+");
    if (!output_file) {
        printf(stderr, "Ошибка: не удалось открыть файл output.txt\n");
        return 1;
    }
    if (generate_expressions(A, B, output_file) == 0){
        printf("Test10 - passed\n");
    }
    else {
        printf("Test10 - not passed\n");
    }  
    
}

void TestGenerateExpr_no_solution_no11() {
    char A[MAX_DIGITS] = "123";
    int B = 14;
    FILE* output_file = fopen("output.txt", "w+");
    if (!output_file) {
        printf(stderr, "Ошибка: не удалось открыть файл output.txt\n");
        return 1;
    }
    if (generate_expressions(A, B, output_file) != 0) {
        printf("Test11 - passed\n");
    }
    else {
        printf("Test11 - not passed\n");
    }
}

void RunAllTests() {
    TestMerge_no1();
    TestInsertOperator_no2();
    TestCalculate_multiplication_no3();
    TestCalculate_division_no4();
    TestCalculate_division_by_zero_no5();
    TestCalculate_division_with_remainder_no6();
    TestCalculate_addition_no7();
    TestCalculate_subtraction_no8();
    TestCalculate_with_priority_no9();
    TestGenerateExpr_no10();
    TestGenerateExpr_no_solution_no11();
}

int main() {
    RunAllTests();
    return 0;
}   

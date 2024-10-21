
#include "C:/Users/vicro/Desktop/Algosy_lab2/postfix_entry/postfix_entry/postfix_entry.h"



int ASSERT_EQ(int expected, int actual, const char* message, char* test_name) {
    expected != actual && printf("Failed %s\n", test_name) &&
        printf("Assertion failed: %s\n", message) &&
        printf("Expected: %d, Actual: %d\n", expected, actual);
    return expected == actual;
}


int ASSERT_NE(int expected, int actual, const char* message, char* test_name) {
    expected == actual && printf("Failed %s\n", test_name) &&
        printf("Assertion failed: %s\n", message) &&
        printf("Expected: %d, Actual: %d\n", expected, actual);
    return expected != actual;
}

// Функция для проверки равенства символов
int ASSERT_CHAR_EQ(char expected, char actual, const char* message, char* test_name) {
    expected != actual && printf("Failed %s\n", test_name) &&
        printf("Assertion failed: %s\n", message) &&
        printf("Expected: %c, Actual: %c\n", expected, actual);
    return expected == actual;
}

// Функция для проверки равенства строк
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
    status != 0 && printf("%s - Success\n", test_name) || printf("%s - Failed\n", test_name);
}

// Тест: Инициализация стека
int Test_InitStack_no1() {
    Stack stack;
    initStack(&stack);
    int status = 1;
    status *= ASSERT_EQ(stack.top, -1, "stack.top should be -1", "Test_InitStack_no1");
    print_result_testing(status, "Test_InitStack_no1");
    return status;
}

// Тест: Проверка на пустоту пустого стека
int Test_IsEmptyForEmptyStack_no2() {
    Stack stack;
    initStack(&stack);
    int status = 1;
    status *= ASSERT_EQ(isEmpty(&stack), 1, "isEmpty should return 1 for empty stack", "Test_IsEmptyForEmptyStack_no2");
    print_result_testing(status, "Test_IsEmptyForEmptyStack_no2");
    return status;
}

// Тест: Проверка на пустоту непустого стека
int Test_IsEmptyForNonEmptyStack_no3() {
    Stack stack;
    initStack(&stack);
    push(&stack, 'a');
    int status = 1;
    status *= ASSERT_EQ(isEmpty(&stack), 0, "isEmpty should return 0 for non-empty stack", "Test_IsEmptyForNonEmptyStack_no3");
    print_result_testing(status, "Test_IsEmptyForNonEmptyStack_no3");
    return status;
}

// Тест: Проверка на полноту полного стека
int Test_IsFullForFullStack_no4() {
    Stack stack;
    initStack(&stack);
    for (int i = 0; i < MAX_SIZE; i++) {
        push(&stack, 'a');
    }
    int status = 1;
    status *= ASSERT_EQ(isFull(&stack), 1, "isFull should return 1 for full stack", "Test_IsFullForFullStack_no4");
    print_result_testing(status, "Test_IsFullForFullStack_no4");
    return status;
}

// Тест: Проверка на полноту неполного стека
int Test_IsFullForNonFullStack_no5() {
    Stack stack;
    initStack(&stack);
    for (int i = 0; i < MAX_SIZE - 1; i++) {
        push(&stack, 'a');
    }
    int status = 1;
    status *= ASSERT_EQ(isFull(&stack), 0, "isFull should return 0 for non-full stack", "Test_IsFullForNonFullStack_no5");
    print_result_testing(status, "Test_IsFullForNonFullStack_no5");
    return status;
}

// Тест: Добавление элемента в пустой стек
int Test_PushToEmptyStack_no6() {
    Stack stack;
    initStack(&stack);
    push(&stack, 'a');
    int status = 1;
    status *= ASSERT_CHAR_EQ(stack.data[stack.top], 'a', "stack.data[stack.top] should be 'a'", "Test_PushToEmptyStack_no6");
    print_result_testing(status, "Test_PushToEmptyStack_no6");
    return status;
}

// Тест: Удаление элемента из не пустого стека
int Test_PopFromNonEmptyStack_no7() {
    Stack stack;
    initStack(&stack);
    push(&stack, 'a');
    char popped = pop(&stack);
    int status = 1;
    status *= ASSERT_CHAR_EQ(popped, 'a', "popped value should be 'a'", "Test_PopFromNonEmptyStack_no7");
    status *= ASSERT_EQ(stack.top, -1, "stack.top should be -1 after pop", "Test_PopFromNonEmptyStack_no7");
    print_result_testing(status, "Test_PopFromNonEmptyStack_no7");
    return status;
}

// Тест: Просмотр верхнего элемента непустого стека
int Test_PeekFromNonEmptyStack_no8() {
    Stack stack;
    initStack(&stack);
    push(&stack, 'a');
    char peeked = peek(&stack);
    int status = 1;
    status *= ASSERT_CHAR_EQ(peeked, 'a', "peeked value should be 'a'", "Test_PeekFromNonEmptyStack_no8");
    status *= ASSERT_EQ(stack.top, 0, "stack.top should remain 0 after peek", "Test_PeekFromNonEmptyStack_no8");
    print_result_testing(status, "Test_PeekFromNonEmptyStack_no8");
    return status;
}

// Тест: Проверка приоритета операторов
int Test_Precedence_no9() {
    int status = 1;
    status *= ASSERT_EQ(precedence('+'), 1, "precedence of '+' should be 1", "Test_Precedence_no9");
    status *= ASSERT_EQ(precedence('-'), 1, "precedence of '-' should be 1", "Test_Precedence_no9");
    status *= ASSERT_EQ(precedence('*'), 2, "precedence of '*' should be 2", "Test_Precedence_no9");
    status *= ASSERT_EQ(precedence('/'), 2, "precedence of '/' should be 2", "Test_Precedence_no9");
    status *= ASSERT_EQ(precedence('x'), -1, "precedence of unknown operator should be -1", "Test_Precedence_no9");
    print_result_testing(status, "Test_Precedence_no9");
    return status;
}

// Тест: Преобразование инфиксной записи в постфиксную
int Test_InfixToPostfixForNonEmptyStack_no10() {
    char infix[] = "a+b*c";
    char postfix[100];
    infixToPostfix(infix, postfix);
    int status = 1;
    status *= ASSERT_STR_EQ(postfix, "abc*+", "postfix should be 'abc*+'", "Test_InfixToPostfixForNonEmptyStack_no10");
    print_result_testing(status, "Test_InfixToPostfixForNonEmptyStack_no10");
    return status;
}

int main() {
    int result_testing = 1;
    result_testing *= Test_InitStack_no1();
    result_testing *= Test_IsEmptyForEmptyStack_no2();
    result_testing *= Test_IsEmptyForNonEmptyStack_no3();
    result_testing *= Test_IsFullForFullStack_no4();
    result_testing *= Test_IsFullForNonFullStack_no5();
    result_testing *= Test_PushToEmptyStack_no6();
    result_testing *= Test_PopFromNonEmptyStack_no7();
    result_testing *= Test_PeekFromNonEmptyStack_no8();
    result_testing *= Test_Precedence_no9();
    result_testing *= Test_InfixToPostfixForNonEmptyStack_no10();

    result_testing == 1 && printf("All tests passed!\n") || printf("Some tests failed");
    return 0;
}

#include "pch.h"
#include <iostream>
#include <sstream>
extern "C" {
#include "../algosi3/header.h"
}

TEST(WriteOutputTest, Success_no1) {
	char* testExpr = "123456";
	EXPECT_EQ(WriteOutput(testExpr), 0);
}

TEST(CreateStackTest, Success_no2) {
	Stack* stack = CreateStack(60);
	ASSERT_NE(stack, nullptr);
	ASSERT_EQ(stack->capacity, 60);
	ASSERT_EQ(stack->top, -1);
}

TEST(PushTest, CorrectData_no3) {
	Stack* stack = CreateStack(2);
	Push(stack, 16);
	Push(stack, 36);
	ASSERT_EQ(stack->data[stack->top--], 36);
	ASSERT_EQ(stack->data[stack->top--], 16);
}

TEST(PopTest, CorrectData_no4) {
	Stack* stack = CreateStack(2);
	stack->data[++stack->top] = 16;
	ASSERT_EQ(Pop(stack), 16);
}

TEST(InfixToPostfixTest, CorrectPostfix_no5) {
	char* infix = "23+5*4-12/6";
	char* expected = "23 5 4 * + 12 6 / -";
	char* postfix = InfixToPostfix(infix);
	ASSERT_STREQ(expected, postfix);
	free(postfix);
}

TEST(InfixToPostfixTest, InvalidFormat_no6) {
	char* infix = "1 +2";
	ASSERT_DEATH(InfixToPostfix(infix), "Invalid format");
}

TEST(CalculateExpressionTest, CorrectAnswer_no7) {
	char* expression = "12+6*42/7";
	ASSERT_EQ(CalculateExpression(expression), 48);
}

TEST(RemoveSpacesTest, Succes_no8) {
	char* expression = "1 2+6*4 2/7";
	char* expected = "12+6*42/7";
	ASSERT_STREQ(RemoveSpaces(expression), expected);
}

TEST(GenerateExpressionsTest, ExpressionExists_no9) {
	char* A = "155314694522";
	int B = 126;
	ASSERT_EQ(GenerateExpressions(A, B), 1);
}

TEST(GenerateExpressionsTest, NoExpression_no10) {
	char* A = "15";
	int B = 123;
	ASSERT_EQ(GenerateExpressions(A, B), 0);
}
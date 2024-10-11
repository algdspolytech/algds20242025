#include <gtest/gtest.h>
#include <string.h>
#include "main.h"
using namespace std;

TEST(AllocationTest, EmptyInt) {
    BigInt* a = (BigInt*)malloc(sizeof(BigInt));
    init((char*)"", a);
    ASSERT_TRUE(a->head->digit == 0);
    init(NULL, a);
    ASSERT_TRUE(a->head->digit == 0);
}

TEST(ArithmeticTests, CompareTest) {
    BigInt* a = (BigInt*)malloc(sizeof(BigInt));
    BigInt* b = (BigInt*)malloc(sizeof(BigInt));

    init((char*)"228", a);
    init((char*)"228", b);
    ASSERT_TRUE(compare(a, b) == 0);

    init((char*)"1337", b);
    ASSERT_TRUE(compare(a, b) == -1);
    init((char*)"-1337", a);
    ASSERT_TRUE(compare(b, a) == 1);

    init((char*)"6775687655767587878678876", a);
    init((char*)"12318767897979", b);
    ASSERT_TRUE(compare(a, b) == 1);

    init((char*)"", b);
    ASSERT_TRUE(compare(a, b) == 1);

}



TEST(ArithmeticTests, BasicTest) {
    BigInt* a = (BigInt*)malloc(sizeof(BigInt));
    BigInt* b = (BigInt*)malloc(sizeof(BigInt));
    BigInt* result = (BigInt*)malloc(sizeof(BigInt));
    BigInt* answer = (BigInt*)malloc(sizeof(BigInt));
    
    init((char*)"600", a);
    init((char*)"412", b);
    sum(a, b, result);
    init((char*)"1012", answer);
    ASSERT_TRUE(compare(result, answer) == 0);
    multiply(result, b, a);

    init((char*)"416944", answer);
    ASSERT_TRUE(compare(a, answer) == 0);

    init((char*)"7685000", b);
    init((char*)"3204214640000", answer);
    multiply(a, b, result);
    ASSERT_TRUE(compare(result, answer) == 0);

    divide(result, b, a);
    init((char*)"416944", answer);
    ASSERT_TRUE(compare(a, answer) == 0);
}

TEST(ArithmeticTests, NullArithmetic) {
    BigInt* a = (BigInt*)malloc(sizeof(BigInt));
    BigInt* b = (BigInt*)malloc(sizeof(BigInt));
    BigInt* result = (BigInt*)malloc(sizeof(BigInt));
    BigInt* answer = (BigInt*)malloc(sizeof(BigInt));

    init((char*)"", a);
    init((char*)"123", b);

    sum(a, b, result);
    ASSERT_TRUE(compare(b, result) == 0);
    sum(b, a, result);
    ASSERT_TRUE(compare(b, result) == 0);
    subtract(b, a, result);
    ASSERT_TRUE(compare(b, result) == 0);

    init((char*)"0", answer);
    multiply(b, a, result);
    ASSERT_TRUE(compare(answer, result) == 0);
    divide(b, a, result);
    ASSERT_TRUE(compare(answer, result) == 0); // nothing changed
}

// Проверяем коммутативность, ассоциативность и дистрибутивность сложения и умножения
TEST(ArithmeticTests, CheckQualities) {
    BigInt* a = (BigInt*)malloc(sizeof(BigInt));
    BigInt* b = (BigInt*)malloc(sizeof(BigInt));
    BigInt* c = (BigInt*)malloc(sizeof(BigInt));
    BigInt* result1 = (BigInt*)malloc(sizeof(BigInt));
    BigInt* result2 = (BigInt*)malloc(sizeof(BigInt));
    BigInt* result3 = (BigInt*)malloc(sizeof(BigInt));
    BigInt* result4 = (BigInt*)malloc(sizeof(BigInt));

    init((char*)"123456", a);
    init((char*)"654321", b);
    init((char*)"111111", c);
    sum(a, b, result1);
    sum(b, a, result2);
    ASSERT_TRUE(compare(result1, result2) == 0);

    multiply(a, b, result1);
    multiply(b, a, result2);
    ASSERT_TRUE(compare(result1, result2) == 0);

    sum(a, b, result1); // result1 = a + b
    sum(result1, c, result2); // result2 = result1 + c = (a + b) + c
    sum(b, c, result1); // result1 = b + c
    sum(result1, a, result3); // result3 = result1 + a = a + (b + c)
    // => result2 = result3
    ASSERT_TRUE(compare(result2, result3) == 0);

    multiply(a, b, result1); // result1 = a * b
    multiply(result1, c, result2); // result2 = result1 * c = (a * b) * c
    multiply(b, c, result1); // result1 = b * c
    multiply(result1, a, result3); // result3 = result1 * a = (b * c) * a
    // => result2 = result3
    ASSERT_TRUE(compare(result2, result3) == 0);

    sum(a, b, result1); // result1 = a + b
    multiply(result1, c, result2); // result2 = result1 * c = (a + b) * c
    multiply(a, c, result1); // result1 = a * c
    multiply(b, c, result3); // result3 = b * c
    sum(result1, result3, result4); // result4 = result1 + result3 = a * c + b * c
    // => result2 = result4
    ASSERT_TRUE(compare(result2, result4) == 0);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

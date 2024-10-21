#include <stdio.h>
#include <gtest/gtest.h>

extern "C" {
#include <long_numbers.h>
}

TEST(LM_InitLNumber, GensValidNUmbers) {
    const char* a = "44444444444444444";
    const char* b = "132323234444";
    const char* b_alt = "000132323234444";
    const char* zero = "0";

    lNumber_t aNum = LM_InitLNumber(1, a);
    lNumber_t bNum = LM_InitLNumber(0, b_alt);
    lNumber_t zNum = LM_InitLNumber(1, zero);

    char* res1Str = LM_GetLNumberString(aNum);
    char* res2Str = LM_GetLNumberString(bNum);
    char* res3Str = LM_GetLNumberString(zNum);

    ASSERT_TRUE(aNum.isPositive);
    ASSERT_STREQ(res1Str, a);
    ASSERT_FALSE(bNum.isPositive);
    ASSERT_STREQ(res2Str, b);
    ASSERT_STREQ(res3Str, zero);

    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);
    LM_DisposeLNumber(zNum);

    free(res1Str);
    free(res2Str);
    free(res3Str);
}


TEST(LM_Add, ZeroPlusNum) {
    const char* z = "0";
    const char* n = "132323234444";

    lNumber_t zero = LM_InitLNumber(1, z);
    lNumber_t num = LM_InitLNumber(1, n);

    lNumber_t result1 = LM_Add(zero, num);
    lNumber_t result2 = LM_Add(num, zero);

    char* res1str = LM_GetLNumberString(result1);
    char* res2str = LM_GetLNumberString(result2);

    ASSERT_STREQ(res1str, n);
    ASSERT_STREQ(res2str, n);

    LM_DisposeLNumber(result1);
    LM_DisposeLNumber(result2);
    LM_DisposeLNumber(zero);
    LM_DisposeLNumber(num);

    free(res1str);
    free(res2str);
}

TEST(LM_Add, NumPlusNumGivesPos) {
    const char* a = "44444444444444444";
    const char* b = "132323234444";

    lNumber_t aNum = LM_InitLNumber(1, a);
    lNumber_t bNum = LM_InitLNumber(1, b);

    lNumber_t result = LM_Add(aNum, bNum);

    char* resStr = LM_GetLNumberString(result);

    ASSERT_EQ(1, result.isPositive);
    ASSERT_STREQ(resStr, "44444576767678888");

    LM_DisposeLNumber(result);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);

    free(resStr);
}

TEST(LM_Add, NumPlusNegNumGivesPos) {
    const char *a = "44444444444444444";
    const char *b = "132323234444";
    const char *c = "55555556";

    lNumber_t aNum = LM_InitLNumber(1, a);
    lNumber_t bNum = LM_InitLNumber(0, b);
    lNumber_t cNum = LM_InitLNumber(0, c);

    lNumber_t result1 = LM_Add(aNum, bNum);
    lNumber_t result2 = LM_Add(cNum, aNum);

    char* res1Str = LM_GetLNumberString(result1);
    char* res2Str = LM_GetLNumberString(result2);

    ASSERT_STREQ(res1Str, "44444312121210000");
    ASSERT_STREQ(res2Str, "44444444388888888");

    LM_DisposeLNumber(result1);
    LM_DisposeLNumber(result2);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);
    LM_DisposeLNumber(cNum);

    free(res1Str);
    free(res2Str);
}

TEST(LM_Add, NumPlusNegNumGivesNeg) {
    const char *a = "44444444444444444";
    const char *b = "132323234444";
    const char *c = "55555556";

    lNumber_t aNum = LM_InitLNumber(0, a);
    lNumber_t bNum = LM_InitLNumber(1, b);
    lNumber_t cNum = LM_InitLNumber(1, c);

    lNumber_t result1 = LM_Add(aNum, bNum);
    lNumber_t result2 = LM_Add(cNum, aNum);

    char* res1Str = LM_GetLNumberString(result1);
    char* res2Str = LM_GetLNumberString(result2);

    ASSERT_FALSE(result1.isPositive);
    ASSERT_STREQ(res1Str, "44444312121210000");
    ASSERT_FALSE(result2.isPositive);
    ASSERT_STREQ(res2Str, "44444444388888888");

    LM_DisposeLNumber(result1);
    LM_DisposeLNumber(result2);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);
    LM_DisposeLNumber(cNum);

    free(res1Str);
    free(res2Str);
}


TEST(LM_Multiply, OneMultNum) {
    const char* o = "1";
    const char* n = "132323234444";

    lNumber_t one = LM_InitLNumber(1, o);
    lNumber_t num = LM_InitLNumber(1, n);

    lNumber_t result1 = LM_Multiply(one, num);
    lNumber_t result2 = LM_Multiply(num, one);

    char* res1str = LM_GetLNumberString(result1);
    char* res2str = LM_GetLNumberString(result2);

    ASSERT_STREQ(res1str, n);
    ASSERT_STREQ(res2str, n);

    LM_DisposeLNumber(result1);
    LM_DisposeLNumber(result2);
    LM_DisposeLNumber(one);
    LM_DisposeLNumber(num);

    free(res1str);
    free(res2str);
}

TEST(LM_Multiply, PosMultPosGivesPos) {
    const char* a = "44444444444444444";
    const char* b = "132323234444";

    lNumber_t aNum = LM_InitLNumber(1, a);
    lNumber_t bNum = LM_InitLNumber(1, b);

    lNumber_t result = LM_Multiply(aNum, bNum);

    char* resStr = LM_GetLNumberString(result);

    ASSERT_EQ(1, result.isPositive);
    ASSERT_STREQ(resStr, "5881032641955555496745229136");

    LM_DisposeLNumber(result);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);

    free(resStr);
}

TEST(LM_Multiply, NegMultPosGivesNeg) {
    const char* a = "44444444444444444";
    const char* b = "132323234444";

    lNumber_t aNum = LM_InitLNumber(0, a);
    lNumber_t bNum = LM_InitLNumber(1, b);

    lNumber_t result = LM_Multiply(aNum, bNum);

    char* resStr = LM_GetLNumberString(result);

    ASSERT_EQ(0, result.isPositive);
    ASSERT_STREQ(resStr, "5881032641955555496745229136");

    LM_DisposeLNumber(result);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);

    free(resStr);
}

TEST(LM_Multiply, NegMultNegGivesPos) {
    const char* a = "44444444444444444";
    const char* b = "132323234444";

    lNumber_t aNum = LM_InitLNumber(0, a);
    lNumber_t bNum = LM_InitLNumber(0, b);

    lNumber_t result = LM_Multiply(aNum, bNum);

    char* resStr = LM_GetLNumberString(result);

    ASSERT_EQ(1, result.isPositive);
    ASSERT_STREQ(resStr, "5881032641955555496745229136");

    LM_DisposeLNumber(result);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);

    free(resStr);
}


TEST(LM_Power, BigNumber) {
    const char* a = "2";
    const char* b = "300";

    lNumber_t aNum = LM_InitLNumber(1, a);
    lNumber_t bNum = LM_InitLNumber(1, b);

    lNumber_t result = LM_Power(aNum, bNum);

    char* resStr = LM_GetLNumberString(result);

    ASSERT_EQ(1, result.isPositive);
    ASSERT_STREQ(resStr, "2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376");

    LM_DisposeLNumber(result);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);
    free(resStr);
}

TEST(LM_Power, NegGivesPos) {
    const char* a = "2";
    const char* b = "10";

    lNumber_t aNum = LM_InitLNumber(0, a);
    lNumber_t bNum = LM_InitLNumber(1, b);

    lNumber_t result = LM_Power(aNum, bNum);

    char* resStr = LM_GetLNumberString(result);

    ASSERT_EQ(1, result.isPositive);
    ASSERT_STREQ(resStr, "1024");

    LM_DisposeLNumber(result);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);
    free(resStr);
}

TEST(LM_Power, NegGivesNeg) {
    const char* a = "2";
    const char* b = "11";

    lNumber_t aNum = LM_InitLNumber(0, a);
    lNumber_t bNum = LM_InitLNumber(1, b);

    lNumber_t result = LM_Power(aNum, bNum);

    char* resStr = LM_GetLNumberString(result);

    ASSERT_EQ(0, result.isPositive);
    ASSERT_STREQ(resStr, "2048");

    LM_DisposeLNumber(result);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);
    free(resStr);
}

TEST(LM_Power, NumToZero) {
    const char* a = "2";
    const char* b = "0";

    lNumber_t aNum = LM_InitLNumber(0, a);
    lNumber_t bNum = LM_InitLNumber(1, b);

    lNumber_t result = LM_Power(aNum, bNum);

    char* resStr = LM_GetLNumberString(result);

    ASSERT_EQ(1, result.isPositive);
    ASSERT_STREQ(resStr, "1");

    LM_DisposeLNumber(result);
    LM_DisposeLNumber(aNum);
    LM_DisposeLNumber(bNum);
    free(resStr);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
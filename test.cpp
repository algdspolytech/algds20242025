#include "main.h"
#include "gtest/gtest.h"
#include <string.h>

// Структура для представления монома
typedef struct {
    long long coeff;
    int power;
} Monom;

// Структура для представления полинома
typedef struct {
    Monom* monomials;
    int size;
} Polynom;

// Тестовый пример для анализа пустого многочлена
TEST(PolyTest, ParsePolynomial_EmptyString_ReturnsEmptyPoly) {
    Polynom polynomial = parsePolynomial("");
    EXPECT_EQ(polynomial.size, 0);
    free(polynomial.monomials);
}

// Тестовый пример для анализа допустимой полиномиальной строки
TEST(PolyTest, ParsePolynomial_ValidString_ReturnsCorrectPoly) {
    Polynom poly = parsePolynomial("2x^2 + 4x^1 + 6");
    EXPECT_EQ((poly.size), 3);
    EXPECT_EQ(poly.monomials[0].coeff, 2);
    EXPECT_EQ(poly.monomials[0].power, 2);
    EXPECT_EQ(poly.monomials[1].coeff, 4);
    EXPECT_EQ(poly.monomials[1].power, 1);
    EXPECT_EQ(poly.monomials[2].coeff, 6);
    EXPECT_EQ(poly.monomials[2].power, 0);
    free(poly.monomials);
}

// Тестовый пример для сложения двух многочленов
TEST(PolyTest, AddPolynomials_TwoPolynomials_ReturnsSum) {
    Polynom poly1 = parsePolynomial("3x^2 + 4x^1");
    Polynom poly2 = parsePolynomial("1x^2 + 2");

    Polynom result = addPolynoms(poly1, poly2);
    EXPECT_EQ(result.size, 3);
    EXPECT_EQ(result.monomials[0].coeff, 4); // 3 + 1
    EXPECT_EQ(result.monomials[0].power, 2);
    EXPECT_EQ(result.monomials[1].coeff, 4);
    EXPECT_EQ(result.monomials[1].power, 1);
    EXPECT_EQ(result.monomials[2].coeff, 2);
    EXPECT_EQ(result.monomials[2].power, 0);
    free(poly1.monomials);
    free(poly2.monomials);
    free(result.monomials);
}

// Тестовый пример для умножения двух многочленов
TEST(PolyTest, MultiplyPolynomials_TwoPolynomials_ReturnsProduct) {
    Polynom poly1 = parsePolynomial("2x^1 + 3");
    Polynom poly2 = parsePolynomial("2x^1 + 4");

    Polynom result = multiplyPolynoms(poly1, poly2);
    EXPECT_EQ(result.size, 3);
    EXPECT_EQ(result.monomials[0].coeff, 4);
    EXPECT_EQ(result.monomials[0].power, 2);
    EXPECT_EQ(result.monomials[1].coeff, 14);
    EXPECT_EQ(result.monomials[1].power, 1);
    EXPECT_EQ(result.monomials[2].coeff, 12);
    EXPECT_EQ(result.monomials[2].power, 0);
    free(poly1.monomials);
    free(poly2.monomials);
    free(result.monomials);
}

// Тестовый пример для дифференцирования многочлена
TEST(PolyTest, DifferentiatePolynomial_ValidPoly_ReturnsDerivative) {
    Polynom poly = parsePolynomial("2x^2 + 5x + 4");

    Polynom result = differentiatePolynom(poly);
    EXPECT_EQ(result.size, 2);
    EXPECT_EQ(result.monomials[0].coeff, 4);
    EXPECT_EQ(result.monomials[0].power, 1);
    EXPECT_EQ(result.monomials[1].coeff, 5);
    EXPECT_EQ(result.monomials[1].power, 0);
    free(poly.monomials);
    free(result.monomials);
}

// Тестовый пример для форматирования многочлена
TEST(PolyTest, FormatPolynomial_ValidPoly_ReturnsCorrectString) {
    Polynom poly = parsePolynomial("2x^2 + 3x + 4");
    char* str = formatPolynomial(poly);
    ASSERT_STREQ(str, "2x^2 + 3x + 4");
    free(str);
    free(poly.monomials);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
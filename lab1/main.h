#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

// Структура для представления монома
typedef struct {
    long long coeff;
    int power;
} Monomial;

// Структура для представления полинома
typedef struct {
    Monomial* monomials;
    int size;
} Polynom;

Polynom parsePolynomial(const char* polynomialString);
Polynom addPolynoms(Polynom p1, Polynom p2);
Polynom multiplyPolynoms(Polynom p1, Polynom p2);
Polynom differentiatePolynom(Polynom p);
char* formatPolynomial(Polynom p);

#endif



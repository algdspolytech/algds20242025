#ifndef POLYNOM_H
#define POLYNOM_H

// Структура для представления монома
typedef struct Monom {
    long long coeff;
    int power;
};

// Структура для представления полинома
typedef struct Polynom {
    Monom* monomials;
    int size;
};

Polynom parsePolynom(const char* polynomialString);
char* formatPolynom(Polynom p);
Polynom addPolynoms(Polynom p1, Polynom p2);
Polynom multiplyPolynoms(Polynom p1, Polynom p2);
Polynom differentiatePolynom(Polynom p);


#endif



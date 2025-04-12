#ifndef POLYNOM_H
#define POLYNOM_H

// ��������� ��� ������������� ������
typedef struct Monom {
    long long coeff;
    int power;
};

// ��������� ��� ������������� ��������
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



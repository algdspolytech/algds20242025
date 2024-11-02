#pragma warning (disable: 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <crtdbg.h>
#include <stdbool.h>
#include "main.h" 
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

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

//Функция парсинга полинома из строки
Polynom parsePolynomial(const char* polynomialString) {
    Polynom polynomial = { NULL, 0 };
    char* token;
    char* rest = (char*)polynomialString;

    while ((token = strtok_r(rest, "+", &rest))) {
        polynomial.size++;
        polynomial.monomials = (Monomial*)realloc(polynomial.monomials, polynomial.size * sizeof(Monomial));
        char* coeffStr;
        char* expStr;

        if ((coeffStr = strtok(token, "*x^"))) {
            if (strtok(NULL, "*x^") == NULL) {
                polynomial.monomials[polynomial.size - 1].coeff = atoll(coeffStr);
                polynomial.monomials[polynomial.size - 1].power = 0;
            }
            else {
                expStr = strtok(NULL, "*x^");
                polynomial.monomials[polynomial.size - 1].coeff = atoll(coeffStr);
                polynomial.monomials[polynomial.size - 1].power = atoi(expStr);
            }
        }
    }
    return polynomial;
}

// Функция для сложения двух полиномов
Polynom addPolynoms(Polynom p1, Polynom p2) {
    Polynom result;
    result.size = 0;
    result.monomials = NULL;

    int i = 0, j = 0;
    while (i < p1.size && j < p2.size) {
        if (p1.monomials[i].power < p2.monomials[j].power) {
            result.size++;
            result.monomials = realloc(result.monomials, result.size * sizeof(Monomial));
            result.monomials[result.size - 1] = p1.monomials[i];
            i++;
        }
        else if (p1.monomials[i].power > p2.monomials[j].power) {
            result.size++;
            result.monomials = realloc(result.monomials, result.size * sizeof(Monomial));
            result.monomials[result.size - 1] = p2.monomials[j];
            j++;
        }
        else {
            Monomial monom;
            monom.coeff = p1.monomials[i].coeff + p2.monomials[j].coeff;
            monom.power = p1.monomials[i].power;
            if (monom.coeff != 0) {
                result.size++;
                result.monomials = realloc(result.monomials, result.size * sizeof(Monomial));
                result.monomials[result.size - 1] = monom;
            }
            i++;
            j++;
        }
    }

    while (i < p1.size) {
        result.size++;
        result.monomials = realloc(result.monomials, result.size * sizeof(Monomial));
        result.monomials[result.size - 1] = p1.monomials[i];
        i++;
    }

    while (j < p2.size) {
        result.size++;
        result.monomials = realloc(result.monomials, result.size * sizeof(Monomial));
        result.monomials[result.size - 1] = p2.monomials[j];
        j++;
    }

    return result;
}

// Функция для умножения двух полиномов
Polynom multiplyPolynoms(Polynom p1, Polynom p2) {
    Polynom result;
    result.size = 0;
    result.monomials = NULL;

    for (int i = 0; i < p1.size; i++) {
        for (int j = 0; j < p2.size; j++) {
            Monomial monom;
            monom.coeff = p1.monomials[i].coeff * p2.monomials[j].coeff;
            monom.power = p1.monomials[i].power + p2.monomials[j].power;
            if (monom.coeff != 0) {
                int k;
                for (k = 0; k < result.size; k++) {
                    if (result.monomials[k].power == monom.power) {
                        result.monomials[k].coeff += monom.coeff;
                        break;
                    }
                }
                if (k == result.size) {
                    result.size++;
                    result.monomials = realloc(result.monomials, result.size * sizeof(Monomial));
                    result.monomials[result.size - 1] = monom;
                }
            }
        }
    }

    return result;
}

// Функция для дифференцирования полинома
Polynom differentiatePolynom(Polynom p) {
    Polynom result;
    result.size = 0;
    result.monomials = NULL;

    for (int i = 0; i < p.size; i++) {
        Monomial monom;
        monom.coeff = p.monomials[i].coeff * p.monomials[i].power;
        monom.power = p.monomials[i].power - 1;
        if (monom.power >= 0 && monom.coeff != 0) {
            result.size++;
            result.monomials = realloc(result.monomials, result.size * sizeof(Monomial));
            result.monomials[result.size - 1] = monom;
        }
    }

    return result;
}

char* formatPolynomial(Polynom p) {
    if (p.size == 0) {
        return strdup("0");
    }

    char* result = (char*)malloc(1);
    result[0] = '\0';

    for (int i = 0; i < p.size; i++) {
        char monomialStr[100];
        long long coeff = p.monomials[i].coeff;
        int power = p.monomials[i].power;

        if (coeff == 0) continue;

        if (coeff == -1 && power != 0) {
            sprintf(monomialStr, "-");
        }
        else if (coeff != 1 || power == 0) {
            sprintf(monomialStr, "%lld", coeff);
        }
        else {
            monomialStr[0] = '\0';
        }

        if (power > 0) {
            if (coeff != -1 && strlen(monomialStr) > 0) strcat(monomialStr, "*");
            if (power == 1) {
                strcat(monomialStr, "x");
            }
            else {
                sprintf(monomialStr + strlen(monomialStr), "x^%d", power);
            }
        }

        char* newResult = (char*)malloc(strlen(result) + strlen(monomialStr) + 2);
        strcpy(newResult, result);
        free(result);
        if (strlen(newResult) > 0 && coeff > 0) strcat(newResult, "+");
        strcat(newResult, monomialStr);
        result = newResult;
    }

    if (strlen(result) > 1 && result[0] == '+') {
        memmove(result, result + 1, strlen(result));
    }

    return result;
}

int main() {

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        fprintf(stderr, "Error opening files.\n");
        return 1;
    }

    char line1[1024], line2[1024];
    fgets(line1, sizeof(line1), inputFile);
    fgets(line2, sizeof(line2), inputFile);


    Polynom p1 = parsePolynomial(line1);
    Polynom p2 = parsePolynomial(line2);

    Polynom sum = addPolynoms(p1, p2);
    Polynom product = multiplyPolynoms(p1, p2);
    Polynom derivative = differentiatePolynom(sum);

    fprintf(outputFile, "%s\n", formatPolynomial(sum));
    fprintf(outputFile, "%s\n", formatPolynomial(product));
    fprintf(outputFile, "%s\n", formatPolynomial(derivative));


    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
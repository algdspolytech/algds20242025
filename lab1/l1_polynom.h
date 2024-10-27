#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include <stdbool.h>

typedef struct monom_t {
	int degree;
	int coeff;
	struct monom_t* next;
} monom_t;

typedef struct {
	monom_t* head;
	monom_t* tail;
} poly_t;

int is_sign(char c);

char* int_to_char(const int number);

poly_t* initialize_poly();

monom_t* new_monom_in_begin(poly_t* poly, int degree, int coeff);

monom_t* new_monom_in_end(poly_t* poly, int degree, int coeff);

monom_t* new_monom_after_current(poly_t* poly, monom_t* last, int degree, int coeff);

monom_t* find(poly_t* poly, int degree);

monom_t* find_after_which(poly_t* poly, int degree);

poly_t* sort_poly(poly_t* poly);

char* read_poly_from_file(FILE* file);

poly_t* read_poly_from_str(char* str);

int StrLength(char const* str);

void print_text(char* paragraph);

char* poly_in_str(poly_t* poly);

void free_poly(poly_t* poly);

poly_t* diff_poly(poly_t* poly);

poly_t* copy_poly(poly_t* poly);

poly_t* sum_poly(poly_t* poly1, poly_t* poly2);

poly_t* mul_poly(poly_t* poly1, poly_t* poly2);

void print_coeffs(poly_t* list);

poly_t* create_poly_from_data(int* degrees, int* coeffs, int num_monoms);

void output(char* filename, poly_t* poly1, poly_t* poly2, poly_t* poly3);
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdbool.h>
#pragma warning (disable: 4996)

#include "poly.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("Reading Error\n");
	}
	char *polys1 = read_poly_from_file(file);
	char *polys2 = read_poly_from_file(file);

	fclose(file);

	poly_t* poly1 = read_poly_from_str(polys1);
	poly_t* poly2 = read_poly_from_str(polys2);

	poly_t* poly_sum = sum_poly(poly1, poly2);
	poly_t* poly_mul = mul_poly(poly1, poly2);
	poly_t* poly_diff = diff_poly(poly1);

	poly_t* sorted_poly_sum = sort_poly(poly_sum);
	poly_t* sorted_poly_mul = sort_poly(poly_mul);
	poly_t* sorted_poly_diff = sort_poly(poly_diff);

	output("output.txt", sorted_poly_sum, sorted_poly_mul, sorted_poly_diff);

	free_poly(poly1);
	free_poly(poly2);
	free_poly(poly_sum);
	free_poly(poly_mul);
	free_poly(poly_diff);
	free_poly(sorted_poly_sum);
	free_poly(sorted_poly_mul);
	free_poly(sorted_poly_diff);

	free(polys1);
	free(polys2);

	return 0;
}
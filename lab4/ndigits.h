#ifndef NDIGITS_H
#define NDIGITS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define MAX_A_LEN 101
#define MAX_EXPR_LEN 300

long long evaluate_expression(const char *expr);
int generate_expressions(char *a, int pos, char *expr, int expr_pos, long long b, char *result_expr);

#endif

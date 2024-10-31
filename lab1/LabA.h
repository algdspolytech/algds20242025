#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SuperHugeNum {
  uint8_t *number;
  size_t size;
} SuperHugeNum;

SuperHugeNum *number_from_string(const char *str);
SuperHugeNum *new_number_from_number(SuperHugeNum *num);

void free_number(SuperHugeNum *num);

void display_number(SuperHugeNum *number);

void add_number(SuperHugeNum *number1, SuperHugeNum *number2);
void short_mul_number(SuperHugeNum *number, uint8_t n);
void mul_number(SuperHugeNum *number1, SuperHugeNum *number2);
void pow_number(SuperHugeNum *number1, int n);

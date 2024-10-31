#include "LabA.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

SuperHugeNum *number_from_string(const char *str) {
  int length = 0;
  while (str[length] != '\0')
    length++;

  SuperHugeNum *number = (SuperHugeNum *)malloc(sizeof(SuperHugeNum));
  number->number = (uint8_t *)malloc(length / 2 + length % 2);
  number->size = length / 2 + length % 2;

  if (length % 2) {
    number->number[number->size - 1] = str[0] - '0';
  }

  for (int i = 0; i < number->size - length % 2; i++) {
    number->number[i] =
        (str[length - 2 * i - 1] - '0') + 10 * (str[length - 2 * i - 2] - '0');
  }

  return number;
}

SuperHugeNum *new_number_from_number(SuperHugeNum *num) {
  SuperHugeNum *number = (SuperHugeNum *)malloc(sizeof(SuperHugeNum));
  number->number = (uint8_t *)malloc(num->size);
  number->size = num->size;

  for (int i = 0; i < number->size; i++)
    number->number[i] = num->number[i];

  return number;
}

void free_number(SuperHugeNum *num) {
  free(num->number);
  free(num);
}

void display_number(SuperHugeNum *number) {
  for (int i = number->size - 1; i >= 0; i--)
    printf(i != number->size - 1 ? "%02i" : "%i", number->number[i]);
  printf("\n");
}

size_t _max(size_t n1, size_t n2) { return n1 > n2 ? n1 : n2; }

void add_number(SuperHugeNum *number1, SuperHugeNum *number2) {
  size_t size = number1->size;

  // Нужно уравнять длины чисел
  if (number2->size > size) {
    number1->number = (uint8_t *)realloc(number1->number, number2->size);

    for (int i = number1->size; i < number2->size; i++)
      number1->number[i] = 0;

    number1->size = number2->size;
    size = number1->size;
  }

  char b = 0;
  for (int i = 0; i < number1->size; i++) {
    int tmp = i < number2->size ? number1->number[i] + number2->number[i] + b
                                : number1->number[i] + b;

    number1->number[i] = tmp % 100;
    b = tmp / 100;
  }
  if (b) {
    number1->size++;
    number1->number = (uint8_t *)realloc(number1->number, number1->size);
    number1->number[number1->size - 1] = b;
  }
}

void short_mul_number(SuperHugeNum *number, uint8_t n) {
  char b = 0;
  for (int i = 0; i < number->size; i++) {
    int tmp = n * number->number[i] + b;

    number->number[i] = tmp % 100;
    b = tmp / 100;
  }
  if (b) {
    number->size++;
    number->number = (uint8_t *)realloc(number->number, number->size);
    number->number[number->size - 1] = b;
  }
}

void mul_number(SuperHugeNum *number1, SuperHugeNum *number2) {
  size_t size = number1->size;
  SuperHugeNum *number = number_from_string("0");

  // Нужно уравнять длины чисел
  if (number2->size > size) {
    number1->number = (uint8_t *)realloc(number1->number, number2->size);
    number->number = (uint8_t *)realloc(number->number, number2->size);

    for (int i = number1->size; i < number2->size; i++)
      number1->number[i] = 0;
    for (int i = 0; i < number2->size; i++)
      number->number[i] = 0;

    number1->size = number2->size;
    number->size = number2->size;
    size = number1->size;
  } else {
    number->number = (uint8_t *)realloc(number->number, number1->size);

    for (int i = 0; i < number1->size; i++)
      number->number[i] = 0;
    number->size = number1->size;
  }

  char b = 0;
  for (int i = 0; i < number2->size; i++) {
    SuperHugeNum *tmp_number = new_number_from_number(number1);
    short_mul_number(tmp_number, number2->number[i]);
    for (int j = 0; j < i; j++)
      short_mul_number(tmp_number, 100);

    add_number(number, tmp_number);
    free_number(tmp_number);
  }

  number1->number = (uint8_t *)realloc(number1->number, number->size);

  for (int i = 0; i < number->size; i++)
    number1->number[i] = number->number[i];
  number1->size = number->size;
}

void pow_number(SuperHugeNum *number1, int n) {
  SuperHugeNum *tmp = new_number_from_number(number1);
  for (int i = 0; i < n - 1; i++)
    mul_number(number1, tmp);
  free_number(tmp);
}

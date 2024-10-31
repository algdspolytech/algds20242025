#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Структура для больших чисел
typedef struct SuperHugeNum {
  uint8_t *number;
  size_t size;
} SuperHugeNum;

SuperHugeNum *number_from_string(
    const char *str); // Функция для создания большого числа из строки
SuperHugeNum *new_number_from_number(
    SuperHugeNum *num); // Функция для копирования больших чисел

void free_number(
    SuperHugeNum *num); // Удаление большого числа (освобождение памяти)

void display_number(SuperHugeNum *number); // Вывод числа в терминал

void add_number(SuperHugeNum *number1,
                SuperHugeNum *number2); // Функция сложения, результат сложения
                                        // записываться в number1
void short_mul_number(
    SuperHugeNum *number,
    uint8_t n); // Функция для умножения большого числа не маленькое (int)
void mul_number(
    SuperHugeNum *number1,
    SuperHugeNum *number2); // Функция для умножения большого числа на большое
void pow_number(SuperHugeNum *number1,
                int n); // Функция для возведения большого числа в степень

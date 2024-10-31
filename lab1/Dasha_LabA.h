#pragma once

#include <stdio.h>
#define N 7

// Функция для считывания списка слов из файла (считается что они разделены
// символом пробела)
char **download_words(FILE *fp);

// Функция для сравнения двух строк
int compare_strings_gt(const void *_s1, const void *_s2);

// Функция для сортировки списка слов
char **sort_words(char **words);

// Функция возвращает список слов длинной больше чем n (принимает на вход
// ОТСОРТИРОВАННЫЙ ПО НЕУБЫВАНИЮ массив слов)
char **get_words_longer_n(char **words, int n);

// Функция возвращает список слов длинной n (принимает на вход ОТСОРТИРОВАННЫЙ
// ПО НЕУБЫВАНИЮ массив слов)
char **get_words_long_n(char **words, int n);
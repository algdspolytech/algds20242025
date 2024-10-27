#ifndef MAIN_H
#define MAIN_H

// Вспомогательная функция для создания холста с заданными размерами и значениями по умолчанию
int** createCanvas(int m, int n, int defaultValue);

// Вспомогательная функция для освобождения памяти холста
void freeCanvas(int** canvas, int m);

// Функция для подсчета количества частей на холсте
int countComponents(int **canvas, int m, int n);
#endif 
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include <locale.h>

/*int main() {
    setlocale(LC_CTYPE, "Russian");
    int n, m;
    printf("Введите количество пар (x, c): ");
    scanf("%d", &n);

    Node* root = NULL;

    printf("Введите %d пар чисел (x c):\n", n);
    for (int i = 0; i < n; i++) {
        long long x, c;
        printf("Пара %d: ", i + 1);
        scanf("%lld %lld", &x, &c);
        insert(&root, x, c);
    }

    printf("Введите количество запросов: ");
    scanf("%d", &m);

    printf("Введите %d пар чисел (x y) для запросов:\n", m);
    for (int i = 0; i < m; i++) {
        long long x, y;
        printf("Запрос %d: ", i + 1);
        scanf("%lld %lld", &x, &y);
        printf("Сумма для диапазона [%lld, %lld): %lld\n", x, y, rangeSum(root, x, y));
    }

    freeTree(root);
    return 0;
}*/
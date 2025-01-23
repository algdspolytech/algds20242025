#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "interval_tree.h" // Подключите файл с реализацией дерева интервалов

void test_insert_find() {
    Node* root = NULL;
    root = insert(root, 5, 10);
    root = insert(root, 15, 20);
    root = insert(root, 25, 30);

    // Проверка на пересечение с интервалом [12, 18]
    int intervalToFind[] = { 12, 18 };
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 1);
    assert(result[0]->low == 15 && result[0]->high == 20);
}

void test_delete() {
    Node* root = NULL;
    root = insert(root, 5, 10);
    root = insert(root, 15, 20);
    root = insert(root, 25, 30);

    root = deleteNode(root, 15); // Удаляем интервал [15, 20]

    // Проверка на пересечение с интервалом [12, 18]
    int intervalToFind[] = { 12, 18 };
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 0); // Должно быть 0 пересечений
}

void test_empty_tree() {
    Node* root = NULL;

    int intervalToFind[] = { 14, 24 };
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 0); // Дерево пустое, пересечений нет
}

void test_single_element() {
    Node* root = NULL;
    root = insert(root, 10, 20); // Вставка интервала [10, 20]

    int intervalToFind[] = { 15, 18 };
    Node* result[100];
    int count = 0;
    findOverlappingIntervals(root, intervalToFind[0], intervalToFind[1], result, &count);

    assert(count == 1);
    assert(result[0]->low == 10 && result[0]->high == 20); // Должен найти [10, 20]
}

int main() {
    // Запуск тестов
    test_insert_find();
    test_delete();
    test_empty_tree();
    test_single_element();

    printf("Все тесты пройдены успешно.\n");
    return 0;
}
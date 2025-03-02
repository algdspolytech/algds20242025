#include "Header.h"
#include <stdio.h>
#include <stdlib.h>

// Тест: Вставка одного элемента
void TestInsert_SingleElement_ReturnValidVal() {
    struct Node* root = NULL;
    root = insert(root, 1, 10);
    printf("TestInsert_SingleElement_ReturnValidVal = %d\n", root->c == 10);  // Проверяем, что значение в корне равно 10
}

// Тест: Вставка нескольких элементов и проверка максимума
void TestInsert_MultipleElements_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 1, 10);
    root = insert(root, 2, 20);
    root = insert(root, 3, 15);
    printf("TestInsert_MultipleElements_ReturnValidMax = %d\n", find_max(root, 1, 4) == 20);
}

// Тест: Поиск максимума в диапазоне с одним элементом
void TestGetMax_SingleElementRange_ReturnValidVal() {
    struct Node* root = NULL;
    root = insert(root, 2, 30);
    printf("TestGetMax_SingleElementRange_ReturnValidVal = %d\n", find_max(root, 2, 3) == 30);
}

// Тест: Поиск максимума в пустом диапазоне
void TestGetMax_EmptyRange_ReturnZero() {
    struct Node* root = NULL;
    printf("TestGetMax_EmptyRange_ReturnZero = %d\n", find_max(root, 1, 2) == -1);  // Пустое дерево, должно возвращать -1 (или минимальное значение)
}

// Тест: Вставка дубликатов
void TestInsert_DuplicateKeys_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 1, 10);
    root = insert(root, 1, 20);  // Вставка с тем же ключом, но другим значением
    printf("TestInsert_DuplicateKeys_ReturnValidMax = %d\n", find_max(root, 1, 2) == 20);  // Максимум в диапазоне [1, 2) должен быть 20
}

// Тест: Вставка элементов в убывающем порядке
void TestInsert_DescendingOrder_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 3, 10);
    root = insert(root, 2, 20);
    root = insert(root, 1, 30);
    printf("TestInsert_DescendingOrder_ReturnValidMax = %d\n", find_max(root, 1, 4) == 30);
}

// Тест: Вставка элементов в возрастающем порядке
void TestInsert_AscendingOrder_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 1, 5);
    root = insert(root, 2, 15);
    root = insert(root, 3, 25);
    printf("TestInsert_AscendingOrder_ReturnValidMax = %d\n", find_max(root, 1, 4) == 25);
}

// Тест: Вставка отрицательных значений и проверка максимума
// Тест: Вставка положительных и отрицательных значений и проверка максимума в диапазоне
void TestInsert_PositiveAndNegativeValues_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 5, 50);    // Положительное значение
    root = insert(root, -10, 100); // Отрицательное значение
    root = insert(root, 15, 70);   // Положительное значение
    root = insert(root, -5, 120);  // Отрицательное значение

    // Проверяем максимальное значение в диапазоне [-10, 10)
    printf("TestInsert_PositiveAndNegativeValues_ReturnValidMax = %d\n", find_max(root, -10, 10) == 120); // Ожидаем максимум 120
}



// Тест: Проверка максимума на подмножестве элементов
void TestGetMax_SubsetRange_ReturnValidMax() {
    struct Node* root = NULL;
    root = insert(root, 1, 5);
    root = insert(root, 2, 15);
    root = insert(root, 3, 10);
    printf("TestGetMax_SubsetRange_ReturnValidMax = %d\n", find_max(root, 2, 3) == 15);
}

// Тест: Проверка максимума, когда диапазон вне имеющихся ключей
void TestGetMax_OutOfBounds_ReturnZero() {
    struct Node* root = NULL;
    root = insert(root, 2, 10);
    root = insert(root, 4, 20);
    printf("TestGetMax_OutOfBounds_ReturnZero = %d\n", find_max(root, 5, 6) == -1);  // Диапазон вне имеющихся ключей, должно быть -1
}

// Запуск всех тестов
void RunAllTests() {
    TestInsert_SingleElement_ReturnValidVal();
    TestInsert_MultipleElements_ReturnValidMax();
    TestGetMax_SingleElementRange_ReturnValidVal();
    TestGetMax_EmptyRange_ReturnZero();
    TestInsert_DuplicateKeys_ReturnValidMax();
    TestInsert_DescendingOrder_ReturnValidMax();
    TestInsert_AscendingOrder_ReturnValidMax();
    TestInsert_PositiveAndNegativeValues_ReturnValidMax();
    TestGetMax_SubsetRange_ReturnValidMax();
    TestGetMax_OutOfBounds_ReturnZero();
}

int main() {
    RunAllTests();
    return 0;
}

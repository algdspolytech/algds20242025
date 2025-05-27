#include "main.h"
#include <assert.h>

// Вставка в пустое дерево и поиск максимума
void TestInsertAndQueryMax_EmptyTree_no1() {
    Node* root = NULL;
    assert(queryMax(root, 1, 5) == -1); // Пустое дерево
    freeTree(root);
}

// Вставка одного элемента и поиск максимума
void TestInsertAndQueryMax_SingleElement_no2() {
    Node* root = NULL;
    root = insert(root, 3, 30);
    assert(queryMax(root, 1, 5) == 30); // Единственный элемент
    freeTree(root);
}

// Вставка нескольких элементов и поиск максимума на полном интервале
void TestInsertAndQueryMax_FullRange_no3() {
    Node* root = NULL;
    root = insert(root, 1, 10);
    root = insert(root, 2, 20);
    root = insert(root, 3, 30);
    assert(queryMax(root, 1, 4) == 30); // Максимум на всем интервале
    freeTree(root);
}

// Поиск максимума на интервале, который не пересекается с ключами
void TestInsertAndQueryMax_NoOverlap_no4() {
    Node* root = NULL;
    root = insert(root, 5, 50);
    root = insert(root, 10, 100);
    assert(queryMax(root, 1, 4) == -1); // Нет пересечения
    freeTree(root);
}

// Поиск максимума на интервале, который частично пересекается с ключами
void TestInsertAndQueryMax_PartialOverlap_no5() {
    Node* root = NULL;
    root = insert(root, 2, 20);
    root = insert(root, 4, 40);
    root = insert(root, 6, 60);
    assert(queryMax(root, 3, 5) == 40); // Частичное пересечение
    freeTree(root);
}

// Вставка дубликатов ключей и поиск максимума
void TestInsertAndQueryMax_DuplicateKeys_no6() {
    Node* root = NULL;
    root = insert(root, 2, 20);
    root = insert(root, 2, 30); // Дубликат ключа
    assert(queryMax(root, 2, 3) == 30); // Максимум среди дубликатов
    freeTree(root);
}

// Поиск максимума на интервале, где все ключи равны
void TestInsertAndQueryMax_AllKeysEqual_no7() {
    Node* root = NULL;
    root = insert(root, 1, 10);
    root = insert(root, 1, 20);
    root = insert(root, 1, 30);
    assert(queryMax(root, 1, 2) == 30); // Все ключи равны
    freeTree(root);
}

// Поиск максимума на интервале, где интервал вырожден (x == y)
void TestInsertAndQueryMax_DegenerateInterval_no8() {
    Node* root = NULL;
    root = insert(root, 1, 10);
    root = insert(root, 2, 20);
    assert(queryMax(root, 2, 2) == -1); // Вырожденный интервал
    freeTree(root);
}

// Поиск максимума на интервале, где интервал выходит за границы ключей
void TestInsertAndQueryMax_IntervalOutsideKeys_no9() {
    Node* root = NULL;
    root = insert(root, 5, 50);
    root = insert(root, 10, 100);
    assert(queryMax(root, 15, 20) == -1); // Интервал за границами
    freeTree(root);
}

// Поиск максимума на интервале, где интервал охватывает все ключи
void TestInsertAndQueryMax_IntervalCoversAllKeys_no10() {
    Node* root = NULL;
    root = insert(root, 3, 30);
    root = insert(root, 7, 70);
    root = insert(root, 10, 100);
    assert(queryMax(root, 1, 15) == 100); // Интервал охватывает все ключи
    freeTree(root);
}


int main() {
    TestInsertAndQueryMax_EmptyTree_no1();
    TestInsertAndQueryMax_SingleElement_no2();
    TestInsertAndQueryMax_FullRange_no3();
    TestInsertAndQueryMax_NoOverlap_no4();
    TestInsertAndQueryMax_PartialOverlap_no5();
    TestInsertAndQueryMax_DuplicateKeys_no6();
    TestInsertAndQueryMax_AllKeysEqual_no7();
    TestInsertAndQueryMax_DegenerateInterval_no8();
    TestInsertAndQueryMax_IntervalOutsideKeys_no9();
    TestInsertAndQueryMax_IntervalCoversAllKeys_no10();

    printf("All tests passed!\n");
    return 0;
}
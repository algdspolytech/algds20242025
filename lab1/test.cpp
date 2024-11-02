#include "Header.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <gtest/gtest.h>



TEST(DataProcessing, CheckWordByKey) {
    Data test_data[3] = { {"Apple", 10}, {"Banana", 20}, {"Orange", 30} };
    EXPECT_STREQ(findWordByKey(test_data, 3, 20), "Banana");
    EXPECT_STREQ(findWordByKey(test_data, 3, 40), NULL);
}

TEST(DataProcessing, CheckDuplicateKeys) {
    Data test_data[3] = { {"Apple", 10}, {"Banana", 20}, {"Orange", 20} };
    int data_size = 3;

    for (int i = 0; i < data_size; i++) {
        for (int j = i + 1; j < data_size; j++) {
            ASSERT_NE(test_data[i].key, test_data[j].key);
        }
    }
}

TEST(DataProcessing, FindWordByKey) {
    Data test_data[3] = { {"Apple", 10}, {"Banana", 20}, {"Orange", 30} };
    EXPECT_STREQ(findWordByKey(test_data, 3, 10), "Apple");
    EXPECT_STREQ(findWordByKey(test_data, 3, 30), "Orange");
    EXPECT_STREQ(findWordByKey(test_data, 3, 40), NULL);
}

TEST(DataProcessing, FindWordByKeyNonExistentKey) {
    Data test_data[3] = { {"Apple", 10}, {"Banana", 20}, {"Orange", 30} };
    EXPECT_STREQ(findWordByKey(test_data, 3, 15), NULL);
}

TEST(DataProcessing, FindWordByKeyLargeData) {
    Data test_data[5] = { {"Apple", 10}, {"Banana", 20}, {"Orange", 30}, {"Mango", 40}, {"Grape", 50} };
    EXPECT_STREQ(findWordByKey(test_data, 5, 40), "Mango");
}

TEST(DataProcessing, FindWordByKeyNegativeKey) {
    Data test_data[2] = { {"Cat", -5}, {"Dog", -10} };
    EXPECT_STREQ(findWordByKey(test_data, 2, -10), "Dog");
}

TEST(DataProcessing, CompareKeysEqual) {
    Data a = { "Apple", 20 };
    Data b = { "Banana", 20 };
    EXPECT_EQ(compareKeys(&a, &b), 0);
}

TEST(DataProcessing, CompareKeysGreaterThan) {
    Data a = { "Apple", 30 };
    Data b = { "Banana", 20 };
    EXPECT_GT(compareKeys(&a, &b), 0);
}

TEST(DataProcessing, FindWordByKeyNullData) {
    EXPECT_EQ(findWordByKey(NULL, 0, 10), NULL);
}

TEST(DataProcessing, FindWordByKeyEmptyKey) {
    Data test_data[1] = { {"Apple", 0} };
    EXPECT_STREQ(findWordByKey(test_data, 1, 0), "Apple");
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    Data data[100];
    int data_size = 0;

    while (fscanf(file, "%s %d", data[data_size].word, &data[data_size].key) == 2) {
        data_size++;
    }

    fclose(file);

    // Сортировка данных по ключам
    qsort(data, data_size, sizeof(Data), compareKeys);

    // Вывод данных
    printf("Sorted Data:\n");
    for (int i = 0; i < data_size; i++) {
        printf("%s %d\n", data[i].word, data[i].key);
    }

    // Запуск тестов
    return RUN_ALL_TESTS();
}
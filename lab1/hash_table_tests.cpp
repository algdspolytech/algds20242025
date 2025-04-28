#include "hash_table.hha.h"
#include <gtest/gtest.h>

class HashTableTest : public ::testing::Test {
protected:
    void SetUp() override {
        memset(table, 0, sizeof(table));
    }

    void TearDown() override {
        free_table();
    }
};

// 1. Тест вставки в пустую таблицу
TEST_F(HashTableTest, InsertIntoEmptyTableReturnsTrue) {
    EXPECT_TRUE(insert("apple"));
}

// 2. Тест поиска существующего элемента
TEST_F(HashTableTest, SearchExistingElementReturnsTrue) {
    insert("apple");
    EXPECT_TRUE(search("apple"));
}

// 3. Тест поиска несуществующего элемента
TEST_F(HashTableTest, SearchNonExistingElementReturnsFalse) {
    insert("apple");
    EXPECT_FALSE(search("banana"));
}

// 4. Тест вставки дубликата
TEST_F(HashTableTest, InsertDuplicateReturnsFalse) {
    insert("apple");
    EXPECT_FALSE(insert("apple"));
}

// 5. Тест обработки коллизий
TEST_F(HashTableTest, HandleCollisionsCorrectly) {
    insert("apple");  // Предположим, что hash("apple") = X
    insert("banana"); // Предположим, что hash("banana") = X (коллизия)
    EXPECT_TRUE(search("apple"));
    EXPECT_TRUE(search("banana"));
}

// 6. Тест переполнения таблицы
TEST_F(HashTableTest, InsertIntoFullTableReturnsFalse) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        char str[20];
        sprintf(str, "item%d", i);
        ASSERT_TRUE(insert(str)) << "Failed to insert on iteration " << i;
    }
    EXPECT_FALSE(insert("overflow")) << "Table should be full";
}

// 7. Тест освобождения таблицы
TEST_F(HashTableTest, FreeTableClearsAllElements) {
    insert("apple");
    insert("banana");
    free_table();
    EXPECT_FALSE(search("apple"));
    EXPECT_FALSE(search("banana"));
}

// 8. Тест функции my_strdup
TEST_F(HashTableTest, MyStrdupCreatesValidCopy) {
    const char* original = "test_string";
    char* copy = my_strdup(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(original, copy);
    free(copy);
}

// 9. Тест хэш-функции (консистентность)
TEST_F(HashTableTest, HashFunctionIsConsistent) {
    const char* str = "consistent";
    int hash1 = hash(str);
    int hash2 = hash(str);
    EXPECT_EQ(hash1, hash2) << "Hash function should return same value for same input";
}

// 10. Тест удаления и повторной вставки
TEST_F(HashTableTest, DeleteAndReinsertWorks) {
    insert("apple");
    free_table();
    EXPECT_TRUE(insert("apple")) << "Should be able to reinsert after delete";
    EXPECT_TRUE(search("apple")) << "Should find reinserted element";
}

// 11. Дополнительный тест: проверка работы с NULL
TEST_F(HashTableTest, HandleNullInputGracefully) {
    EXPECT_FALSE(insert(nullptr));
    EXPECT_FALSE(search(nullptr));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include "pch.h"

extern "C" {
#include "Lab_J.h"
}

class HashTableTest : public ::testing::Test {
  protected:
    void SetUp() override { initTable(); }
    void TearDown() override { freeTable(); }
};

TEST_F(HashTableTest, SearchEmpty) { EXPECT_EQ(searchKey("nothing"), -1); }

TEST_F(HashTableTest, InsertAndSearch) {
    insertKey("apple");
    int pos = searchKey("apple");
    EXPECT_GE(pos, 0);
    EXPECT_NE(searchKey("banana"), pos);
}

TEST_F(HashTableTest, InsertDuplicate) {
    insertKey("apple");
    int pos1 = searchKey("apple");
    insertKey("apple");
    int pos2 = searchKey("apple");
    EXPECT_EQ(pos1, pos2);
}

TEST_F(HashTableTest, DeleteExisting) {
    insertKey("orange");
    EXPECT_GE(searchKey("orange"), 0);
    deleteKey("orange");
    EXPECT_EQ(searchKey("orange"), -1);
}

TEST_F(HashTableTest, DeleteNonExisting) {
    // Должно проигнорировать
    deleteKey("ghost");
    EXPECT_EQ(searchKey("ghost"), -1);
}

TEST_F(HashTableTest, ReuseDeletedSlot) {
    insertKey("key1");
    int pos1 = searchKey("key1");
    deleteKey("key1");
    EXPECT_EQ(searchKey("key1"), -1);

    // После удаления та же строка вставляется снова —
    // желательно получить либо тот же pos, либо корректный новый.
    insertKey("key1");
    int pos2 = searchKey("key1");
    EXPECT_GE(pos2, 0);
    // pos2 может совпадать с pos1 или быть другим,
    // но поиск должен снова найти элемент.
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
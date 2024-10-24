#include "pch.h"
#include <iostream>
#include <sstream>
extern "C" {
#include "../Algosi1/main.h"
}
class InsertSortedTest : public ::testing::Test {
protected:
    Item list[MAX_LIST_SIZE];
    int size;

    void SetUp() override { size = 0; }
};

TEST_F(InsertSortedTest, InsertSingleElement_no1) {
    Item newItem = { "five", 5 };
    insert_sorted(list, &size, newItem);
    EXPECT_EQ(size, 1);
    EXPECT_EQ(list[0].key, 5);
    EXPECT_STREQ(list[0].word, "five");
}

TEST_F(InsertSortedTest, InsertElementsOutOfOrder_no2) {
    Item item1 = { "three", 3 };
    Item item2 = { "one", 1 };
    Item item3 = { "four", 4 };

    insert_sorted(list, &size, item1);
    insert_sorted(list, &size, item2);
    insert_sorted(list, &size, item3);

    EXPECT_EQ(size, 3);
    EXPECT_EQ(list[0].key, 1);
    EXPECT_EQ(list[1].key, 3);
    EXPECT_EQ(list[2].key, 4);
    EXPECT_STREQ(list[0].word, "one");
    EXPECT_STREQ(list[1].word, "three");
    EXPECT_STREQ(list[2].word, "four");
}

TEST_F(InsertSortedTest, InsertDuplicateElement_no3) {
    Item item1 = { "two", 2 };
    Item item2 = { "alsotwo", 2 };

    insert_sorted(list, &size, item1);

    EXPECT_EXIT(insert_sorted(list, &size, item2), ::testing::ExitedWithCode(1),
        "");
}

TEST_F(InsertSortedTest, InsertElementsInOrder_no4) {
    Item item1 = { "one", 1 };
    Item item2 = { "two", 2 };
    Item item3 = { "three", 3 };

    insert_sorted(list, &size, item1);
    insert_sorted(list, &size, item2);
    insert_sorted(list, &size, item3);

    EXPECT_EQ(size, 3);
    EXPECT_EQ(list[0].key, 1);
    EXPECT_EQ(list[1].key, 2);
    EXPECT_EQ(list[2].key, 3);
    EXPECT_STREQ(list[0].word, "one");
    EXPECT_STREQ(list[1].word, "two");
    EXPECT_STREQ(list[2].word, "three");
}

class FindWordByKeyTest : public ::testing::Test {
protected:
    Item item_list[3];

    void SetUp() override {
        item_list[0] = { "one", 1 };
        item_list[1] = { "two", 2 };
        item_list[2] = { "three", 3 };
    }
};

TEST_F(FindWordByKeyTest, ExistingKey_no5) {
    EXPECT_EQ(find_word_by_key(item_list, 3, 2), 1);
}

TEST_F(FindWordByKeyTest, NonExistingKey_no6) {
    EXPECT_EQ(find_word_by_key(item_list, 3, 4), 0);
}

TEST_F(FindWordByKeyTest, EmptyArray_no7) {
    Item empty_list[MAX_LIST_SIZE] = {};
    EXPECT_EQ(find_word_by_key(empty_list, 0, 1), 0);
}

class PrintListOfItemsTest : public ::testing::Test {
protected:
    void SetUp() override { Item list[MAX_LIST_SIZE]; }
};
TEST_F(PrintListOfItemsTest, EmptyArray_no8) {
    Item list[MAX_LIST_SIZE] = {};
    EXPECT_EQ(print_list(list, 0), 0);
}

TEST_F(PrintListOfItemsTest, NotEmptyArray_no9) {
    Item list[MAX_LIST_SIZE] = { {"word", 1} };
    EXPECT_EQ(print_list(list, 1), 1);
}

class ScanCheckTest : public ::testing::Test {
protected:
    FILE* file;
    Item newItem;
    void SetUp() override { file = tmpfile(); }

    void TearDown() override { fclose(file); }
};

TEST_F(ScanCheckTest, CorrectInput_no10) {
    const char* input = "apple 42";
    fprintf(file, "%s", input);
    rewind(file);

    EXPECT_EQ(scan_check(file, newItem), 1);
}

TEST_F(ScanCheckTest, WrongInput_no11) {
    const char* input = "apple one";
    fprintf(file, "%s", input);
    rewind(file);

    EXPECT_EQ(scan_check(file, newItem), 0);
}

TEST_F(ScanCheckTest, LackOfData_no12) {
    const char* input = "apple";
    fprintf(file, "%s", input);
    rewind(file);
    EXPECT_EQ(scan_check(file, newItem), 0);
}

TEST_F(ScanCheckTest, ExtraData_no13) {
    const char* input = "banana 24 extraData";
    fprintf(file, "%s", input);
    rewind(file);
    EXPECT_EQ(scan_check(file, newItem), 1);
}

TEST_F(ScanCheckTest, EmptyFile_no14) {
    rewind(file);

    EXPECT_EQ(scan_check(file, newItem), 0);
}
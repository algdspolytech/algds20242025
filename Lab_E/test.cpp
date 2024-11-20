#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
extern "C" {
    #include "Lab_E.h" // Подключаем ваш код с функциями
}

TEST(TreeTest, Four_roots) {
    Tree t1 = {"a", NULL, NULL, 0};
    Tree t2 = {"abcd", NULL, NULL, 0};
    Tree t3 = {"ab", &t1, NULL, 0};
    Tree t4 = {"abc", &t3, &t2, 0};
    Fill_width(&t4);
    EXPECT_EQ(t4.width, 10) << "Ожидалось 10";
    EXPECT_EQ(t3.width, 3) << "Ожидалось 3";
    EXPECT_EQ(t2.width, 4) << "Ожидалось 4";
    EXPECT_EQ(t1.width, 1) << "Ожидалось 1";
}

TEST(TreeTest, Three_roots) {
    Tree t1 = {"a", NULL, NULL, 0};
    Tree t2 = {"abcd", NULL, NULL, 0};
    Tree t3 = {"ab", &t1, &t2, 0};
    Fill_width(&t3);
    EXPECT_EQ(t3.width, 7) << "Ожидалось 7";
    EXPECT_EQ(t2.width, 4) << "Ожидалось 4";
    EXPECT_EQ(t1.width, 1) << "Ожидалось 1";
}

TEST(TreeTest, Two_roots) {
    Tree t1 = {"a", NULL, NULL, 0};
    Tree t2 = {"abcd", &t1, NULL, 0};
    Fill_width(&t2);
    EXPECT_EQ(t2.width, 5) << "Ожидалось 5";
    EXPECT_EQ(t1.width, 1) << "Ожидалось 1";
}

TEST(TreeTest, Single_root) {
    Tree t1 = {"a", NULL, NULL, 0};
    Fill_width(&t1);
    EXPECT_EQ(t1.width, 1) << "Ожидалось 1";
}

TEST(TreeTest, Print) {
    Tree t1 = {"a", NULL, NULL, 0};
    Tree t2 = {"abcd", NULL, NULL, 0};
    Tree t3 = {"ab", &t1, NULL, 0};
    Tree t4 = {"abc", &t3, &t2, 0};
    Fill_width(&t4);
    Print_Tree(&t4, 0);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); // Запуск всех тестов
}

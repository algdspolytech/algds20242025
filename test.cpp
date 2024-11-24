//
// Created by Александр on 02.11.2024.
//
#include "pch.h"
#include "gtest/gtest.h"
#include "lab3.h"
#include <fstream>
#include <string>


TEST(TaskSchedulerTest, ReadTasks_ValidFile_no1) {
    Task tasks[MAX_TASKS];
    int task_count, K;


    EXPECT_TRUE(read_tasks("input_test1.txt", tasks, &task_count, &K));
    EXPECT_EQ(task_count, 3);
    EXPECT_EQ(K, 15);
    EXPECT_EQ(tasks[0].cost, 5);
    EXPECT_EQ(tasks[1].cost, -3);
    EXPECT_EQ(tasks[2].cost, 8);
}


TEST(TaskSchedulerTest, ReadTasks_InvalidFile_no2) {
    Task tasks[MAX_TASKS];
    int task_count, K;


    EXPECT_FALSE(read_tasks("input_test2.txt", tasks, &task_count, &K));
}


TEST(TaskSchedulerTest, WriteSchedule_ValidOutput_no3) {
    int result_schedule[] = { 1, 2, 3 };
    int task_count = 3;

    write_schedule("output.txt", result_schedule, task_count);

    // �������� ����������� ������������� ����� "output.txt"
    std::ifstream file("output_test1.txt");
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    EXPECT_EQ(content, "1 2 3 \n");
}


TEST(TaskSchedulerTest, WriteSchedule_EmptyOutput_no4) {
    int result_schedule[MAX_TASKS] = { 0 };
    int task_count = 0;

    write_schedule("output_test2.txt", result_schedule, task_count);


    std::ifstream file("output.txt");
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    EXPECT_EQ(content, "\n");
}


TEST(TaskSchedulerTest, EmptyTaskSet_no5) {
    Task tasks[MAX_TASKS];
    int task_count = 0, K = 10;
    int result_schedule[MAX_TASKS];
    EXPECT_TRUE(process_schedule(tasks, task_count, K, result_schedule));
}


TEST(TaskSchedulerTest, WithinBudget_no6) {
    Task tasks[] = { {1, 1}, {2, 2}, {3, 3} };
    int task_count = 3, K = 10;
    int result_schedule[MAX_TASKS];
    EXPECT_TRUE(process_schedule(tasks, task_count, K, result_schedule));
}

TEST(TaskSchedulerTest, ExceedsBudget_no7) {
    Task tasks[] = { {10, 1}, {20, 2}, {30, 3} };
    int task_count = 3, K = 25;
    int result_schedule[MAX_TASKS];
    EXPECT_FALSE(process_schedule(tasks, task_count, K, result_schedule));
}

TEST(TaskSchedulerTest, ExactBudget_no8) {
    Task tasks[] = { {5, 1}, {10, 2} };
    int task_count = 2, K = 15;
    int result_schedule[MAX_TASKS];
    EXPECT_TRUE(process_schedule(tasks, task_count, K, result_schedule));
}

TEST(TaskSchedulerTest, SingleTaskExceeds_no9) {
    Task tasks[] = { {10, 1} };
    int task_count = 1, K = 5;
    int result_schedule[MAX_TASKS];
    EXPECT_FALSE(process_schedule(tasks, task_count, K, result_schedule));
}

TEST(TaskSchedulerTest, LargeTaskSet_no10) {
    Task tasks[MAX_TASKS];
    int task_count = MAX_TASKS, K = MAX_TASKS * 5;
    int result_schedule[MAX_TASKS];

    for (int i = 0; i < task_count; ++i) {
        tasks[i].cost = 5;
        tasks[i].id = i + 1;
    }

    EXPECT_TRUE(process_schedule(tasks, task_count, K, result_schedule));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>

extern "C" {
#include "main.h"
}

// Тесты для очереди на основе связного списка

// TestEnqueueLinkedQueue_no1
TEST(QueueTest, EnqueueLinkedQueue_no1) {
    LinkedQueue* queue = createLinkedQueue();
    enqueueLinkedQueue(queue, 10);
    int value;
    bool result = dequeueLinkedQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(10, value);
    destroyLinkedQueue(queue);
}

// TestDequeueLinkedQueueEmpty_no2
TEST(QueueTest, DequeueLinkedQueueEmpty_no2) {
    LinkedQueue* queue = createLinkedQueue();
    int value;
    bool result = dequeueLinkedQueue(queue, &value);
    EXPECT_FALSE(result);
    destroyLinkedQueue(queue);
}

// TestMultipleEnqueueDequeueLinked_no3
TEST(QueueTest, MultipleEnqueueDequeueLinked_no3) {
    LinkedQueue* queue = createLinkedQueue();
    enqueueLinkedQueue(queue, 1);
    enqueueLinkedQueue(queue, 2);
    enqueueLinkedQueue(queue, 3);
    int value;
    bool result;

    result = dequeueLinkedQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(1, value);

    result = dequeueLinkedQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(2, value);

    result = dequeueLinkedQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(3, value);

    result = dequeueLinkedQueue(queue, &value);
    EXPECT_FALSE(result);

    destroyLinkedQueue(queue);
}

// TestEnqueueLinkedQueueLargeNumbers_no4
TEST(QueueTest, EnqueueLinkedQueueLargeNumbers_no4) {
    LinkedQueue* queue = createLinkedQueue();
    enqueueLinkedQueue(queue, 1000);
    enqueueLinkedQueue(queue, 2000);
    int value;

    bool result = dequeueLinkedQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(1000, value);

    result = dequeueLinkedQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(2000, value);

    destroyLinkedQueue(queue);
}

// TestEnqueueLinkedQueueNegativeNumbers_no5
TEST(QueueTest, EnqueueLinkedQueueNegativeNumbers_no5) {
    LinkedQueue* queue = createLinkedQueue();
    enqueueLinkedQueue(queue, -10);
    enqueueLinkedQueue(queue, -20);
    int value;

    bool result = dequeueLinkedQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-10, value);

    result = dequeueLinkedQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-20, value);

    destroyLinkedQueue(queue);
}

// Тесты для очереди на основе массива

// TestEnqueueArrayQueue_no6
TEST(QueueTest, EnqueueArrayQueue_no6) {
    ArrayQueue* queue = createArrayQueue();
    enqueueArrayQueue(queue, 10);
    int value;
    bool result = dequeueArrayQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(10, value);
    destroyArrayQueue(queue);
}

// TestDequeueArrayQueueEmpty_no7
TEST(QueueTest, DequeueArrayQueueEmpty_no7) {
    ArrayQueue* queue = createArrayQueue();
    int value;
    bool result = dequeueArrayQueue(queue, &value);
    EXPECT_FALSE(result);
    destroyArrayQueue(queue);
}

// TestMultipleEnqueueDequeueArray_no8
TEST(QueueTest, MultipleEnqueueDequeueArray_no8) {
    ArrayQueue* queue = createArrayQueue();
    enqueueArrayQueue(queue, 1);
    enqueueArrayQueue(queue, 2);
    enqueueArrayQueue(queue, 3);
    int value;
    bool result;

    result = dequeueArrayQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(1, value);

    result = dequeueArrayQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(2, value);

    result = dequeueArrayQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(3, value);

    result = dequeueArrayQueue(queue, &value);
    EXPECT_FALSE(result);

    destroyArrayQueue(queue);
}

// TestEnqueueArrayQueueFull_no9
TEST(QueueTest, EnqueueArrayQueueFull_no9) {
    ArrayQueue* queue = createArrayQueue();
    for (int i = 0; i < MAX_SIZE; i++) {
        enqueueArrayQueue(queue, i);
    }
    EXPECT_TRUE(isFullArrayQueue(queue));
    // Здесь можно проверить поведение при переполнении
    // Но так как функция вызывает exit, тест не сможет продолжиться
    destroyArrayQueue(queue);
}

// TestEnqueueArrayQueueNegativeNumbers_no10
TEST(QueueTest, EnqueueArrayQueueNegativeNumbers_no10) {
    ArrayQueue* queue = createArrayQueue();
    enqueueArrayQueue(queue, -10);
    enqueueArrayQueue(queue, -20);
    int value;

    bool result = dequeueArrayQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-10, value);

    result = dequeueArrayQueue(queue, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(-20, value);

    destroyArrayQueue(queue);
}

// Главная функция для запуска тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

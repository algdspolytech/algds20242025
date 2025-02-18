#include "pch.h"
extern "C"
{
#include "LabC.h"
}

TEST(LabC, GrafcreateAndFree)
{
	Graf* graf = createGraf(5);
	EXPECT_EQ(graf->num_vertex, 5);
	graf = freeGraf(graf);
	EXPECT_EQ(graf, nullptr);
}
TEST(LabC, NodecreateAndFree)
{
	Node* node = createNode(5);
	EXPECT_EQ(node->vertex, 5);
	EXPECT_EQ(node->next, nullptr);
}
TEST(LabC, QueuecreateAndFree)
{
	Queue* queue = createQueue(5);
	EXPECT_EQ(queue->startQueue, 0);
	EXPECT_EQ(queue->endQueue, 0);
	queue = freeQueue(queue);
	EXPECT_EQ(queue, nullptr);
}
TEST(LabC, addQueue)
{
	Queue* queue = createQueue(5);
	queue = addQueue(queue, 5);
	EXPECT_EQ(queue->data[0], 5);
	EXPECT_EQ(queue->endQueue, 1);
	queue = addQueue(queue, 6);
	EXPECT_EQ(queue->data[1], 6);
	EXPECT_EQ(queue->endQueue, 2);
	queue = freeQueue(queue);
	EXPECT_EQ(queue, nullptr);
}
TEST(LabC, deleteQueue)
{
	Queue* queue = createQueue(5);
	queue = addQueue(queue, 5);
	queue = addQueue(queue, 6);
	queue = deleteQueue(queue);
	EXPECT_EQ(queue->startQueue, 1);
	queue = freeQueue(queue);
	EXPECT_EQ(queue, nullptr);
}
TEST(LabC, addEdge)
{
	Graf* graf = createGraf(5);
	addEdge(graf, 0, 1);
	EXPECT_EQ(graf->List[0]->vertex, 1);
	addEdge(graf, 0, 2);
	EXPECT_EQ(graf->List[0]->vertex, 2);
	EXPECT_EQ(graf->List[0]->next->vertex, 1);
	graf = freeGraf(graf);
	EXPECT_EQ(graf, nullptr);
}

TEST(LabC, RideFile)
{
	Graf* graf = ReadFile("test.txt");
	EXPECT_EQ(graf->num_vertex, 5);
	graf = freeGraf(graf);
	EXPECT_EQ(graf, nullptr);
}
TEST(LabC, BFS)
{
	Graf* graf = createGraf(5);
	addEdge(graf, 0, 1);
	addEdge(graf, 0, 2);
	addEdge(graf, 1, 2);
	addEdge(graf, 2, 3);
	addEdge(graf, 3, 4);
	int result = BFS(graf, 0, 4);
	EXPECT_EQ(result, 3);
	graf = freeGraf(graf);
	EXPECT_EQ(graf, nullptr);

}
TEST(LabC, printGraf)
{
	Graf* graf = createGraf(5);
	addEdge(graf, 0, 1);
	addEdge(graf, 0, 2);
	addEdge(graf, 1, 2);
	addEdge(graf, 2, 3);
	addEdge(graf, 3, 4);
	printGraf(graf);
	graf = freeGraf(graf);
	EXPECT_EQ(graf, nullptr);
}


TEST(LabC, BFSZerotoZero)
{
	Graf* graf = createGraf(5);
	addEdge(graf, 0, 1);
	addEdge(graf, 0, 2);
	addEdge(graf, 1, 2);
	addEdge(graf, 2, 3);
	addEdge(graf, 3, 4);
	int result = BFS(graf, 0, 0);
	EXPECT_EQ(result, 0);
	graf = freeGraf(graf);
	EXPECT_EQ(graf, nullptr);
}
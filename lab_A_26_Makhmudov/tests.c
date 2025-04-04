#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "date.h"

void TestCreateNode_returnValidValue() {
    List* node = CreateNode(15, 5, 2020, 25.5);
    assert(node != NULL);
    assert(node->day == 15);
    assert(node->month == 5);
    assert(node->year == 2020);
    assert(node->t == 25.5);
    assert(node->next == NULL);
    free(node);
}

void TestInsertBefore_returnValidValue() {
    List* node = CreateNode(10, 10, 2021, 30.0);
    InsertBefore(node, 5, 5, 2020, 15.0);

    assert(node->day == 5);
    assert(node->month == 5);
    assert(node->year == 2020);
    assert(node->t == 15.0);
    assert(node->next != NULL);

    List* nextNode = node->next;
    assert(nextNode->day == 10);
    assert(nextNode->month == 10);
    assert(nextNode->year == 2021);
    assert(nextNode->t == 30.0);

    free(node->next);
    free(node);
}

void TestReadList_EmptyFile_returnNULL() {
    FILE* fp = fopen("empty.txt", "w");
    fclose(fp);

    List* list = ReadList("empty.txt");
    assert(list == NULL);
}

void TestReadList_SingleEntry_returnValidValue() {
    FILE* fp = fopen("single.txt", "w");
    fprintf(fp, "1/1/2020 -5.5\n");
    fclose(fp);

    List* list = ReadList("single.txt");
    assert(list != NULL);
    assert(list->day == 1);
    assert(list->month == 1);
    assert(list->year == 2020);
    assert(list->t == -5.5);
    assert(list->next == NULL);

    Clear(list);
}

void TestReadList_MultipleEntriesTemperatureOrder_returnSorted() {
    FILE* fp = fopen("multi_temp.txt", "w");
    fprintf(fp, "1/1/2020 10.0\n");
    fprintf(fp, "1/1/2019 5.0\n");
    fclose(fp);

    List* list = ReadList("multi_temp.txt");
    assert(list != NULL);
    assert(list->t == 5.0);
    assert(list->next->t == 10.0);
    assert(list->next->next == NULL);

    Clear(list);
}

void TestReadList_MultipleEntriesTemperatureIsSorted_returnSorted() {
    FILE* fp = fopen("multi_temp.txt", "w");
    fprintf(fp, "1/1/2020 5.0\n");
    fprintf(fp, "1/1/2019 10.0\n");
    fclose(fp);

    List* list = ReadList("multi_temp.txt");
    assert(list != NULL);
    assert(list->t == 5.0);
    assert(list->next->t == 10.0);
    assert(list->next->next == NULL);

    Clear(list);
}

void TestReadList_SameTemperatureDateOrder_SortedByDate() {
    FILE* fp = fopen("same_temp.txt", "w");
    fprintf(fp, "2/1/2020 0.0\n");
    fprintf(fp, "1/1/2020 0.0\n");
    fclose(fp);

    List* list = ReadList("same_temp.txt");
    assert(list != NULL);
    assert(list->day == 1);
    assert(list->next->day == 2);
    assert(list->next->next == NULL);

    Clear(list);
}

void TestReadList_SameTemperatureInputDateIsSorted_SortedByDate() {
    FILE* fp = fopen("same_temp.txt", "w");
    fprintf(fp, "1/1/2020 0.0\n");
    fprintf(fp, "2/1/2020 0.0\n");
    fclose(fp);

    List* list = ReadList("same_temp.txt");
    assert(list != NULL);
    assert(list->day == 1);
    assert(list->next->day == 2);
    assert(list->next->next == NULL);

    Clear(list);
}

void TestSearch_Exists() {
    List* node1 = CreateNode(1, 1, 2020, -5.0);
    List* node2 = CreateNode(2, 2, 2020, 0.0);
    node1->next = node2;

    assert(Search(node1, 0.0) == 1);
    Clear(node1);
}

void TestSearch_NotExists() {
    List* node = CreateNode(1, 1, 2020, -5.0);
    assert(Search(node, 10.0) == 0);
    Clear(node);
}

void TestClearList_returnNULL() {
    List* node1 = CreateNode(1, 1, 2020, -5.0);
    List* node2 = CreateNode(2, 2, 2020, 0.0);
    node1->next = node2;

    List* cleared = Clear(node1);
    assert(cleared == NULL);
}

void TestPrintListBelowZero_ListIsIntact() {
    List* node1 = CreateNode(1, 1, 2020, -5.0);
    List* node2 = CreateNode(2, 2, 2020, -1.0);
    List* node3 = CreateNode(3, 3, 2020, 10.0);
    node1->next = node2;
    node2->next = node3;

    // function should traverse all nodes without crashing
    PrintListBelowZero(node1);

    // verify that the list structure is intact
    assert(node1 != NULL);
    assert(node1->next == node2);
    assert(node2->next == node3);
    assert(node3->next == NULL);

    Clear(node1);
}


int main() {
    TestCreateNode_returnValidValue();
    TestInsertBefore_returnValidValue();
    TestReadList_EmptyFile_returnNULL();
    TestReadList_SingleEntry_returnValidValue();
    TestReadList_MultipleEntriesTemperatureOrder_returnSorted();
    TestReadList_MultipleEntriesTemperatureIsSorted_returnSorted();
    TestReadList_SameTemperatureDateOrder_SortedByDate();
    TestReadList_SameTemperatureInputDateIsSorted_SortedByDate();
    TestSearch_Exists();
    TestSearch_NotExists();
    TestClearList_returnNULL();
    TestPrintListBelowZero_ListIsIntact();

    printf("All tests passed!\n");
    return 0;
}
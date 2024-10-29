#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "priority_queue.h"

void readDataFromFile(const char* filename, PriorityQueue* pq) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("������: �� ������� ������� ���� %s.\n", filename);
        return;
    }

    int data, priority;
    while (fscanf(file, "%d %d", &data, &priority) == 2) {
        enqueue(pq, data, priority);
    }

    fclose(file);
}

void executeAlgorithm(const char* outputFilename) {
    PriorityQueue* pq = createPriorityQueue();

    // ��������� ������ �� input.txt
    readDataFromFile("input.txt", pq);

    // ���������� ���������� ������� � ��������� �������� � output.txt
    FILE* outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("������: �� ������� ������� ���� �� ������ %s.\n", outputFilename);
        freeQueue(pq);
        return;
    }

    fprintf(outputFile, "���������� �������:\n");
    Node* current = pq->head;
    while (current != NULL) {
        fprintf(outputFile, "Data: %d, Priority: %d\n", current->data, current->priority);
        current = current->next;
    }

    int removedData = dequeue(pq);
    fprintf(outputFile, "������� �������: %d\n", removedData);

    fprintf(outputFile, "���������� ������� ����� ��������:\n");
    current = pq->head;
    while (current != NULL) {
        fprintf(outputFile, "Data: %d, Priority: %d\n", current->data, current->priority);
        current = current->next;
    }

    fclose(outputFile);
    freeQueue(pq);
}

// ������� ��������� ��� ������ �������
void processPriorityQueue() {
    executeAlgorithm("output.txt");
}

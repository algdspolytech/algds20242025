#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "priority_queue.h"

void readDataFromFile(const char* filename, PriorityQueue* pq) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Îøèáêà: íå óäàëîñü îòêðûòü ôàéë %s.\n", filename);
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

    // Ñ÷èòûâàåì äàííûå èç input.txt
    readDataFromFile("input.txt", pq);

    // Çàïèñûâàåì ñîäåðæèìîå î÷åðåäè è ðåçóëüòàò óäàëåíèÿ â output.txt
    FILE* outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        printf("Îøèáêà: íå óäàëîñü îòêðûòü ôàéë íà çàïèñü %s.\n", outputFilename);
        freeQueue(pq);
        return;
    }

    fprintf(outputFile, "Ñîäåðæèìîå î÷åðåäè:\n");
    Node* current = pq->head;
    while (current != NULL) {
        fprintf(outputFile, "Data: %d, Priority: %d\n", current->data, current->priority);
        current = current->next;
    }

    int removedData = dequeue(pq);
    fprintf(outputFile, "Óäàëÿåì ýëåìåíò: %d\n", removedData);

    fprintf(outputFile, "Ñîäåðæèìîå î÷åðåäè ïîñëå óäàëåíèÿ:\n");
    current = pq->head;
    while (current != NULL) {
        fprintf(outputFile, "Data: %d, Priority: %d\n", current->data, current->priority);
        current = current->next;
    }

    fclose(outputFile);
    freeQueue(pq);
}

// Âíåøíèé èíòåðôåéñ äëÿ âûçîâà ôóíêöèé
void processPriorityQueue() {
    executeAlgorithm("output.txt");
}

#include <stdio.h>
#define FILENAME "../input.txt"
#include <stdlib.h>
#include <stdbool.h>

struct Pair{
    int first;
    int second;
} typedef Pair ;

struct Carriage{
    int time;
    int num;
} typedef Carriage;

void readFile(const char* filename, int* countCarriages, int* timeBeforeDeparture,
    int* atTheStation, Carriage** carriages, int* countPairs, Pair** pairs) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fscanf(file, "%d %d %d", countCarriages, timeBeforeDeparture, atTheStation);

    *carriages = (Carriage*)malloc(sizeof(Carriage) * (*countCarriages));
    if (!(*carriages)) {
        perror("Error allocating memory for carriages");
        fclose(file);
        return;
    }

    for (size_t i = 0; i < *countCarriages; ++i) {
        fscanf(file, "%d", &(*carriages)[i].time);
        (*carriages)[i].num = i;
    }

    fscanf(file, "%d", countPairs);
    *pairs = (Pair*)malloc(sizeof(Pair) * (*countPairs));
    if (!(*pairs)) {
        perror("Error allocating memory for pairs");
        free(*carriages);
        fclose(file);
        return;
    }
    for (size_t i = 0; i < *countPairs; ++i) {
        fscanf(file, "%d %d", &(*pairs)[i].first, &(*pairs)[i].second);
        --(*pairs)[i].first;
        --(*pairs)[i].second;
     }

    fclose(file);
}

void topologicalSort(int* inDegrees, Pair* pairs, int countPairs, int countCarriages, int* sortedOrder, int* sortedCount) {
    bool* visited = (bool*)malloc(sizeof(bool) * countCarriages);
    if (!visited) {
        perror("Error allocating memory for visited");
        return;
    }

    int* queue = (int*)malloc(sizeof(int) * countCarriages);
    if (!queue) {
        perror("Error allocating memory for queue");
        return;
    }

    int front = 0, rear = 0;

    for (size_t i = 0; i < countCarriages; ++i) {
        if (!inDegrees[i]) queue[rear++] = i;
    }

    while (front < rear) {
        int current = queue[front++];
        sortedOrder[(*sortedCount)++] = current;
        // Уменьшаем степень входа для всех зависимых вагонов
        for (size_t i = 0; i < countPairs; ++i) {
            if (pairs[i].first == current) {
                inDegrees[pairs[i].second]--;
                if (inDegrees[pairs[i].second] == 0) {
                    queue[rear++] = pairs[i].second; // Добавляем в очередь, если степень входа стала нулевой
                }
            }
        }
    }
    free(queue);
    free(visited);
}

void writeFile(const char* filename){
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int countCarriages =0;
    int timeBeforeDeparture=0;
    int atTheStation=0;
    int countPairs=0;
    Carriage* carriages = NULL;
    Pair* pairs = NULL;

    readFile(FILENAME, &countCarriages, &timeBeforeDeparture, &atTheStation, &carriages, &countPairs, &pairs);

    // Построение графа зависимостей
    int* inDegrees=(int*)malloc(sizeof(int)*countCarriages);
    if (!inDegrees) {
        perror("Error allocating memory for inDegrees");
        return;
    }
    for (size_t i = 0; i < countCarriages; ++i) {inDegrees[i] = 0; }
    for (size_t i = 0; i < countPairs; ++i) inDegrees[pairs[i].second]++;

    // Топологическая сортировка
    int* sortedOrder=(int*)malloc(sizeof(int)*countCarriages);
    if (!sortedOrder) {
        perror("Error allocating memory for sortedOrder");
        return;
    }
    int sortedCount = 0;
    topologicalSort(inDegrees, pairs, countPairs, countCarriages, sortedOrder, &sortedCount);

    int totalTime = 0;
    int countAttached = 0;
    int* attachedCarriages=(int*)malloc(sizeof(int)*countCarriages);
    if (!attachedCarriages) {
        perror("Error allocating memory for attachedCarriages");
        return;
    }

    for (size_t i = 0; i < sortedCount; ++i) {
        int index = sortedOrder[i];
        if (totalTime + carriages[index].time <= timeBeforeDeparture) {
            attachedCarriages[countAttached] = carriages[index].num + 1; // Сохраняем номер зацепленного вагона
            totalTime += carriages[index].time;
            countAttached++;
        }
    }
    if (countAttached>=countCarriages-atTheStation){
        for (size_t i = 0; i < countAttached; ++i) fprintf(file, "%d ", attachedCarriages[i]);
    }
    else{
       fprintf(file, "%d ", 0) ;
    }

    free(carriages);
    free(pairs);
    free(inDegrees);
    free(sortedOrder);
    free(attachedCarriages);
}

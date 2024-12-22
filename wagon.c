#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "wagon.h"

void add_edge(Wagon* wagons, int from, int to) {
    wagons[from].adjacency_list[wagons[from].adjacency_count++] = to;
}

int read_graph_from_file(const char* filename, Wagon** wagons, int* W, int* D, int* K, int* N) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return -1;
    }

    if (!fscanf(file, "%d %d %d", W, D, K)) {
        printf("Error reading W, D, K from file!\n");
        fclose(file);
        return -1;
    }

    if ((*W) < 0 || (*D) < 0 || (*K) < 0 || (*K) > (*W)) {
        printf("\nInvalid input!\n");
        return -1;
    }

    *wagons = (Wagon*)malloc(sizeof(Wagon) * (*W));
    if (!(*wagons)) {
        printf("malloc for vertices failed!\n");
        fclose(file);
        return -1;
    }

    for (int i = 0; i < *W; i++) {
        (*wagons)[i].id = i + 1;
        if (!fscanf(file, "%d", &((*wagons)[i].time))) {
            printf("Error reading time from file!\n");
            fclose(file);
            return -1;
        }
        if ((*wagons)[i].time < 0) {
            printf("Error reading t(w[%d]) from file!\n", i);
            fclose(file);
            return -1;
        }
        (*wagons)[i].adjacency_count = 0;
        (*wagons)[i].adjacency_list = NULL;
        (*wagons)[i].in_degree = 0;
    }

    if (!fscanf(file, "%d", N)) {
        printf("Error reading N from file!\n");
        fclose(file);
        return -1;
    }

    if (N < 0) {
        printf("\nInvalid N value!\n");
        return -1;
    }

    for (int i = 0; i < *N; i++) {
        int from, to;
        if (!fscanf(file, "%d %d", &from, &to)) {
            printf("Error reading from and to from file!\n");
            fclose(file);
            return -1;
        }
        if (from <= 0) {
            printf("\nInvalid w1 value!\n");
            return -1;
        }
        if (to <= 0) {
            printf("\nInvalid w2 value!\n");
            return -1;
        }
        if (from == to) continue;
        from--; // Convert to 0-based index
        to--;   // Convert to 0-based index

        int* temp = realloc((*wagons)[from].adjacency_list,
            ((*wagons)[from].adjacency_count + 1) * sizeof(int));
        if (!temp) {
            printf("malloc for temp failed!\n");
            fclose(file);
            return -1;
        }
        (*wagons)[from].adjacency_list = temp;

        add_edge(*wagons, from, to);
        (*wagons)[to].in_degree++; // Increment in-degree of destination vertex
    }

    fclose(file);
    return 0;
}

int topological_sort(Wagon* wagons, int wagons_count, const char* outputfile_name) {
    int* queue = (int*)malloc(wagons_count * sizeof(int));
    if (!queue) {
        printf("malloc for queue failed!\n");
        return -1;
    }

    int front = 0, back = 0;

    for (int i = 0; i < wagons_count; i++) {
        if (wagons[i].in_degree == 0) {
            queue[back++] = i;
        }
    }

    int* result = malloc(wagons_count * sizeof(int));
    if (!result) {
        printf("malloc for result failed!\n");
        return -1;
    }

    int result_size = 0;

    while (front < back) {
        int vertex = queue[front++];
        result[result_size++] = wagons[vertex].id;

        for (int i = 0; i < wagons[vertex].adjacency_count; i++) {
            int adj_vertex = wagons[vertex].adjacency_list[i];
            wagons[adj_vertex].in_degree--;

            if (wagons[adj_vertex].in_degree == 0) {
                result[result_size++] = wagons[adj_vertex].id;
            }
        }
    }

    FILE* file = fopen(outputfile_name, "w");
    if (file == NULL) {
        perror("Error opening outputfile_name file");
        return 1;
    }

    for (int i = 0; i < result_size; i++) {
        fprintf(file, "%d ", result[i]);
    }

    fclose(file);

    free(queue);
    free(result);
    return 1;
}

int is_selected(int* selected_ids, int selected_count, int id) {
    for (int i = 0; i < selected_count; i++) {
        if (selected_ids[i] == id) {
            return i;
        }
    }
    return 0;
}

int wagons_sort(const char* inputfile_name, const char* outputfile_name) {
    int W, D, K, N;
    Wagon* wagons = NULL;

    if (read_graph_from_file(inputfile_name, &wagons, &W, &D, &K, &N) != 0) {
        return -1;
    }

    if (W == 0 || D == 0) {
        free(wagons);
        FILE* file = fopen(outputfile_name, "w");
        if (file == NULL) {
            perror("Error opening input file");
            return 1;
        }

        fprintf(file, "0");

        fclose(file);
        return 0;
    }

    int total_time = 0;
    int selected_count = 0;
    int* selected_ids = NULL;

    for (int i = 0; i < W; i++) {
        if (total_time + wagons[i].time <= D) {
            total_time += wagons[i].time;
            selected_count++;
            int* temp = (int*)realloc(selected_ids, selected_count * sizeof(int));
            if (temp == NULL) {
                free(selected_ids);
                return -1;
            }
            selected_ids = temp;
            selected_ids[selected_count - 1] = wagons[i].id;
        }
        else {
            wagons[i].time = -1;
            if (wagons[i].adjacency_count > 0) {
                for (int j = 0; j < wagons[i].adjacency_count; j++) {
                    int index = wagons[i].adjacency_list[j];
                    wagons[index].in_degree--;
                }
            }
        }
    }

    if (selected_count < W - K) {
        free(wagons);
        free(selected_ids);
        FILE* file = fopen(outputfile_name, "w");
        if (file == NULL) {
            perror("Error opening input file");
            return 1;
        }
        
        fprintf(file, "0");

        fclose(file);
        return 0;
    }

    Wagon* selected_wagons = malloc(selected_count * sizeof(Wagon));
    if (!selected_wagons) {
        printf("malloc for selected_vertices failed!\n");
        return -1;
    }

    int j = 0;

    for (int i = 0; i < W; i++) {
        if (wagons[i].time != -1) {
            selected_wagons[j] = wagons[i];
            selected_wagons[j].adjacency_count = 0;
            selected_wagons[j].adjacency_list = NULL;

            for (int k = 0; k < wagons[i].adjacency_count; k++) {
                int index = is_selected(selected_ids, selected_count, wagons[i].adjacency_list[k] + 1);
                if (index) {
                    int* temp = (int*)realloc(selected_wagons[j].adjacency_list, sizeof(int) * (selected_wagons[j].adjacency_count + 1));
                    if (temp == NULL) {
                        printf("\nrealloc for selected_vertices[j].adjacency_list failed!\n");
                        return -1;
                    }
                    selected_wagons[j].adjacency_list = temp;
                    selected_wagons[j].adjacency_list[selected_wagons[j].adjacency_count] = index;
                    selected_wagons[j].adjacency_count++;
                }
            }
            j++;
        }
    }

    int success = topological_sort(selected_wagons, selected_count, outputfile_name);

    for (int i = 0; i < W; i++) {
        if (wagons[i].adjacency_list != NULL) {
            free(wagons[i].adjacency_list);
        }
    }
    free(wagons);
    for (int i = 0; i < selected_count; i++) {
        if (selected_wagons[i].adjacency_list != NULL) {
            free(selected_wagons[i].adjacency_list);
        }
    }
    free(selected_wagons);
    free(selected_ids);

    return success;
}

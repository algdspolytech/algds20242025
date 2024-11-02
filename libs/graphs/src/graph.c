#include "graph.h"

#include <stdlib.h>

GR_Node_t *GR_GetAssociationList(FILE *file, int *size) {
    fscanf(file, "%i", size);

    GR_Node_t *list = malloc(sizeof(GR_Node_t) * *size);

    for (int i = 0; i < *size; i++) {
        int cnt;
        fscanf(file, "%i", &cnt);
        list[i].connectionCnt = cnt;
        list[i].connectedTo = malloc(sizeof(int) * cnt);

        for (int j = 0; j < cnt; j++) {
            fscanf(file, "%i", &list[i].connectedTo[j]);
        }
    }

    return list;
}

void GR_WriteAssociationList(FILE *file, GR_Node_t *associationList, int size) {
    fprintf(file, "%i\n", size);

    for (int i = 0; i < size; i++) {
        int cnt = associationList[i].connectionCnt;
        fprintf(file, "%i ", cnt);

        for (int j = 0; j < cnt; j++) {
            fprintf(file, "%i ", associationList[i].connectedTo[j]);
        }
        fprintf(file, "\n");
    }
}

void GR_DeleteAssociationList(GR_Node_t *associationList, int size) {
    for (int i = 0; i < size; i++) {
        free(associationList[i].connectedTo);
    }
    free(associationList);
}

int **GR_AssociationToMatrix(GR_Node_t *associationList, int n) {
    int **matrix = malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++) {
        matrix[i] = calloc(n, sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        int cnt = associationList[i].connectionCnt;
        for (int j = 0; j < cnt; j++) {
            matrix[i][associationList[i].connectedTo[j]] = 1;
        }
    }

    return matrix;
}

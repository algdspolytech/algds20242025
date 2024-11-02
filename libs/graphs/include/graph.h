#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>

typedef struct Node {
    int* connectedTo;
    int connectionCnt;
} GR_Node_t;

GR_Node_t* GR_GetAssociationList(FILE* file, int* n);
void GR_WriteAssociationList(FILE* file, GR_Node_t* associationList, int n);
void GR_DeleteAssociationList(GR_Node_t *associationList, int size);
int** GR_AssociationToMatrix(GR_Node_t* associationList, int n);

#endif //GRAPH_H

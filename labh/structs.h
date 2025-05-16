//
//  structs.h
//  LabH
//
//  Created by Фёдор Филь on 22.03.2025.
//

#ifndef structs_h
#define structs_h

#include <stdio.h>

typedef struct Node {
    int key;
    long value;
    struct Node *left;
    struct Node *right;
    long sum;
} Node;

#endif /* structs_h */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct oaoa {
    char* data;
    unsigned ds;
    struct oaoa* xor_addr;
} Node;


Node* XOR(oaoa* a, oaoa* b);
Node* add(oaoa* head, char* data);
Node* find(oaoa* head, char* key);
Node* dn(oaoa* head, Node* node);
Node* dbk(oaoa* head, char* key);
void it(oaoa* head);

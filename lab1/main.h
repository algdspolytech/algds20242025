#pragma once
#ifndef MAIN_H
#define MAIN_H

typedef struct Node {
    int digit;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int digits;
    int sign;
} BigInt;

Node* createNode(int digit);
void prependNode(BigInt* num, int digit);
void init(char* integer, BigInt* num);
void freeBigInt(BigInt* num);
char print(BigInt* num);
void reverse(BigInt* src, BigInt* dest);

int compare(BigInt* a, BigInt* b);
void sum(BigInt* a, BigInt* b, BigInt* result);
void subtract(BigInt* a, BigInt* b, BigInt* result);
void multiply(BigInt* a, BigInt* b, BigInt* result);
void divide(BigInt* a, BigInt* b, BigInt* result);

#endif

#ifndef LONG_NUMBERS_H
#define LONG_NUMBERS_H
#include <stdint.h>

typedef struct LNumberNode {
    struct LNumberNode *next;
    struct LNumberNode *prev;
    char value;
} lNumberNode_t;

typedef struct LNumber {
    unsigned char isPositive;
    lNumberNode_t *head;
    lNumberNode_t *tail;
} lNumber_t;

lNumber_t LM_InitLNumber(unsigned char isPositive, const char* numberBase);
void LM_DisposeLNumber(lNumber_t num);

char* LM_GetLNumberString(lNumber_t num);

lNumber_t LM_Add(lNumber_t a, lNumber_t b);
lNumber_t LM_Sub(lNumber_t a, lNumber_t b);
lNumber_t LM_Multiply(lNumber_t a, lNumber_t b);
lNumber_t LM_Power(lNumber_t a, lNumber_t b);

#endif //LONG_NUMBERS_H

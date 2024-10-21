#include "long_numbers.h"
#include <stddef.h>
#include <stdlib.h>


lNumber_t LM_InitLNumber(unsigned char isPositive, const char* numberBase) {
    if (numberBase[0] != '\0') {
        int i = 0;
        lNumberNode_t *prev = NULL;
        lNumberNode_t *head = NULL;
        lNumberNode_t *tail = NULL;

        while(numberBase[i] == '0' && numberBase[i + 1] != '\0') {
            i++;
        }

        while(numberBase[i] != '\0') {
            tail = malloc(sizeof(lNumberNode_t));

            tail->value = numberBase[i] - '0';
            tail->prev = prev;

            if(prev != NULL)
                prev->next = tail;
            if(head == NULL)
                head = tail;

            prev = tail;
            i++;
        }
        tail->next = NULL;

        lNumber_t res = {isPositive, head, tail};
        return res;
    }
    lNumber_t res = {isPositive, NULL, NULL};
    return res;
}

void LM_ClearLNumberNodesRec(lNumberNode_t* node) {
    if (node != NULL) {
        LM_ClearLNumberNodesRec(node->next);
        free(node);
    }
}

void LM_CleanupLeadingZeroes(lNumber_t* node) {
    lNumberNode_t *head = node->head;

    while (head != NULL && head->value == 0 && head->next != NULL) {
        node->head = node->head->next;
        node->head->prev = NULL;
        free(head);
        head = node->head;
    }
}

void LM_AddNewBlockBG(lNumber_t *num, char value) {
    //Adds new block to the beginning of number
    lNumberNode_t* node = malloc(sizeof(lNumberNode_t));
    node->value = value;
    node->prev = NULL;
    node->next = NULL;

    if(num->head != NULL) {
        node->next = num->head;
        num->head->prev = node;
        num->head = node;
    } else {
        num->head = node;
        num->tail = node;
    }
}

void LM_DisposeLNumber(lNumber_t num) { LM_ClearLNumberNodesRec(num.head); }

int LM_LengthLNumber(lNumber_t num) {
    lNumberNode_t* node = num.head;
    int length = 0;

    while(node != NULL) {
        length++;
        node = node->next;
    }

    return length;
}

unsigned char LM_BodyGte(lNumber_t a, lNumber_t b) {
    lNumberNode_t *aNode = a.head;
    lNumberNode_t *bNode = b.head;
    int aLength = LM_LengthLNumber(a);
    int bLength = LM_LengthLNumber(b);

    if(aLength > bLength)
        return 1;
    if(aLength < bLength)
        return 0;

    while(aNode != NULL) {
        if(aNode->value > bNode->value)
            return 1;
        if(aNode->value < bNode->value)
            return 0;
        aNode = aNode->next;
        bNode = bNode->next;
    }

    return 1;
}

lNumber_t LM_InternalSub(lNumber_t a, lNumber_t b) {
    //Side function: both numbers must be positive, consider using LM_Sub for subtraction

    lNumber_t res = LM_InitLNumber(1, "");

    if(LM_BodyGte(b, a)) {
        lNumber_t tmp = a;
        a = b;
        b = tmp;

        res.isPositive = 0;
    }

    unsigned char takenFromNext = 0;
    const lNumberNode_t *aNode = a.tail;
    const lNumberNode_t *bNode = b.tail;

    while(aNode != NULL || bNode != NULL) {
        char aVal = (aNode == NULL) ? 0 : aNode->value;
        char bVal = (bNode == NULL) ? 0 : bNode->value;
        char sub = 0;

        if(bVal + takenFromNext > aVal) {
            sub = 10 + aVal - bVal - takenFromNext;
            takenFromNext = 1;
        } else {
            sub = aVal - bVal - takenFromNext;
            takenFromNext = 0;
        }

        LM_AddNewBlockBG(&res, sub);
        aNode = (aNode == NULL) ? NULL : aNode->prev;
        bNode = (bNode == NULL) ? NULL : bNode->prev;
    }

    return res;
}

lNumber_t LM_InternalAdd(lNumber_t a, lNumber_t b) {
    //Side function: both numbers must be positive, consider using LM_Add for addition

    const lNumber_t res = LM_InitLNumber(a.isPositive, "");
    char overflow = 0;

    const lNumberNode_t *aNode = a.tail;
    const lNumberNode_t *bNode = b.tail;

    while (aNode != NULL || bNode != NULL) {
        char aVal = (aNode == NULL) ? 0 : aNode->value;
        char bVal = (bNode == NULL) ? 0 : bNode->value;
        char sum = 0;

        sum = aVal + bVal + overflow;
        overflow = sum / 10;
        sum = sum % 10;

        LM_AddNewBlockBG(&res, sum);
        aNode = (aNode == NULL) ? NULL : aNode->prev;
        bNode = (bNode == NULL) ? NULL : bNode->prev;
    }

    if(overflow != 0)
        LM_AddNewBlockBG(&res, overflow);

    return res;
}

lNumber_t LM_Add(lNumber_t a, lNumber_t b) {
    lNumber_t num;
    if (a.isPositive == 0 && b.isPositive == 1) {
        a.isPositive = 1;
        num = LM_InternalSub(b, a);
    }
    else if (a.isPositive == 1 && b.isPositive == 0) {
        b.isPositive = 1;
        num = LM_InternalSub(a, b);
    }
    else
        num = LM_InternalAdd(a, b);

    LM_CleanupLeadingZeroes(&num);
    return num;
}

lNumber_t LM_Sub(lNumber_t a, lNumber_t b) {
    b.isPositive = !b.isPositive;
    return LM_Add(a, b);
}

lNumber_t LM_Multiply(lNumber_t a, lNumber_t b) {
    lNumber_t res = LM_InitLNumber(1, "");

    if (LM_BodyGte(b, a)) {
        lNumber_t tmp = a;
        a = b;
        b = tmp;
    }

    int limbPos = 0;
    const lNumberNode_t *bNode = b.tail;

    while (bNode != NULL) {
        lNumber_t multPart = LM_InitLNumber(1, "");
        lNumberNode_t *aNode = a.tail;

        char overflow = 0;
        char mult = 0;

        for (int i = 0; i < limbPos; i++) {
            LM_AddNewBlockBG(&multPart, 0);
        }

        while (aNode != NULL) {
            char aVal = aNode->value;

            mult = aVal * bNode->value + overflow;
            overflow = mult / 10;
            mult = mult % 10;

            LM_AddNewBlockBG(&multPart, mult);

            aNode = aNode->prev;
        }

        if (overflow != 0)
            LM_AddNewBlockBG(&multPart, overflow);

        lNumber_t newRes = LM_Add(res, multPart);
        LM_DisposeLNumber(res);
        res = newRes;

        bNode = bNode->prev;
        limbPos++;
    }

    if (a.isPositive ^ b.isPositive)
        res.isPositive = 0;

    return res;
}

lNumber_t LM_Power(lNumber_t a, lNumber_t b) {
    lNumber_t b_buf = b;
    lNumber_t res = LM_InitLNumber(1, "1");
    lNumber_t one = LM_InitLNumber(1, "1");

    while(b_buf.head->value != 0) {
        lNumber_t tmp = LM_Multiply(res, a);
        LM_DisposeLNumber(res);
        res = tmp;

        tmp = LM_Sub(b_buf, one);
        if(b_buf.head != b.head)
            LM_DisposeLNumber(b_buf);
        b_buf = tmp;
    }

    LM_DisposeLNumber(one);

    return res;
}

char * LM_GetLNumberString(lNumber_t num) {
    int len = LM_LengthLNumber(num);
    char *string = malloc(len + 1);
    lNumberNode_t *node = num.head;

    string[len] = '\0';

    for(int i = 0; i < len; i++) {
        string[i] = node->value + '0';
        node = node->next;
    }

    return string;
}
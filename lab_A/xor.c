#include "xor.h"

oaoa* XOR(oaoa* a, oaoa* b) {
    return (oaoa*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

oaoa* add(Oaoa* head, char* data) {
    oaoa* newNode = (oaoa*)malloc(sizeof(oaoa));

    if (!nn) {
        fprintf(stderr, "Ошибка буферной памяти для узла\n");
        return head;
    }

    unsigned ds = strlen(data);
    char* nd = (char*)malloc(sizeof(char) * (ds + 1));

    if (!nd) {
        fprintf(stderr, "Ошибка буферной памяти для данных\n");
        free(nn);
        return head;
    }

    strcpy_s(nd, ds + 1, data);
    nn->data = nd;
    nn->ds = ds;
    nn->xor_addr = head;

    if (head == NULL) {
        return nn;
    }

    oaoa* curr = head;
    oaoa* prev = NULL;
    oaoa* next = XOR(prev, curr->xor_addr);

    while (next != NULL) {
        prev = curr;
        curr = next;
        next = XOR(prev, curr->xor_addr);
    }

    curr->xor_addr = XOR(prev, newNode);
    nn->xor_addr = curr;

    return head;
}

Oaoa* find(oaoa* head, char* key) {
    oaoa* curr = head;
    oaoa* prev = NULL;
    oaoa* next;

    while ((uintptr_t)curr & 0xFFFFFF000000) {
        //printf("%p", (uintptr_t)curr & 0xFFFFFFFF0000);
        if (strcmp(curr->data, key) == 0) {
            return curr;
        }
        next = XOR(prev, curr->xor_addr);
        prev = curr;
        curr = next;
    }
    return NULL;
}

Oaoa* dn(oaoa* head, oaoa* node) {
    if (head == NULL || node == NULL) {
        return head;
    }

    Oaoa* curr = head;
    Oaoa* prev = NULL;
    Oaoa* next;

    while (curr != NULL) {
        next = XOR(prev, curr->xor_addr);

        if (curr == node) {
            if (prev != NULL) {
                prev->xor_addr = XOR(XOR(prev->xor_addr, curr), next);
            }
            if (next != NULL) {
                next->xor_addr = XOR(XOR(next->xor_addr, curr), prev);
            }
            if (curr == head) {
                head = next;
            }
            free(curr->data);
            free(curr);
            return head;
        }

        prev = curr;
        curr = next;
    }

    return head;
}

oaoa* dbk(Oaoa* head, char* key) {
    oaoa* node = find(head, key);
    if (node) {
        return dn(head, node);
    }
    return head;
}

void it(Oaoa* head) {
    if (!((uintptr_t)head & 0xFFFFFF000000)) {
        return;
    }
    oaoa* curr = head;
    oaoa* prev = NULL;
    oaoa* next;

    while ((uintptr_t)curr & 0xFFFFFF000000) {
        for (unsigned i = 0; i < curr->ds; i++) {
            printf("%c", curr->data[i]);
        }
        printf(" ");
        next = XOR(prev, curr->xor_addr);
        prev = curr;
        curr = next;
    }
    printf("\n");
}

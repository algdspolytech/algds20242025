#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int digit;
	struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int digits;
    int sign;
} BigInt;

Node* createNode(int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->digit = digit;
    newNode->next = NULL;
    return newNode;
}

void prependNode(BigInt* num, int digit) {
    Node* newNode = createNode(digit);
    newNode->next = num->head;
    num->head = newNode;
    num->digits++;
}

void init(char* integer, BigInt* num) {
    num->head = NULL;
    num->digits = 0;
    if (integer != NULL && strlen(integer) > 0 && strlen(integer) > (integer[0] == '-')) {
        if (integer[0] == '-') num->sign = -1;
        else num->sign = 1;

        for (int i = (integer[0] == '-'); integer[i] != '\0'; ++i) {
            prependNode(num, integer[i] - '0');
        }
    }
    else {
        init((char*)"0", num);
    }
}

void freeBigInt(BigInt* num) {
    Node* current = num->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(num);
}

void reverse(BigInt* src, BigInt* dest) {
    dest->head = NULL;
    dest->sign = src->sign;
    dest->digits = 0;
    Node* cur = src->head;
    while (cur) {
        prependNode(dest, cur->digit);
        cur = cur->next;
    }
}

int compare(BigInt* a, BigInt* b) {
    if (a->digits > b->digits) return a->sign;
    else if (b->digits > a->digits) return -1 * b->sign;
    else {
        BigInt *tempA, *tempB;
        tempA = (BigInt*)malloc(sizeof(BigInt));
        tempB = (BigInt*)malloc(sizeof(BigInt));
        reverse(a, tempA);
        reverse(b, tempB);
        Node* curA = tempA->head;
        Node* curB = tempB->head;

        int flag = 0;

        while (curA != NULL && curB != NULL) {
            if (curA->digit > curB->digit) {
                flag = a->sign;
                break;
            }
            else if (curB->digit > curA->digit) {
                flag = -1 * b->sign;
                break;
            }
            else {
                curA = curA->next;
                curB = curB->next;
            }
        }
        freeBigInt(tempA);
        freeBigInt(tempB);
        if (flag == 0) flag = (a->sign == b->sign ? 0 : a->sign);
        return flag;
    }
}

char* print(BigInt* num) {
    char* output = (char*)malloc(sizeof(char) * (num->digits + 1 + (num->sign == -1)));
    int index = num->digits - (num->sign == 1);
    output[index+1] = '\0';
    if (num->sign == -1) {
        output[0] = '-';
    }
    Node* currentNode = num->head;
    while (currentNode) {
        output[index] = currentNode->digit + '0';
        currentNode = currentNode->next;
        --index;
    }
    return output;
}

void sum(BigInt* a, BigInt* b, BigInt* result);
void subtract(BigInt* a, BigInt* b, BigInt* result);

void sum(BigInt* a, BigInt* b, BigInt* result) {
    if (a->sign * b->sign == -1) {
        if (a->sign == -1) {
            BigInt* temp = (BigInt*)malloc(sizeof(BigInt));
            init(print(a), temp);
            temp->sign = 1;
            subtract(b, temp, result);
            freeBigInt(temp);
        }
        else {
            BigInt* temp = (BigInt*)malloc(sizeof(BigInt));
            init(print(b), temp);
            temp->sign = 1;
            subtract(a, temp, result);
            freeBigInt(temp);
        }
    }
    else {
        BigInt* resultTemp = (BigInt*)malloc(sizeof(BigInt));
        resultTemp->head = NULL;
        resultTemp->sign = a->sign;
        resultTemp->digits = 0;

        Node* curA = a->head;
        Node* curB = b->head;
        int carry = 0;

        while (curA != NULL || curB != NULL || carry != 0) {
            int sum = carry;
            if (curA != NULL) {
                sum += curA->digit;
                curA = curA->next;
            }
            if (curB != NULL) {
                sum += curB->digit;
                curB = curB->next;
            }
            prependNode(resultTemp, sum % 10);
            carry = sum / 10;
        }
        reverse(resultTemp, result);
        freeBigInt(resultTemp);
    }
}

void subtract(BigInt* a, BigInt* b, BigInt* result) {
    if (a->sign == 1 && b->sign == -1) {
        BigInt* temp = (BigInt*)malloc(sizeof(BigInt));
        init(print(b), temp);
        temp->sign = 1;
        sum(a, temp, result);
        freeBigInt(temp);
    }
    else if (a->sign == -1 && b->sign == -1) {
        BigInt* tempA = (BigInt*)malloc(sizeof(BigInt));
        init(print(a), tempA);
        tempA->sign = 1;
        BigInt* tempB = (BigInt*)malloc(sizeof(BigInt));
        init(print(b), tempB);
        tempB->sign = 1;
        subtract(tempB, tempA, result);
        freeBigInt(tempA);
        freeBigInt(tempB);
    }
    else if (a->sign == -1 && b->sign == 1) {
        BigInt* temp = (BigInt*)malloc(sizeof(BigInt));
        init(print(a), temp);
        temp->sign = 1;
        sum(b, temp, result);
        result->sign = -1;
        freeBigInt(temp);
    }
    else {
        if (compare(a, b) == 0) init((char*)"0", result);
        else if (compare(a, b) == -1) {
            subtract(b, a, result);
            result->sign = -1;
        }
        else {
            BigInt* resultTemp = (BigInt*)malloc(sizeof(BigInt));
            resultTemp->head = NULL;
            resultTemp->digits = 0;
            resultTemp->sign = 1;

            Node* curA = a->head;
            Node* curB = b->head;
            int borrow = 0;

            while (curA != NULL || curB != NULL) {
               int diff = -borrow;

               if (curA != NULL) {
                   diff += curA->digit;
                   curA = curA->next;
               }
               if (curB != NULL) {
                   diff -= curB->digit;
                   curB = curB->next;
               }

               if (diff < 0) {
                   diff += 10;
                   borrow = 1;
               }
               else borrow = 0;


               prependNode(resultTemp, diff);
            }

            while (resultTemp->head->digit == 0) {
                Node* temp = resultTemp->head;
                resultTemp->head = resultTemp->head->next;
                free(temp);
                resultTemp->digits--;
            }
            
            reverse(resultTemp, result);
            freeBigInt(resultTemp);
        }
    }
}



void multiply(BigInt* a, BigInt* b, BigInt* result) {
    if (a->sign != 1 || b->sign != 1) {
        BigInt* tempA = (BigInt*)malloc(sizeof(BigInt));
        BigInt* tempB = (BigInt*)malloc(sizeof(BigInt));

        init(print(a), tempA);
        init(print(b), tempB);
        tempA->sign = 1;
        tempB->sign = 1;
        multiply(tempA, tempB, result);

        result->sign = a->sign * b->sign;
        freeBigInt(tempA);
        freeBigInt(tempB);
        return;
    }

    init((char*)"0", result);
    if (compare(result, b) == 0) return; // b == 0
    Node* curB = b->head;
    int position = 0;

    while (curB != NULL) {
        BigInt* currentProduct = (BigInt*)malloc(sizeof(BigInt));
        currentProduct->head = NULL;
        currentProduct->digits = 0;
        currentProduct->sign = 1;

        Node* curA = a->head;
        int carry = 0;

        for (int i = 0; i < position; ++i) {
            prependNode(currentProduct, 0);
        }

        while (curA != NULL || carry != 0) {
            int product = carry;
            if (curA != NULL) {
                product += curA->digit * curB->digit;
                curA = curA->next;
            }
            prependNode(currentProduct, product % 10);
            carry = product / 10;
        }
        BigInt* tmp = (BigInt*)malloc(sizeof(BigInt));
        reverse(currentProduct, tmp);
        init(print(tmp), currentProduct);
        init(print(result), tmp);
        sum(tmp, currentProduct, result);

        curB = curB->next;
        position++;
        freeBigInt(tmp);
        freeBigInt(currentProduct);
    }

    result->sign = a->sign * b->sign;
}

void divide(BigInt* a, BigInt* b, BigInt* result) {
    BigInt* ZERO = (BigInt*)malloc(sizeof(BigInt));
    init((char*)"0", ZERO);
    if (compare(b, ZERO) == 0) {
        printf("division by zero error\n");
        return;
    }
    freeBigInt(ZERO);
    if (a->sign == 1 && b->sign == 1) {
        if (compare(a, b) == -1) init((char*)"0", result);
        else if (compare(a, b) == 0) init((char*)"1", result);
        BigInt* TEN = (BigInt*)malloc(sizeof(BigInt));
        init((char*)"10", TEN);

        BigInt* tempA = (BigInt*)malloc(sizeof(BigInt)); 
        init(print(a), tempA);
        BigInt* tempB = (BigInt*)malloc(sizeof(BigInt));
        init(print(b), tempB);

        init((char*)"0", result);

        while(compare(tempA, tempB) >= 0) {
            BigInt* multiplicator = (BigInt*)malloc(sizeof(BigInt));
            init((char*)"1", multiplicator);
            BigInt* currentSubtractor = (BigInt*)malloc(sizeof(BigInt));
            init(print(b), currentSubtractor);
            for (int i = 0; i < (tempA->digits - tempB->digits - 1); ++i) {
                BigInt* tmp = (BigInt*)malloc(sizeof(BigInt));

                multiply(currentSubtractor, TEN, tmp);
                init(print(tmp), currentSubtractor);

                multiply(multiplicator, TEN, tmp);
                init(print(tmp), multiplicator);

                freeBigInt(tmp);
            }
            while(compare(tempA, currentSubtractor) >= 0) {
                BigInt* tmp = (BigInt*)malloc(sizeof(BigInt));

                subtract(tempA, currentSubtractor, tmp);
                init(print(tmp), tempA);

                sum(result, multiplicator, tmp);
                init(print(tmp), result);

                freeBigInt(tmp);
            }
            freeBigInt(multiplicator);
            freeBigInt(currentSubtractor);
        }
        
        result->sign = a->sign * b->sign;
        freeBigInt(tempA);
        freeBigInt(tempB);
        freeBigInt(TEN);
    }
    else {
        BigInt* tempA = (BigInt*)malloc(sizeof(BigInt));
        BigInt* tempB = (BigInt*)malloc(sizeof(BigInt));

        init(print(a), tempA);
        init(print(b), tempB);
        tempA->sign = 1;
        tempB->sign = 1;
        multiply(tempA, tempB, result);

        result->sign = a->sign * b->sign;
        freeBigInt(tempA);
        freeBigInt(tempB);
        return;
    }
}

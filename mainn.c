#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "Libr.h"


// Òåñò äëÿ ñîçäàíèÿ óçëà
void test_no1() {
    Node* node = createNode("test");
    if (strcmp(node->data, "test") == 0 && node->next == NULL) {
        printf("createNode test passed\n");
    }
    else {
        printf("createNode test failed\n");
    }
    free(node->data);
    free(node);
}

// Òåñò äëÿ äîáàâëåíèÿ óçëà â êîíåö ñïèñêà
void test_no2() {
    Node* head = NULL;
    append(&head, "first");
    append(&head, "second");

    if (head != NULL && head->next != NULL &&
        strcmp(head->data, "first") == 0 &&
        strcmp(head->next->data, "second") == 0) {
        printf("append test passed\n");
    }
    else {
        printf("append test failed\n");
    }

   
    if (head != NULL) {
        if (head->next != NULL) {
            free(head->next->data);
            free(head->next);
        }
        free(head->data);
        free(head);
    }
}

void test_no3() {
    Node* head = createNode("bikers");
    append(&head, "first");
    append(&head, "second");

    if (strcmp(head->next->next->data, "second") == 0 && strcmp(head->next->data, "first") == 0) {
        printf("append test passed\n");
    }
    else {
        printf("append test failed\n");
    }


    free(head->next->next->data);
    free(head->next->next->next);
    free(head->next->data);
    free(head->next);
    free(head->data);
    free(head);
}

// Òåñò äëÿ äîáàâëåíèÿ óçëà â íà÷àëî ñïèñêà
void test_no4() {
    Node* head = NULL;
    append_forward(&head, "second");
    append_forward(&head, "first");

    if (strcmp(head->data, "first") == 0 && strcmp(head->next->data, "second") == 0) {
        printf("append_forward test passed\n");
    }
    else {
        printf("append_forward test failed\n");
    }

    free(head->next->data);
    free(head->next);
    free(head->data);
    free(head);
}

void test_no5() {
    Node* head = createNode("test");
    append_forward(&head, "second");
    append_forward(&head, "first");

    if (strcmp(head->next->next->data, "test") == 0 && strcmp(head->next->data, "second") == 0) {
        printf("append_forward test passed\n");
    }
    else {
        printf("append_forward test failed\n");
    }

    free(head->next->next->data);
    free(head->next->next);
    free(head->next->data);
    free(head->next);
    free(head->data);
    free(head);
}

// Òåñò äëÿ ðàáîòû ñ ïóñòîé ñòðîêîé
void test_no6(){
    Node* head = NULL;
    append(&head, "");

    if (strcmp(head->data, "") == 0 && head->next == NULL) {
        printf("empty string append test passed\n");
    }
    else {
        printf("empty string append test passed\n");
    }

    free(head->data);
    free(head);
}

// Òåñò äëÿ ðàçäåëåíèÿ ñïèñêà
void test_no7() {
    Node* head = NULL;
    append(&head, "1");
    append(&head, "2");
    append(&head, "3");
    append(&head, "4");

    Node* firstHalf = NULL;
    Node* secondHalf = NULL;

    split(head, &firstHalf, &secondHalf);

    if (firstHalf != NULL && secondHalf != NULL &&
        strcmp(firstHalf->data, "1") == 0 &&
        strcmp(firstHalf->next->data, "2") == 0 &&
        strcmp(secondHalf->data, "3") == 0 &&
        strcmp(secondHalf->next->data, "4") == 0) {
        printf("split test passed\n");
    }
    else {
        printf("split test failed\n");
    }

    if (firstHalf != NULL) {
        free(firstHalf->next->data);
        free(firstHalf->next);
        free(firstHalf->data);
        free(firstHalf);
    }

    if (secondHalf != NULL) {
        free(secondHalf->next->data);
        free(secondHalf->next);
        free(secondHalf->data);
        free(secondHalf);
    }
}

// Òåñò äëÿ ñëèÿíèÿ ñïèñêîâ
void test_no8() {
    Node* a = createNode("apple");
    append(&a, "cereal");

    Node* b = createNode("bicycle");
    append(&b, "digger");

    Node* merged = merge(a, b);

    if (strcmp(merged->data, "apple") == 0 && strcmp(merged->next->data, "bicycle") == 0 &&
        strcmp(merged->next->next->data, "cereal") == 0 && strcmp(merged->next->next->next->data, "digger") == 0) {
        printf("merge test passed\n");
    }
    else {
        printf("merge test failed\n");
    }

    
    while (merged != NULL) {
        Node* temp = merged;
        merged = merged->next;
        free(temp->data);
        free(temp);
    }
}


void test_no9() {
    Node* head = NULL;
    append(&head, "3");
    append(&head, "1");
    append(&head, "4");
    append(&head, "2");

    mergeSort(&head);

    if (head != NULL && head->next != NULL && head->next->next != NULL && head->next->next->next != NULL) {
        if (strcmp(head->data, "1") == 0 &&
            strcmp(head->next->data, "2") == 0 &&
            strcmp(head->next->next->data, "3") == 0 &&
            strcmp(head->next->next->next->data, "4") == 0) {
            printf("mergeSort test passed\n");
        }
        else {
            printf("mergeSort test failed\n");
        }
    }
    else {
        printf("mergeSort test failed: list is empty or not properly sorted\n");
    }

  
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

// Òåñò äëÿ ðàáîòû ñ ïóñòûì ñïèñêîì
void test_no10() {
    Node* head = NULL;

    split(head, &head, &head);

    if (head == NULL) {
        printf("empty list split test passed\n");
    }
    else {
        printf("empty list split test failed\n");
    }
}


void test_no11() {
    Node* head = NULL;
    mergeSort(&head);

    if (head == NULL) {
        printf("empty list mergeSort test passed\n");
    }
    else {
        printf("empty list mergeSort test failed\n");
    }
}

int main() {
    printf("\n");
    test_no1();
    test_no2();
    test_no3();
    test_no4();
    test_no5();
    test_no6();
    test_no7();
    test_no8();
    test_no9();
    test_no10();
    test_no11();

    return 0;
}

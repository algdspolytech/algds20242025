#include "labA.h"
#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

int compare_nodes(Node* first_node, Node* second_node) {
    while (first_node && second_node) {
        if (strcmp(first_node->last_name, second_node->last_name) != 0 || strcmp(first_node->first_name, second_node->first_name) != 0 ||
            strcmp(first_node->middle_name, second_node->middle_name) != 0 ||
            first_node->date.day != second_node->date.day ||
            first_node->date.month != second_node->date.month ||
            first_node->date.year != second_node->date.year) {
            return 0;
        }
        first_node = first_node->next;
        second_node = second_node->next;
    }
    return (first_node == NULL && second_node == NULL) ? 1 : 0;
}

TEST(_parse_, NormalInput) {
    char* line = (char*)malloc(sizeof(char) * 1000);
    strcpy(line, "Petrov Petr Petrovich 15.05.2015");

    Node* new_node = parse_line(line);
    new_node->next = NULL;

    Node* expected_node = (Node*)malloc(sizeof(Node));
    strcpy(expected_node->last_name, "Petrov");
    strcpy(expected_node->first_name, "Petr");
    strcpy(expected_node->middle_name, "Petrovich");
    expected_node->date.day = 15;
    expected_node->date.month = 05;
    expected_node->date.year = 2015;
    expected_node->next = NULL;

    EXPECT_TRUE(compare_nodes(new_node, expected_node));

    free(line);
    free(new_node);
    free(expected_node);
}

TEST(_parse_, NoInput) {
    char* line = (char*)malloc(sizeof(char) * 1000);
    strcpy(line, "");

    Node* new_node = parse_line(line);
    EXPECT_TRUE(compare_nodes(new_node, NULL));

    free(line);
    free(new_node);
}

TEST(_parse_, IncompleteInput) {
    char* line = (char*)malloc(sizeof(char) * 1000);
    strcpy(line, "Petrov Petr Petrovich");

    Node* new_node = parse_line(line);
    EXPECT_TRUE(compare_nodes(new_node, NULL));

    free(line);
    free(new_node);
}

TEST(_insert_sorted, AddToEmptyList) {
    Node* head = NULL;

    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->last_name, "Petrov");
    strcpy(new_node->first_name, "Petr");
    strcpy(new_node->middle_name, "Petrovich");
    new_node->date.day = 15;
    new_node->date.month = 05;
    new_node->date.year = 2015;

    head = insert_sorted(head, new_node);

    Node* expected_head = (Node*)malloc(sizeof(Node));
    strcpy(expected_head->last_name, "Petrov");
    strcpy(expected_head->first_name, "Petr");
    strcpy(expected_head->middle_name, "Petrovich");
    expected_head->date.day = 15;
    expected_head->date.month = 05;
    expected_head->date.year = 2015;
    expected_head->next = NULL;

    EXPECT_TRUE(compare_nodes(head, expected_head));

    free(new_node);
    free(expected_head);
}

TEST(_insert_sorted, AddToNonEmptyList) {
    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->last_name, "Sidorov");
    strcpy(head->first_name, "Pavel");
    strcpy(head->middle_name, "Pavlovich");
    head->date.day = 10;
    head->date.month = 10;
    head->date.year = 2016;
    head->next = NULL;

    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->last_name, "Petrov");
    strcpy(new_node->first_name, "Petr");
    strcpy(new_node->middle_name, "Petrovich");
    new_node->date.day = 15;
    new_node->date.month = 05;
    new_node->date.year = 2015;

    head = insert_sorted(head, new_node);

    Node* expected_head = (Node*)malloc(sizeof(Node));
    strcpy(expected_head->last_name, "Petrov");
    strcpy(expected_head->first_name, "Petr");
    strcpy(expected_head->middle_name, "Petrovich");
    expected_head->date.day = 15;
    expected_head->date.month = 05;
    expected_head->date.year = 2015;

    Node* expected_second = (Node*)malloc(sizeof(Node));
    strcpy(expected_second->last_name, "Sidorov");
    strcpy(expected_second->first_name, "Pavel");
    strcpy(expected_second->middle_name, "Pavlovich");
    expected_second->date.day = 10;
    expected_second->date.month = 10;
    expected_second->date.year = 2016;
    expected_head->next = expected_second;
    expected_second->next = NULL;

    EXPECT_TRUE(compare_nodes(head, expected_head));

    free(new_node);
    free(expected_head);
    free(expected_second);
}

TEST(_insert_sorted, AddToMiddle) {
    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->last_name, "Kuznetsov");
    strcpy(head->first_name, "Anatoly");
    strcpy(head->middle_name, "Ivanovich");
    head->date.day = 01;
    head->date.month = 02;
    head->date.year = 2007;

    Node* second_node = (Node*)malloc(sizeof(Node));
    strcpy(second_node->last_name, "Morozov");
    strcpy(second_node->first_name, "Viktor");
    strcpy(second_node->middle_name, "Alekseevich");
    second_node->date.day = 03;
    second_node->date.month = 04;
    second_node->date.year = 2008;

    head->next = second_node;
    second_node->next = NULL;

    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->last_name, "Petrov");
    strcpy(new_node->first_name, "Sergey");
    strcpy(new_node->middle_name, "Vladimirovich");
    new_node->date.day = 15;
    new_node->date.month = 01;
    new_node->date.year = 2006;

    head = insert_sorted(head, new_node);

    Node* expected_head = (Node*)malloc(sizeof(Node));
    strcpy(expected_head->last_name, "Kuznetsov");
    strcpy(expected_head->first_name, "Anatoly");
    strcpy(expected_head->middle_name, "Ivanovich");
    expected_head->date.day = 01;
    expected_head->date.month = 02;
    expected_head->date.year = 2007;

    Node* expected_middle = (Node*)malloc(sizeof(Node));
    strcpy(expected_middle->last_name, "Petrov");
    strcpy(expected_middle->first_name, "Sergey");
    strcpy(expected_middle->middle_name, "Vladimirovich");
    expected_middle->date.day = 15;
    expected_middle->date.month = 01;
    expected_middle->date.year = 2006;

    Node* expected_tail = (Node*)malloc(sizeof(Node));
    strcpy(expected_tail->last_name, "Morozov");
    strcpy(expected_tail->first_name, "Viktor");
    strcpy(expected_tail->middle_name, "Alekseevich");
    expected_tail->date.day = 03;
    expected_tail->date.month = 04;
    expected_tail->date.year = 2008;

    expected_head->next = expected_middle;
    expected_middle->next = expected_tail;
    expected_tail->next = NULL;

    EXPECT_TRUE(compare_nodes(head, expected_head));

    free(new_node);
    free(head);
    free(second_node);
    free(expected_head);
    free(expected_middle);
    free(expected_tail);
}

TEST(_insert_sorted, AddDuplicate) {
    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->last_name, "Kuznetsov");
    strcpy(head->first_name, "Anatoly");
    strcpy(head->middle_name, "Ivanovich");
    head->date.day = 01;
    head->date.month = 02;
    head->date.year = 2007;

    head->next = NULL;

    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->last_name, "Kuznetsov");
    strcpy(new_node->first_name, "Anatoly");
    strcpy(new_node->middle_name, "Ivanovich");
    new_node->date.day = 01;
    new_node->date.month = 02;
    new_node->date.year = 2007;

    head = insert_sorted(head, new_node);

    Node* expected_head = (Node*)malloc(sizeof(Node));
    strcpy(expected_head->last_name, "Kuznetsov");
    strcpy(expected_head->first_name, "Anatoly");
    strcpy(expected_head->middle_name, "Ivanovich");
    expected_head->date.day = 01;
    expected_head->date.month = 02;
    expected_head->date.year = 2007;

    expected_head->next = NULL;

    EXPECT_TRUE(compare_nodes(head, expected_head));

    free(new_node);
    free(expected_head);
}

TEST(_insert_sorted, AddSameDates) {
    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->last_name, "Kuznetsov");
    strcpy(head->first_name, "Anatoly");
    strcpy(head->middle_name, "Ivanovich");
    head->date.day = 01;
    head->date.month = 02;
    head->date.year = 2007;

    Node* second_node = (Node*)malloc(sizeof(Node));
    strcpy(second_node->last_name, "Morozov");
    strcpy(second_node->first_name, "Viktor");
    strcpy(second_node->middle_name, "Alekseevich");
    second_node->date.day = 01;
    second_node->date.month = 02;
    second_node->date.year = 2007;

    head->next = second_node;
    second_node->next = NULL;

    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->last_name, "Petrov");
    strcpy(new_node->first_name, "Sergey");
    strcpy(new_node->middle_name, "Vladimirovich");
    new_node->date.day = 01;
    new_node->date.month = 02;
    new_node->date.year = 2007;

    head = insert_sorted(head, new_node);

    Node* expected_head = (Node*)malloc(sizeof(Node));
    strcpy(expected_head->last_name, "Kuznetsov");
    strcpy(expected_head->first_name, "Anatoly");
    strcpy(expected_head->middle_name, "Ivanovich");
    expected_head->date.day = 01;
    expected_head->date.month = 02;
    expected_head->date.year = 2007;

    Node* expected_middle = (Node*)malloc(sizeof(Node));
    strcpy(expected_middle->last_name, "Morozov");
    strcpy(expected_middle->first_name, "Viktor");
    strcpy(expected_middle->middle_name, "Alekseevich");
    expected_middle->date.day = 01;
    expected_middle->date.month = 02;
    expected_middle->date.year = 2007;

    Node* expected_tail = (Node*)malloc(sizeof(Node));
    strcpy(expected_tail->last_name, "Petrov");
    strcpy(expected_tail->first_name, "Sergey");
    strcpy(expected_tail->middle_name, "Vladimirovich");
    expected_tail->date.day = 01;
    expected_tail->date.month = 02;
    expected_tail->date.year = 2007;

    expected_head->next = expected_middle;
    expected_middle->next = expected_tail;
    expected_tail->next = NULL;

    EXPECT_TRUE(compare_nodes(head, expected_head));

    free(new_node);
    free(expected_head);
    free(expected_middle);
    free(expected_tail);
}

TEST(_insert_sorted, AddReverseOrder) {
    Node* head = (Node*)malloc(sizeof(Node));
    strcpy(head->last_name, "Petrov");
    strcpy(head->first_name, "Sergey");
    strcpy(head->middle_name, "Vladimirovich");
    head->date.day = 15;
    head->date.month = 01;
    head->date.year = 2016;

    head->next = NULL;

    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->last_name, "Kuznetsov");
    strcpy(new_node->first_name, "Anatoly");
    strcpy(new_node->middle_name, "Ivanovich");
    new_node->date.day = 01;
    new_node->date.month = 02;
    new_node->date.year = 2007;

    head = insert_sorted(head, new_node);

    new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->last_name, "Sidorov");
    strcpy(new_node->first_name, "Pavel");
    strcpy(new_node->middle_name, "Pavlovich");
    new_node->date.day = 10;
    new_node->date.month = 10;
    new_node->date.year = 2016;

    head = insert_sorted(head, new_node);

    Node* expected_head = (Node*)malloc(sizeof(Node));
    strcpy(expected_head->last_name, "Kuznetsov");
    strcpy(expected_head->first_name, "Anatoly");
    strcpy(expected_head->middle_name, "Ivanovich");
    expected_head->date.day = 01;
    expected_head->date.month = 02;
    expected_head->date.year = 2007;

    Node* expected_middle = (Node*)malloc(sizeof(Node));
    strcpy(expected_middle->last_name, "Petrov");
    strcpy(expected_middle->first_name, "Sergey");
    strcpy(expected_middle->middle_name, "Vladimirovich");
    expected_middle->date.day = 15;
    expected_middle->date.month = 01;
    expected_middle->date.year = 2016;

    Node* expected_tail = (Node*)malloc(sizeof(Node));
    strcpy(expected_tail->last_name, "Sidorov");
    strcpy(expected_tail->first_name, "Pavel");
    strcpy(expected_tail->middle_name, "Pavlovich");
    expected_tail->date.day = 10;
    expected_tail->date.month = 10;
    expected_tail->date.year = 2016;

    expected_head->next = expected_middle;
    expected_middle->next = expected_tail;
    expected_tail->next = NULL;

    EXPECT_TRUE(compare_nodes(head, expected_head));

    free(new_node);
    free(expected_head);
    free(expected_middle);
    free(expected_tail);
}

TEST(_parse_, InvalidFormat) {
    char* line = "Petrov Sergey Vladimirovich 15.01.2016a";
    Node* new_node = parse_line(line);
    EXPECT_EQ(new_node, nullptr);
}

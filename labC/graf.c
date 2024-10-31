#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define BUFFER_SIZE 256

typedef struct node {
    char* data;
    struct node* prev;
    struct node* next;
} Node;

bool append(Node** head, const char* str) {
    if (str != NULL) {
        if (*head == NULL) {
            Node* new_node = malloc(sizeof(Node));
            if (!new_node) {
                perror("Memory allocation error for the node");
                exit(EXIT_FAILURE);
            }

            new_node->data = _strdup(str);
            if (!new_node->data) {
                free(new_node);
                perror("Line copying error");
                exit(EXIT_FAILURE);
            }

            new_node->prev = NULL;
            new_node->next = NULL;
            *head = new_node;
            return;
        }

        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }

        Node* new_node = malloc(sizeof(Node));
        if (!new_node) {
            perror("Memory allocation error for the node");
            exit(EXIT_FAILURE);
        }

        new_node->data = _strdup(str);
        if (!new_node->data) {
            free(new_node);
            perror("Line copying error");
            exit(EXIT_FAILURE);
        }

        new_node->prev = current;
        new_node->next = NULL;
        current->next = new_node;
        return true;
    }
    else{
        return false;
    }
}

bool eq(Node* headL, Node* headM, bool b, int lenL, int lenM) {
    if (lenL != lenM) {
        return false;
    }
    if (b) {
        Node* currentL = headL;
        Node* currentM = headM;
        while (currentL->next != NULL) {
            int current = 1;
            char* L = currentL->data;
            char* M = currentM->data;
            char* contextL = NULL;
            char* contextM = NULL;
            char* tokenL = NULL;
            char* tokenM = NULL;
            tokenL = strtok_s(L, " ", &contextL);
            tokenM = strtok_s(M, " ", &contextM);
            while (true) {
                if (tokenL != NULL) {
                    if (tokenM != NULL) {
                        if (atoi(tokenM) == 0) {
                            if (atoi(tokenL) == current) {
                                return false;
                            }
                            else {
                                tokenM = strtok_s(NULL, " ", &contextM);
                                current++;
                            }
                        }
                        else {
                            if (atoi(tokenL) != current) {
                                return false;
                            }
                            else {
                                tokenL = strtok_s(NULL, " ", &contextL);
                                tokenM = strtok_s(NULL, " ", &contextM);
                                current++;
                            }
                        }
                    }
                    else{
                        return false;
                    }
                }
                else if((tokenM != NULL)){
                    if (atoi(tokenM) == 1){
                        return false;
                    }
                    tokenM = strtok_s(NULL, " ", &contextM);
                }
                else{
                    break;
                }
            }
            currentM = currentM->next;
            currentL = currentL->next;
        }
        return true;
    }
    else {
        return true;
    }
}

int main() {
    Node* headList = NULL;
    Node* headMatrix = NULL;
    int Matrixlen = 0;
    int Listlen = 0;
    FILE* FileList = fopen("TextFile1.txt", "r");
    if (!FileList) {
        perror("Error opening the input file");
        return EXIT_FAILURE;
    }

    FILE* FileMatrix = fopen("TextFile2.txt", "r");
    if (!FileMatrix) {
        perror("Error opening the output file");
        return EXIT_FAILURE;
    }

    char bufferList[BUFFER_SIZE];

    while (fgets(bufferList, sizeof(bufferList), FileList)) {
        Listlen++;
        size_t len = strlen(bufferList);
        if (len > 0 && bufferList[len - 1] == '\n') {
            bufferList[len - 1] = '\0';
        }
        append(&headList, bufferList);
    }

    char bufferMatrix[BUFFER_SIZE];

    while (fgets(bufferMatrix, sizeof(bufferMatrix), FileMatrix)) {
        Matrixlen++;
        size_t len = strlen(bufferMatrix);
        if (len > 0 && bufferMatrix[len - 1] == '\n') {
            bufferMatrix[len - 1] = '\0';
        }
        append(&headMatrix, bufferMatrix);
    }
    append(&headList, "stop");
    append(&headMatrix, "stop");
    fclose(FileList);
    fclose(FileMatrix);
    bool t = eq(headList, headMatrix, !((Listlen == Matrixlen) && (Matrixlen == 0)), Listlen, Matrixlen);
    if (t) {
        printf("graphs are isomorphic");
    }
    else {
        printf("graphs are not isomorphic");
    }

    while (headList != NULL) {
        Node* temp = headList;
        headList = headList->next;
        free(temp->data);
        free(temp);
    }

    while (headMatrix != NULL) {
        Node* temp = headMatrix;
        headMatrix = headMatrix->next;
        free(temp->data);
        free(temp);
    }
    //Unit tests
    test_append_empty_list(); //проверка добавления в пустой список
    test_append_nonempty_list(); //проверка добавления в непустой список
    test_append_null(); //проверка добавления null в список
    test_eq_null_list(); //проверка при пустом списке
    test_eq_null_matrix(); //проверка при пустой матрице
    test_eq_null(); //проверка при пустой матрице и пустом списке
    test_eq_true(); //проверка, когда графы равны
    test_eq_false();//проверка, когда графы не равны
    test_eq_List_morethen_Matrix(); //проверка, когда в графе, заданном списком, больше вершин, чем в графе, заданном матрицей
    test_eq_Matrix_morethen_List(); //проверка, когда в графе, заданном матрицей, больше вершин, чем в графе, заданном списком
    return 0;
}
//Unit tests

int test_append_empty_list() {
    Node* head1 = NULL;
    assert(append(&head1, "A")&&(strcmp(head1->data, "A") == 0) && (head1->prev == NULL) && (head1->next == NULL));
}
int test_append_nonempty_list() {
    Node* head2 = NULL;
    assert(append(&head2, "A")&& append(&head2, "B") &&(strcmp(head2->next->data, "B") == 0) && (head2->next->prev == head2) && (head2->next->next == NULL));
}
int test_append_null() {
    Node* head3 = NULL;
    assert(!append(&head3, NULL));
}
int test_eq_null() {
    Node a = { NULL, NULL,NULL };
    Node* A = &a;
    Node a1 = { NULL, NULL,NULL };
    Node* A1 = &a1;
    assert(eq(A, A1, false, 0, 0));
}
int test_eq_null_list() {
    Node a = { NULL, NULL,NULL };
    Node* A = &a;
    Node a1 = { "0", NULL,NULL };
    Node* A1 = &a1;
    assert(eq(A, A1, false, 0, 0));
}
int test_eq_null_matrix() {
    Node a = { "", NULL,NULL};
    Node* A = &a;
    Node a1 = { NULL, NULL,NULL };
    Node* A1 = &a1;
    assert(eq(A, A1, false, 0, 0));
}
int test_eq_true() {
    Node a = { "1", NULL,NULL };
    Node* A = &a;
    Node a1 = { "1", NULL,NULL };
    Node* A1 = &a1;
    assert(eq(A, A1, true, 1, 1));
}
int test_eq_false() {
    Node a = { "1", NULL,NULL };
    Node* A = &a;
    Node a1 = { "0", NULL,NULL };
    Node* A1 = &a1;
    assert(eq(A, A1, true, 1, 1));
}
int test_eq_List_morethen_Matrix() {
    Node a = { "1 1", NULL,NULL };
    Node b = { "1 1", &a,NULL };
    a.next = &b;
    Node* A = &a;
    Node a1 = { "1", NULL,NULL };
    Node* A1 = &a1;
    assert(!(eq(A, A1, true, 2, 1)));
}
int test_eq_Matrix_morethen_List() {
    Node a = { "1", NULL,NULL };
    Node* A = &a;
    Node a1 = { "1 1", NULL,NULL };
    Node b1 = { "1 1", &a1,NULL };
    a1.next = &b1;
    Node* A1 = &a1;
    assert(!(eq(A, A1, true, 1, 2)));
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define BUFFER_SIZE 256

typedef struct oaoa {
    char* data;
    struct oaoa* prev;
    struct oaoa* next;
} oaoa;

bool append(oaoa** head, const char* str) {
    if (str != NULL) {
        if (*head == NULL) {
            oaoa* newn = malloc(sizeof(oaoa));
            if (!newn) {
                perror("Memory allocation error for the node");
                exit(EXIT_FAILURE);
            }

            newn->data = _strdup(str);
            if (!newn->data) {
                free(newn);
                perror("Line copying error");
                exit(EXIT_FAILURE);
            }

            newn->prev = NULL;
            newn->next = NULL;
            *head = newn;
            return;
        }

        oaoa* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }

        oaoa* newn = malloc(sizeof(oaoa));
        if (!newn) {
            perror("Memory allocation error for the node");
            exit(EXIT_FAILURE);
        }

        newn->data = _strdup(str);
        if (!newn->data) {
            free(newn);
            perror("Line copying error");
            exit(EXIT_FAILURE);
        }

        newn->prev = current;
        newn->next = NULL;
        current->next = newn;
        return true;
    }
    else{
        return false;
    }
}

bool eq(oaoa* headL, oaoa* headM, bool b, int lenL, int lenM) {
    if (lenL != lenM) {
        return false;
    }
    if (b) {
        oaoa* cl = headL;
        oaoa* cm = headM;
        while (cl->next != NULL) {
            int current = 1;
            char* L = cl->data;
            char* M = cm->data;
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
            cm = cm->next;
            cl = cl->next;
        }
        return true;
    }
    else {
        return true;
    }
}

int main() {
    oaoa* headList = NULL;
    oaoa* headMatrix = NULL;
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
        oaoa* temp = headList;
        headList = headList->next;
        free(temp->data);
        free(temp);
    }

    while (headMatrix != NULL) {
        oaoa* temp = headMatrix;
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
    oaoa* head1 = NULL;
    assert(append(&head1, "A")&&(strcmp(head1->data, "A") == 0) && (head1->prev == NULL) && (head1->next == NULL));
}
int test_append_nonempty_list() {
    oaoa* head2 = NULL;
    assert(append(&head2, "A")&& append(&head2, "B") &&(strcmp(head2->next->data, "B") == 0) && (head2->next->prev == head2) && (head2->next->next == NULL));
}
int test_append_null() {
    oaoa* head3 = NULL;
    assert(!append(&head3, NULL));
}
int test_eq_null() {
    oaoa a = { NULL, NULL,NULL };
    oaoa* A = &a;
    oaoa a1 = { NULL, NULL,NULL };
    oaoa* A1 = &a1;
    assert(eq(A, A1, false, 0, 0));
}
int test_eq_null_list() {
    oaoa a = { NULL, NULL,NULL };
    oaoa* A = &a;
    oaoa a1 = { "0", NULL,NULL };
    oaoa* A1 = &a1;
    assert(eq(A, A1, false, 0, 0));
}
int test_eq_null_matrix() {
    oaoa a = { "", NULL,NULL};
    oaoa* A = &a;
    oaoa a1 = { NULL, NULL,NULL };
    oaoa* A1 = &a1;
    assert(eq(A, A1, false, 0, 0));
}
int test_eq_true() {
    oaoa a = { "1", NULL,NULL };
    oaoa* A = &a;
    oaoa a1 = { "1", NULL,NULL };
    oaoa* A1 = &a1;
    assert(eq(A, A1, true, 1, 1));
}
int test_eq_false() {
    oaoa a = { "1", NULL,NULL };
    oaoa* A = &a;
    oaoa a1 = { "0", NULL,NULL };
    oaoa* A1 = &a1;
    assert(eq(A, A1, true, 1, 1));
}
int test_eq_List_morethen_Matrix() {
    oaoa a = { "1 1", NULL,NULL };
    oaoa b = { "1 1", &a,NULL };
    a.next = &b;
    oaoa* A = &a;
    oaoa a1 = { "1", NULL,NULL };
    oaoa* A1 = &a1;
    assert(!(eq(A, A1, true, 2, 1)));
}
int test_eq_Matrix_morethen_List() {
    oaoa a = { "1", NULL,NULL };
    oaoa* A = &a;
    oaoa a1 = { "1 1", NULL,NULL };
    oaoa b1 = { "1 1", &a1,NULL };
    a1.next = &b1;
    oaoa* A1 = &a1;
    assert(!(eq(A, A1, true, 1, 2)));
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#define BUFFER_SIZE 1000

typedef struct vertex {
    int st;
    struct vertex* prev;
    struct vertex* next;
} Vertexx;
typedef struct graf {
    char* data;
    struct graf* prev;
    struct graf* next;
} Graff;


bool appendG(Graff** head, const char* str) {
    if (str != NULL) {
        if (*head == NULL) {
            Graff* new_node = malloc(sizeof(Graff));
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

        Graff* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }

        Graff* new_node = malloc(sizeof(Graff));
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
    else {
        return false;
    }
}

void appendV(Vertexx** head, int value) {
    Vertexx* new_node = (Vertexx*)malloc(sizeof(Vertexx));
    new_node->st = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Vertexx* last = *head;
    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;
}

bool checkadjacentvertex(Graff* Graf1, int vc, int vf) {
    Graff* current = Graf1;
    for (int i = 0; i < vc + 1; i++) {
        current = current->next;
    }
    bool p = false;
    char* E = _strdup(current->data);
        char* context = NULL;
        char* token = NULL;
        token = strtok_s(E, " ", &context);
        while (token != NULL) {
            if (atoi(token) == vf + 1) {
                p = true;
                break;
            }
            token = strtok_s(NULL, " ", &context);
        }
        return p;
}
bool cover(Graff* Graf, Vertexx* Vertex, int K, int N) {
    int* st;
    int max = 0;
    int maxi = -1;
    st = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        st[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (checkadjacentvertex(Graf, i, j)) {
                st[i] = st[i] + 1;
            }
            if (st[i] > max) {
                max = st[i];
            }
        }
    }
    if (max == 0) {
        return true;
    }
    bool b = false;
    for (int k = 0; k < K; k++) {
        max = 0;
        maxi = -1;
        for (int i = 0; i < N; i++) {
            if (st[i] > max) {
                max = st[i];
                maxi = i;
            }
        }
        appendV(&Vertex, maxi + 1);
        st[maxi] = -1;
        for (int j = 0; j < N; j++) {
            if (maxi != j && checkadjacentvertex(Graf, maxi, j)) {
                st[j] = st[j] - 1;
            }
        }
        max = 0;
        for (int i = 0; i < N; i++) {
            if (st[i] > max) {
                max = st[i];
                maxi = i;
            }
        }
        if (max == 0) {
            b = true;
            return true;
        }
    }
    return b;
}

void printList1(Graff* head) {
    Graff* current = head;
    while (current != NULL) {
        char* E = _strdup(current->data);
        char* context = NULL;
        char* token = NULL;
        token = strtok_s(E, " ", &context);
        while (token != NULL) {
            printf("Value: %d \n", atoi(token));
            token = strtok_s(NULL, " ", &context);
        }
        current = current->next;
    }
}

int main() {
    int N, K;
    Graff* Graph = NULL;
    Vertexx* Vertex = NULL;
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening the input file");
        return EXIT_FAILURE;
    }

    fscanf_s(file, "%d %d", &N, &K);
    char bufferList[BUFFER_SIZE];
    while (fgets(bufferList, sizeof(bufferList), file)) {
        size_t len = strlen(bufferList);
        if (len > 0 && bufferList[len - 1] == '\n') {
            bufferList[len - 1] = '\0';
        }
        appendG(&Graph, bufferList);
    }
    fclose(file);
    appendV(&Vertex, -1);
    bool res = cover(Graph, Vertex, K, N);
    FILE* fileo = fopen("output.txt", "w");
    if (!fileo) {
        perror("Error opening the output file");
        return EXIT_FAILURE;
    }
    if (res) {
        Vertexx* current = Vertex->next;
        while (current != NULL) {
            fprintf(fileo, "%d\n", current->st);
            current = current->next;
        }
    }
    else {
         fprintf(fileo, "%d\n", 0);
    }
    fclose(fileo);
    while (Graph != NULL) {
        Graff* temp = Graph;
        Graph = Graph->next;
        free(temp->data);
        free(temp);
    }
    Vertexx* current = Vertex;
    Vertexx* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    //Тесты
    test_appendV_empty_list(); 
    test_appendV_nonempty_list(); 
    test_appendG_empty_list(); 
    test_appendG_nonempty_list(); 
    test_appendG_null(); 
    test_checkadjacentvertex_true(); 
    test_checkadjacentvertex_false(); 
    test_cover_true(); 
    test_cover_false(); 
    test_cover_one_element_graph(); 
    return 0;
}
//Unit tests
int test_appendV_empty_list() {
    Vertexx* head1 = NULL;
    appendV(&head1, 1);
    assert((head1->st == 1) && (head1->prev == NULL) && (head1->next == NULL));
}
int test_appendV_nonempty_list() {
    Vertexx* head2 = NULL;
    appendV(&head2, 1);
    appendV(&head2, 1);
    assert((head2->next->st == 1) && (head2->next->prev == head2) && (head2->next->next == NULL));
}
int test_appendG_empty_list() {
    Graff* head1 = NULL;
    assert(appendG(&head1, "A") && (strcmp(head1->data, "A") == 0) && (head1->prev == NULL) && (head1->next == NULL));
}
int test_appendG_nonempty_list() {
    Graff* head2 = NULL;
    assert(appendG(&head2, "A") && appendG(&head2, "B") && (strcmp(head2->next->data, "B") == 0) && (head2->next->prev == head2) && (head2->next->next == NULL));
}
int test_appendG_null() {
    Graff* head3 = NULL;
    assert(!appendG(&head3, NULL));
}
int test_checkadjacentvertex_true() {
    Graff a = { "1", NULL,NULL };
    Graff b = { "1", &a,NULL };
    a.next = &b;
    Graff* A = &a;
    assert(checkadjacentvertex(A,0,0));
}
int test_checkadjacentvertex_false() {
    Graff a1 = { "", NULL,NULL };
    Graff b1 = { "1", &a1,NULL };
    a1.next = &b1;
    Graff* A = &a1;
    assert(!checkadjacentvertex(A, 0, 1));
}
int test_cover_true() {
    Vertexx V = { -1, NULL,NULL };
    Graff a1 = { "0", NULL,NULL };
    Graff b1 = { "2", &a1,NULL };
    Graff c1 = { "1", &b1,NULL };
    a1.next = &b1;
    b1.next = &c1;
    Graff* A = &a1;
    Vertexx* Vt = &V;
    cover(A, Vt, 1, 2);
    assert(Vt->next->st==1);
}
int test_cover_false() {
    Vertexx V = { -1, NULL,NULL };
    Graff a1 = { "0", NULL,NULL };
    Graff b1 = { "2 3", &a1,NULL };
    Graff c1 = { "1 3", &b1,NULL };
    Graff d1 = { "1 2", &c1,NULL };
    a1.next = &b1;
    b1.next = &c1;
    c1.next = &d1;
    Graff* A = &a1;
    Vertexx* Vt = &V;
    assert(!cover(A, Vt, 1, 3));
}
int test_cover_one_element_graph() {
    Vertexx V = { -1, NULL,NULL };
    Graff a1 = { "0", NULL,NULL };
    Graff b1 = { "1", &a1,NULL };
    a1.next = &b1;
    Graff* A = &a1;
    Vertexx* Vt = &V;
    cover(A, Vt, 1, 1);
    assert(Vt->next->st == 1);
}

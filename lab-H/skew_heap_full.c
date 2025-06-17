/*  skew_heap_full.c
 *  ──────────────────────────────────────────────────────────────
 *  Скошенная куча (skew-heap) + 10 юнит-тестов в одном файле.
 *  ▸ Обычная сборка           :  gcc -std=c11 -Wall -Wextra -O2 skew_heap_full.c -o outDebug
 *  ▸ Сборка юнит-тестов       :  gcc -std=c11 -Wall -Wextra -O2 -DTEST skew_heap_full.c -o test_runner
 *  ▸ Makefile (см. репозиторий) автоматизирует и то и другое, + цель run.
 *  ──────────────────────────────────────────────────────────────*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* ──────────────────────────────────────────────────────────────
   Реализация скошенной кучи
   ──────────────────────────────────────────────────────────────*/
typedef struct Node {
    int           key;
    struct Node  *left, *right;
} Node;

static Node* createNode(int key) {
    Node *n = malloc(sizeof(Node));
    if (!n) { perror("malloc"); exit(EXIT_FAILURE); }
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

static Node* merge(Node *h1, Node *h2) {
    if (!h1) return h2;
    if (!h2) return h1;
    if (h1->key > h2->key) { Node *t = h1; h1 = h2; h2 = t; }
    Node *tmp  = h1->left;
    h1->left   = merge(h1->right, h2);
    h1->right  = tmp;
    return h1;
}

static Node* insertNode(Node *root, int key)     { return merge(root, createNode(key)); }
static Node* deleteMin (Node *root) {
    if (!root) return NULL;
    Node *l = root->left, *r = root->right;
    free(root);
    return merge(l, r);
}
static Node* searchNode(Node *root, int key) {
    if (!root) return NULL;
    if (root->key == key) return root;
    Node *f = searchNode(root->left, key);
    return f ? f : searchNode(root->right, key);
}

/* ──────────────────────────────────────────────────────────────
   Блок юнит-тестов (компилируется при -DTEST)
   ──────────────────────────────────────────────────────────────*/
#ifdef TEST

static int cmp_arr(const int *a, const int *b, int n) {
    for (int i = 0; i < n; ++i) if (a[i] != b[i]) return 0;
    return 1;
}

/* 1 */  void merge_TwoSingleNodes_MinAtRoot_no1(void) {
            Node *h1 = createNode(10), *h2 = createNode(5);
            assert(merge(h1,h2)->key == 5);
        }
/* 2 */  void merge_EmptyAndNode_ReturnOther_no2(void) {
            Node *h = createNode(7);  assert(merge(NULL,h) == h);
        }
/* 3 */  void merge_BothEmpty_ReturnNull_no3(void) { assert(merge(NULL,NULL)==NULL); }
/* 4 */  void insert_EmptyHeap_ReturnValidVal_no4(void) {
            Node *h = insertNode(NULL,42);  assert(searchNode(h,42)!=NULL);
        }
/* 5 */  void insert_MultipleKeys_MinAtRoot_no5(void) {
            Node *h=NULL; h=insertNode(h,8); h=insertNode(h,3); h=insertNode(h,5);
            assert(h->key==3);
        }
/* 6 */  void deleteMin_SingleElement_ReturnNull_no6(void) {
            Node *h=createNode(99); assert(deleteMin(h)==NULL);
        }
/* 7 */  void deleteMin_MultipleElements_NextMinAtRoot_no7(void) {
            Node *h=NULL; h=insertNode(h,2); h=insertNode(h,5); h=insertNode(h,3);
            h=deleteMin(h);  assert(h->key==3);
        }
/* 8 */  void search_ExistingKey_ReturnValidVal_no8(void) {
            Node *h=NULL; h=insertNode(h,15); h=insertNode(h,10);
            assert(searchNode(h,15)!=NULL);
        }
/* 9 */  void search_NonExistingKey_ReturnNull_no9(void) {
            Node *h=insertNode(NULL,1);  assert(searchNode(h,2)==NULL);
        }
/*10 */  void deleteMin_SequentialDeletes_SortedSequence_no10(void) {
            int exp[4]={1,2,3,4}, res[4];
            Node *h=NULL; h=insertNode(h,4); h=insertNode(h,1);
            h=insertNode(h,3); h=insertNode(h,2);
            for(int i=0;i<4;++i){ res[i]=h->key; h=deleteMin(h); }
            assert(cmp_arr(res,exp,4));
        }

int main(void) {
    merge_TwoSingleNodes_MinAtRoot_no1();
    merge_EmptyAndNode_ReturnOther_no2();
    merge_BothEmpty_ReturnNull_no3();
    insert_EmptyHeap_ReturnValidVal_no4();
    insert_MultipleKeys_MinAtRoot_no5();
    deleteMin_SingleElement_ReturnNull_no6();
    deleteMin_MultipleElements_NextMinAtRoot_no7();
    search_ExistingKey_ReturnValidVal_no8();
    search_NonExistingKey_ReturnNull_no9();
    deleteMin_SequentialDeletes_SortedSequence_no10();
    printf("All tests passed.\n");
    return 0;
}

#else /* ────────────────────── обычная программа ───────────────────── */

/* префиксный вывод в файл */
static void printPreorderFile(Node *root, FILE *out){
    if(!root) return;
    fprintf(out,"%d ",root->key);
    printPreorderFile(root->left ,out);
    printPreorderFile(root->right,out);
}

int main(int argc,char *argv[]){
    FILE *in = stdin ,*out = stdout;
    if(argc>=2){ in=fopen(argv[1],"r"); if(!in){perror("fopen");return 1;} }
    if(argc>=3){ out=fopen(argv[2],"w"); if(!out){perror("fopen");return 1;} }

    Node *heap = NULL;
    char cmd[32];
    int  x;
    while(fscanf(in,"%31s",cmd)==1){
        if     (!strcmp(cmd,"insert")){
            if(fscanf(in,"%d",&x)==1) heap = insertNode(heap,x);
        }
        else if(!strcmp(cmd,"deleteMin")){
            heap = deleteMin(heap);
        }
        else if(!strcmp(cmd,"search")){
            if(fscanf(in,"%d",&x)==1)
                fprintf(out,"%s\n", searchNode(heap,x)?"found":"not found");
        }
        else if(!strcmp(cmd,"print")){
            printPreorderFile(heap,out);
            fprintf(out,"\n");
        }
        else if(!strcmp(cmd,"exit")){
            break;
        }
    }

    if(in!=stdin)  fclose(in);
    if(out!=stdout)fclose(out);
    while(heap) heap = deleteMin(heap);
    return 0;
}
#endif

///#ifndef TREAP_H
//#define TREAP_H

typedef struct TreapNode {
    int x;
    int c;
    int priority;
    int sum;
    struct TreapNode *left, *right;
} TreapNode;

void update_sum(TreapNode* node);
void split(TreapNode* root, int key, TreapNode** left, TreapNode** right);
TreapNode* merge(TreapNode* a, TreapNode* b);
void insert(TreapNode** root, int x, int c);
int sum_range(TreapNode** root, int x_start, int x_end);
void free_treap(TreapNode* root);

//#endif // TREAP_H
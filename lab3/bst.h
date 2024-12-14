typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int count;
} Node;

Node* newNode(int data);
Node* insert(Node* root, int data);
int kthSmallest(Node* root, int K, int* count);
void printElementsLessThanK(Node* root, int K);
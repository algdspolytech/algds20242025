#define RED 0
#define BLACK 1

typedef struct Node {
    int data;
    int color;
    struct Node* left, * right, * parent;
} Node;

typedef struct RBTree {
    Node* root;
    Node* TNULL; // ������� (��������) ����
} RBTree;

Node* makeNode(int data);                         // ������� ��� �������� ������ ����
RBTree* createTree();                             // ������� ��� �������� ������
void rotateRight(RBTree* tree, Node* x);
void rotateLeft(RBTree* tree, Node* x);            // ����� � ������ �������� (��� ������������)
void balanceAfterAdd(RBTree* tree, Node* k);              // ������� ��� ������������ ������ ����� �������
void addNode(RBTree* tree, int key);                 // ������� ��� ������� ������ ��������
Node* findNode(RBTree* tree, int key);                // ������� ��� ������ ��������
void balanceAfterDelete(RBTree* tree, Node* x);              // ��������������� ������ ����� �������� ����
void removeNode(RBTree* tree, Node* z);             // ������� ��� �������� ����
void transplant(RBTree* tree, Node* u, Node* v);  // ������� �������������� ��� ��������
Node* getMinimum(Node* node);                          // ����� ������������ ���� � ���������
void displayTree(Node* node, Node* TNULL, int space); // ������� ��� ������ ������
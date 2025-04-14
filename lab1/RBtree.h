#define RED 0
#define BLACK 1

typedef struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
} Node;

typedef struct RBTree {
    Node *root;
    Node *TNULL; // Нулевой (листовой) узел
} RBTree;

Node* createNode(int data);                         // Функция для создания нового узла
RBTree* createRBTree();                             // Функция для создания дерева
void rightRotate(RBTree *tree, Node *x);            // Левый и правый повороты (для балансировки)
void fixInsert(RBTree *tree, Node *k);              // Функция для балансировки дерева после вставки
void insert(RBTree *tree, int key);                 // Функция для вставки нового элемента
Node* search(RBTree *tree, int key);                // Функция для поиска элемента
void fixDelete(RBTree *tree, Node *x);              // Восстанавливает баланс после удаления узла
void deleteNode(RBTree *tree, Node *z);             // Функция для удаления узла
void rbTransplant(RBTree *tree, Node *u, Node *v);  // Функция трансплантации для удаления
Node* treeMin(Node *node);                          // Поиск минимального узла в поддереве
void printTree(Node *node, Node *TNULL, int space); // Функция для печати дерева
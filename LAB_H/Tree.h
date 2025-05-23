#define RED 0
#define BLACK 1

typedef struct Node {
    int data;
    int color;
    struct Node* left, * right, * parent;
} Node;

typedef struct RBTree {
    Node* root;
    Node* TNULL; // Нулевой (листовой) узел
} RBTree;

Node* makeNode(int data);                         // Функция для создания нового узла
RBTree* createTree();                             // Функция для создания дерева
void rotateRight(RBTree* tree, Node* x);
void rotateLeft(RBTree* tree, Node* x);            // Левый и правый повороты (для балансировки)
void balanceAfterAdd(RBTree* tree, Node* k);              // Функция для балансировки дерева после вставки
void addNode(RBTree* tree, int key);                 // Функция для вставки нового элемента
Node* findNode(RBTree* tree, int key);                // Функция для поиска элемента
void balanceAfterDelete(RBTree* tree, Node* x);              // Восстанавливает баланс после удаления узла
void removeNode(RBTree* tree, Node* z);             // Функция для удаления узла
void transplant(RBTree* tree, Node* u, Node* v);  // Функция трансплантации для удаления
Node* getMinimum(Node* node);                          // Поиск минимального узла в поддереве
void displayTree(Node* node, Node* TNULL, int space); // Функция для печати дерева
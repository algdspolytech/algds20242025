
// Структура для представления узла декартового дерева
struct Node {
    int x, c, priority, size;  // x - ключ, c - значение, priority - приоритет для дерева кучи, size - размер поддерева
    struct Node* left;
    struct Node* right;
};

// Функция для получения размера поддерева
int get_size(struct Node* node);

// Функция для обновления размера поддерева
void update_size(struct Node* node);

// Функция для создания нового узла
struct Node* new_node(int x, int c);

// Функция для выполнения поворота вправо
struct Node* rotate_right(struct Node* node);

// Функция для выполнения поворота влево
struct Node* rotate_left(struct Node* node);

// Функция для вставки узла в декартово дерево
struct Node* insert(struct Node* root, int x, int c);

// Функция для поиска максимума на интервале [x, y)
int find_max(struct Node* root, int x, int y);



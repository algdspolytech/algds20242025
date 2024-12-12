typedef struct Node {
    int value;
    int subtree_size;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int value, Node* parent);
void update_subtree_size(Node* node);
void add_node(Node** root, int value);
Node* find_minimum(Node* node);
void delete_node(Node** root, int value);
void inorder_traversal(Node* node);
void free_tree(Node* node);

void create_node_withPositiveValue_returnValidVal();
void create_node_withNegativeValue_returnValidVal();
void create_node_withNullParent_returnValidVal();

void add_node_toEmptyTree_returnValidVal();
void add_node_toTreeWithMultipleNodes_returnValidVal();
void add_node_toTreeWithDuplicateValues_returnValidVal();

void delete_node_withLeaf_returnTrue();
void delete_node_withRootAndSingleChild_returnTrue();
void delete_node_withTwoChildren_returnTrue();

void inorder_traversal_withEmptyTree_returnTrue();
void inorder_traversal_withSingleNode_returnValidVal();
void inorder_traversal_withMultipleNodes_returnValidVal();

// ��������� ��� ������������� ���� ����������� ������
struct Node {
    int x, c, priority, size;  // x - ����, c - ��������, priority - ��������� ��� ������ ����, size - ������ ���������
    struct Node* left;
    struct Node* right;
};

// ������� ��� ��������� ������� ���������
int get_size(struct Node* node);

// ������� ��� ���������� ������� ���������
void update_size(struct Node* node);

// ������� ��� �������� ������ ����
struct Node* new_node(int x, int c);

// ������� ��� ���������� �������� ������
struct Node* rotate_right(struct Node* node);

// ������� ��� ���������� �������� �����
struct Node* rotate_left(struct Node* node);

// ������� ��� ������� ���� � ��������� ������
struct Node* insert(struct Node* root, int x, int c);

// ������� ��� ������ ��������� �� ��������� [x, y)
int find_max(struct Node* root, int x, int y);



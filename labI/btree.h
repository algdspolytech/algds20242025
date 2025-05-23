#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define T 2
#define MIN_CHILDREN (T - 1)
#define MAX_KEYS (2 * T - 1)
#define MAX_CHILDREN (2 * T)

    /*
    ��������� ������ ����� � ������:
    MISSING - ������ ����� � ������ ���.
    EXISTS - ���� � ������ �����������.
    */
    typedef enum B_search_result
    {
        MISSING,
        EXISTS
    } B_search_result;

    /*
    ���� ������, ��� ��� ���������� �����, ��� � ��� �������.
    */
    typedef struct B_node
    {
        struct B_node* children[MAX_CHILDREN]; // ������ ���������� �� �������� ����
        int keys[MAX_KEYS]; // ������ ������, ����������� � ���� ����
        int keys_count; // ������� ���-�� ������, ������������ � ���� (�.�. � ������� keys)
        int is_leaf; // ���� - ���� ������, � �������� ��� �� ������ ��������� ����.
        struct B_node* parent; // ��������� �� ��������, ��� NULL ��� ����� ������
    } B_node;


    /*
    �������� ���������, ��� ������ � ����� ����������� ������
    */
    typedef struct B_tree
    {
        B_node* root; // ��������� �� �������� ���� ������
    } B_tree;


    /*
    ��������� ������ ��� ������ ���������� ��������� �� ������
    */
    typedef struct B_tree_iterator
    {
        // ��������� �� ����, �� ������� ������ ��������� ��������
        B_node* node;
        // ����� ����� ������ ����, �� ������� ������ ����� ��������
        int position;
    } B_tree_iterator;

    typedef void (*split_t)(B_node* node_to_split, int split_at_index);
    typedef void (*insertNotFull_t)(B_node* node, int data);

    /*
    �������� ���� � ������.
     ���� ���� ��� ���������� - ������ �� ������
    B_tree tree = {};
    Insert(&tree, 1);
    Insert(&tree, 1);
    Insert(&tree, 2);
    */
    void Insert(B_tree* tree, int data, split_t split_fn, insertNotFull_t insert_fn);

    // ���������� ���������� ��� ������ ������.
    void Free(B_tree* tree);

    /*
    ���������, ���� �� � ������ tree ���� data
    ������:
    B_tree tree = {};
    Insert(&tree, 7);
    Search(&tree, 7); ---> EXISTS
    Search(&tree, 5); ---> MISSING
    */
    B_search_result Search(B_tree* tree, int data);

    // ��������� � ���� �� ��������� ����������� ���� node  ���� data
    // ��. https://neerc.ifmo.ru/wiki/index.php?title=B-%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
    void insertNotFull(B_node* node, int data);

    // �������� �� ���� ������������� ���� parent_of_splited,
    // � �������� ���� ��������� ����������� �������� ���� �� ������� split_at_index.
    // ��������� ��������� ���� ��������� ����������� �������� ���� �� ���.
    // ��. https://neerc.ifmo.ru/wiki/index.php?title=B-%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE
    void split(B_node* parent_of_splited, int split_at_index);

    // ������� ����� �������� �� ������
    B_tree_iterator IteratorBegin(B_tree* tree);

    // ������������� �� ��������� ������� ��� ������������ ������
    // ���������� 1 ���� �������� ��� "���" � ����� �������� �������� ����� Key
    // ���������� 0, ���� ������������ ��������, ��� ���� ���� ��������, �������� ����� Key ��� �� ��������
    int Next(B_tree_iterator* iter);

    // �������� ����, �� ������� ������ ��������� ��������
    int Key(B_tree_iterator* iter);

    /*
    ������ ������������� ���������:
    B_tree_iterator iter = IteratorBegin(&tree);
    while (int has_element = Next(&iter))
    {
        printf("%d", Key(&iter));
    }
    */


    /*
    ����������������������������������������������������������
    ����������������������������������������������������������
    ���������                ��������!!              ���������
    ����������������������������������������������������������
    ����������������������������������������������������������
    ��� ������������ ������� ����������� �������� ������ ������ ��������� ����� �������:
    - split
    - insertNotFull
    ����������� ����, ������ �������, � ������ �� ����������:
    (*SplitFPtr)(node, 1)
    (*InsertNotFullPtr)(node, 1)
    ������:
    � ��� ���� ���-�� � ������� ���� �����:

      insertNotFull(node->children[key_ind], data);

    ��� �������� � ������� ��������, ��� ����� �������� ��� ��
      (*InsertNotFullPtr)(node->children[key_ind], data);
    */
    extern split_t const* SplitFPtr;
    extern insertNotFull_t const* InsertNotFullPtr;



#ifdef __cplusplus
}
#endif
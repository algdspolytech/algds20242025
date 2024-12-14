#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>


typedef struct TreeNode 
{
    char* value;        
    struct TreeNode* left;  
    struct TreeNode* right;
} TreeNode;


TreeNode* Create_Node(const char* value) 
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    if (!node) 
    {
        perror("Failed to allocate memory for TreeNode");
        exit(EXIT_FAILURE);
    }

    node->value = strdup(value); 
    node->left = NULL;
    node->right = NULL;
    return node;
}


const char* Skip_Spaces(const char* data) 
{
    while (isspace(*data)) {
        data++;
    }
    return data;
}

int Parse_Tree(const char** data_ptr, TreeNode** root) 
{
    const char* data = *data_ptr;
    data = Skip_Spaces(data);

    if (*data == '\0' || *data == ')') 
    {
        *data_ptr = data;
        return 0;
    }
    const char* start = data;

    while (*data != ' ' && *data != '(' && *data != ')' && *data != '\0') 
    {
        data++;
    }

    int length = data - start;
    char* value = (char*)malloc(length + 1);

    if (!value) 
    {
        perror("Failed to allocate memory for node value");
        exit(EXIT_FAILURE);
    }

    strncpy(value, start, length);

    value[length] = '\0';
    *root = Create_Node(value);

    free(value);  

    data = Skip_Spaces(data);

    if (*data == '(') 
    {
        data++;
        Parse_Tree(&data, &(*root)->left);
        data = Skip_Spaces(data);

        if (*data == ')') 
        {
            data++;  
        }
        data = Skip_Spaces(data);
        if (*data == '(') 
        {
            data++;  
            Parse_Tree(&data, &(*root)->right);
            data = Skip_Spaces(data);
            if (*data == ')') 
            {
                data++;
            }
        }
    }

    *data_ptr = data;  
    return 1;
}

void Print_Tree(TreeNode* root, int level) 
{
    if (root == NULL) 
    {
        return;
    }

    for (int i = 0; i < level; i++) 
    {
        printf("    ");
    }

    printf("%s\n", root->value);
    Print_Tree(root->left, level + 1);
    Print_Tree(root->right, level + 1);
}


void Free_Tree(TreeNode* root) 
{
    if (root == NULL) 
    {
        return;
    }

    free(root->value); 
    Free_Tree(root->left);
    Free_Tree(root->right);
    free(root);
}

void Collect_Tree(TreeNode* root, int level, char* buffer, size_t buffer_size) 
{
    if (root == NULL) 
    {
        return;
    }

    for (int i = 0; i < level; i++) 
    {
        strncat(buffer, "    ", buffer_size - strlen(buffer) - 1);
    }

    strncat(buffer, root->value, buffer_size - strlen(buffer) - 1);
    strncat(buffer, "\n", buffer_size - strlen(buffer) - 1);

    Collect_Tree(root->left, level + 1, buffer, buffer_size);
    Collect_Tree(root->right, level + 1, buffer, buffer_size);
}

void run_test(const char* test_name, const char* test_input, const char* expected_output) 
{
    printf(" %s \n", test_name);
    printf("test input: %s\n", test_input);

    TreeNode* root = NULL;

    const char* data_ptr = test_input;
    char result_buffer[1024] = ""; 

    if (Parse_Tree(&data_ptr, &root)) 
    {
        Collect_Tree(root, 0, result_buffer, sizeof(result_buffer));
    }
    else 
    {
        strncpy(result_buffer, "tree is empty\n", sizeof(result_buffer) - 1);
    }

    printf("result:\n%s", result_buffer);
    assert(strcmp(result_buffer, expected_output) == 0);

    Free_Tree(root);
    printf("test passed\n\n");
}


int main() 
{
    // проверка работы чтения из файла и отладка кода
    FILE* file = fopen("tree.txt", "r");

    if (file == NULL) 
    {
        perror("error with opening");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    fseek(file, 0, SEEK_SET);
    char* data = (char*)malloc(file_size + 1);

    if (!data) 
    {
        perror("Failed to allocate memory for data");
        fclose(file);
        return 1;
    }


    fread(data, 1, file_size, file);

    data[file_size] = '\0';
    fclose(file);

    TreeNode* root = NULL;
    const char* data_ptr = data;

    if (Parse_Tree(&data_ptr, &root)) 
    {
        Print_Tree(root, 0);
    }

    else 
    {
        printf("tree is empty\n");
    }

    Free_Tree(root);
    free(data);

    // тесты
    run_test("test 1. empty tree",
        " ",
        "tree is empty\n");

    run_test("test 2. tree with root without leaves",
        "root () ()",
        "root\n");

    run_test("test 3. tree with 2 leaves",
        "root (left () ()) (right () ())",
        "root\n"
        "    left\n"
        "    right\n");

    run_test("test 4. left-handed tree",
        "root (left (left.left () ()) ()) ()",
        "root\n"
        "    left\n"
        "        left.left\n");

    run_test("test 5. right-handed tree",
        "root () (right () (right.right () ()))",
        "root\n"
        "    right\n"
        "        right.right\n");

    run_test("test 6. full tree without skips in leaves",
        "root (left (left.left () ()) (left.right () ())) (right (right.left () ()) (right.right () ()))",
        "root\n"
        "    left\n"
        "        left.left\n"
        "        left.right\n"
        "    right\n"
        "        right.left\n"
        "        right.right\n");

    run_test("test 7. tree with skips in leaves",
        "root (left (left.left (left.left.left () ()) ()) ()) ()",
        "root\n"
        "    left\n"
        "        left.left\n"
        "            left.left.left\n");

    run_test("test 8. tree with only left side",
        "root (left (left.left (left.left.left () ()) ()) ()) ()",
        "root\n"
        "    left\n"
        "        left.left\n"
        "            left.left.left\n");

    run_test("test 9. tree with only right side",
        "root () (right (right.right () (right.right.right () ())))",
        "root\n"
        "    right\n"
        "        right.right\n"
        "            right.right.right\n");

    run_test("test 10. deep tree",
        "root (left (left.left (left.left.left (left.left.left.left () ()) ()) ()) ()) (right (right.left (right.left.left (right.left.left.left () ()) ()) ()) ())",
        "root\n"
        "    left\n"
        "        left.left\n"
        "            left.left.left\n"
        "                left.left.left.left\n"
        "    right\n"
        "        right.left\n"
        "            right.left.left\n"
        "                right.left.left.left\n");

    printf("All tests passed!\n");

    return 0;
}
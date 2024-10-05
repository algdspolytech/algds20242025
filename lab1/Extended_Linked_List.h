#pragma once

typedef struct Node
{
    struct Node *next;
    int *data;
    int current_length;
} Node;
#ifdef __cplusplus
extern "C"
{
#endif
    Node *CreateList();
    void PrintList(Node *list);
    int InsertElement(Node *list, int index, int element);
    int FindIndexWithKey(Node *list, int key);
    int RemoveElementWithIndex(Node *list, int index);
    int *FindElementWithIndex(Node *list, int index);
    int CountElements(Node *list);
    Node *NextElement(Node *list);
    void DeleteList(Node *list);

#ifdef __cplusplus
}
#endif
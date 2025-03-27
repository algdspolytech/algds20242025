#include <iostream>
#include <algorithm>

struct ListNode {
    int value;
    int height;
    int subtreeSize;
    ListNode* left;
    ListNode* right;
};

int getHeight(ListNode* node);
int getSize(ListNode* node);
void updateNode(ListNode* node);
ListNode* rotateRight(ListNode* root);
ListNode* rotateLeft(ListNode* root);
int computeBalance(ListNode* node);
ListNode* rebalanceNode(ListNode* node);
ListNode* newNode(int value);
ListNode* insertAtPosition(ListNode* root, int value, int pos);
ListNode* findMinNode(ListNode* node);
ListNode* removeByValue(ListNode* root, int value);
ListNode* removeAtIndex(ListNode* root, int index);
ListNode* getNodeByIndex(ListNode* root, int index);
ListNode* findByKey(ListNode* root, int key);
ListNode* mergeTrees(ListNode* treeA, ListNode* treeB);
void inOrderPrint(ListNode* root);
void freeTree(ListNode* root);
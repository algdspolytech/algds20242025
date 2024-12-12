#include "header.h"

int main() {
    Node* root = NULL;
    int n, k;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        root = insert(root, value);
    }
    printf("Enter K: ");
    scanf("%d", &k);

    Node* kthSmallestNode = findKthSmallest(root, k);

    if (kthSmallestNode != NULL) {
        printf("K-th smaller element: %d\n", kthSmallestNode->data);
        if (KIsEven(kthSmallestNode)) {
            printLessThanK(root, kthSmallestNode->data);
        }
    }
    else {
        printf("There isn't K-th smaller element\n");
    }

    return 0;
}
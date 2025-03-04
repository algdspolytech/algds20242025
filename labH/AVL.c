#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 
#include "AVL.h"


// Ôóíêöèÿ ñîçäàíèÿ íîâîãî óçëà.
Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1; // Ëèñò èìååò âûñîòó 1.
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

// Âîçâðàùàåò âûñîòó óçëà (0, åñëè óçåë ðàâåí NULL).
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Âîçâðàùàåò ðàçìåð ïîääåðåâà (0, åñëè óçåë ðàâåí NULL).
int getSize(Node* node) {
    return node ? node->size : 0;
}

// Îáíîâëåíèå âûñîòû è ðàçìåðà óçëà íà îñíîâå åãî ïîòîìêîâ.
void update(Node* node) {
    if (node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        node->size = 1 + getSize(node->left) + getSize(node->right);
    }
}

// Ïðàâûé ïîâîðîò âîêðóã óçëà y.
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}

// Ëåâûé ïîâîðîò âîêðóã óçëà x.
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

// Ïîëó÷åíèå áàëàíñèðóþùåãî ôàêòîðà óçëà.
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Áàëàíñèðîâêà óçëà AVL-äåðåâà.
Node* balance(Node* node) {
    if (!node) return node;
    update(node);
    int b = getBalance(node);
    if (b > 1) {
        if (getBalance(node->left) < 0)
            node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (b < -1) {
        if (getBalance(node->right) > 0)
            node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

/*
  Ïîèñê k-ãî ýëåìåíòà â ñïèñêå (1-based íóìåðàöèÿ).
  Èñïîëüçóåò ïîëå size, ÷òî ïîçâîëÿåò çà O(log n) íàõîäèòü íóæíûé óçåë.
*/
Node* find_kth(Node* root, int k) {
    if (!root || k <= 0 || k > getSize(root))
        return NULL;
    int leftSize = getSize(root->left);
    if (k == leftSize + 1)
        return root;
    else if (k <= leftSize)
        return find_kth(root->left, k);
    else
        return find_kth(root->right, k - leftSize - 1);
}

/*
  Ïîèñê ýëåìåíòà ïî çíà÷åíèþ key.
  Òàê êàê äåðåâî íå óïîðÿäî÷åíî ïî çíà÷åíèþ, ïîèñê âûïîëíÿåòñÿ ïîëíûì îáõîäîì – O(n).
*/
Node* search_by_key(Node* root, int key) {
    if (!root)
        return NULL;
    if (root->key == key)
        return root;
    Node* found = search_by_key(root->left, key);
    if (found)
        return found;
    return search_by_key(root->right, key);
}

/*
  Âñòàâêà ýëåìåíòà ñî çíà÷åíèåì key â ïîçèöèþ pos (0-based èíäåêñ).
  Áëàãîäàðÿ ïîëþ size îïåðàöèÿ âûïîëíÿåòñÿ çà O(log n).
*/
Node* insert_at(Node* root, int pos, int key) {
    if (!root)
        return create_node(key);
    int leftSize = getSize(root->left);
    if (pos <= leftSize)
        root->left = insert_at(root->left, pos, key);
    else
        root->right = insert_at(root->right, pos - leftSize - 1, key);
    return balance(root);
}

/*
  Óäàëåíèå ýëåìåíòà, çàíèìàþùåãî ïîçèöèþ pos (0-based èíäåêñ).
  Îïåðàöèÿ âûïîëíÿåòñÿ çà O(log n).
*/
Node* delete_at(Node* root, int pos) {
    if (!root)
        return NULL;
    int leftSize = getSize(root->left);
    if (pos < leftSize) {
        root->left = delete_at(root->left, pos);
    }
    else if (pos > leftSize) {
        root->right = delete_at(root->right, pos - leftSize - 1);
    }
    else {
        // Óäàëÿåì òåêóùèé óçåë.
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }
        else {
            // Íàõîäèì ìèíèìàëüíûé óçåë â ïðàâîì ïîääåðåâå (in-order ïðååìíèê).
            Node* temp = root->right;
            while (temp->left)
                temp = temp->left;
            root->key = temp->key;
            // Óäàëÿåì ïðååìíèêà.
            root->right = delete_at(root->right, 0);
        }
    }
    return balance(root);
}

/*
  Ôóíêöèÿ extract_max èçâëåêàåò (óäàëÿåò) ìàêñèìàëüíûé ýëåìåíò (ïðàâûé êðàéíèé óçåë)
  èç äåðåâà è ïåðåäàåò åãî ÷åðåç ïàðàìåòð max_node.
*/
Node* extract_max(Node* root, Node** max_node) {
    if (!root->right) {
        *max_node = root;
        return root->left;
    }
    else {
        root->right = extract_max(root->right, max_node);
        return balance(root);
    }
}

/*
  Îïåðàöèÿ ñöåïëåíèÿ äâóõ ñïèñêîâ, ïðåäñòàâëåííûõ AVL-äåðåâüÿìè.
  Ïðåäïîëàãàåòñÿ, ÷òî âñå ýëåìåíòû ïåðâîãî ñïèñêà èäóò ïåðåä ýëåìåíòàìè âòîðîãî.
  Ñëîæíîñòü: O(log n)
*/
Node* join_trees(Node* t1, Node* t2) {
    if (!t1) return t2;
    if (!t2) return t1;
    if (getHeight(t1) > getHeight(t2) + 1) {
        t1->right = join_trees(t1->right, t2);
        return balance(t1);
    }
    else if (getHeight(t2) > getHeight(t1) + 1) {
        t2->left = join_trees(t1, t2->left);
        return balance(t2);
    }
    else {
        Node* max = NULL;
        t1 = extract_max(t1, &max);
        max->left = t1;
        max->right = t2;
        return balance(max);
    }
}

// Ôóíêöèÿ in-order îáõîäà äëÿ âûâîäà ýëåìåíòîâ äåðåâà â âèäå ñïèñêà.
void inorder_print(Node* root) {
    if (!root) return;
    inorder_print(root->left);
    printf("%d ", root->key);
    inorder_print(root->right);
}

int main(void) {
    setlocale(LC_CTYPE, "Russian");
    Node* list = NULL;

    // Âñòàâëÿåì ýëåìåíòû â ñïèñîê.
    list = insert_at(list, 0, 10);
    list = insert_at(list, 1, 20);
    list = insert_at(list, 2, 30);
    list = insert_at(list, 1, 15); // Âñòàâëÿåì 15 íà ïîçèöèþ 1.

    printf("Ñïèñîê ïîñëå âñòàâîê (inorder): ");
    inorder_print(list);
    printf("\n");

    // Ïîèñê 3-ãî ýëåìåíòà (1-based íóìåðàöèÿ).
    Node* kth = find_kth(list, 3);
    if (kth)
        printf("3-é ýëåìåíò: %d\n", kth->key);

    // Ïîèñê ýëåìåíòà ïî çíà÷åíèþ.
    Node* found = search_by_key(list, 20);
    if (found)
        printf("Ýëåìåíò ñî çíà÷åíèåì 20 íàéäåí.\n");

    // Óäàëÿåì âòîðîé ýëåìåíò (ïîçèöèÿ 1, 0-based).
    list = delete_at(list, 1);
    printf("Ñïèñîê ïîñëå óäàëåíèÿ âòîðîãî ýëåìåíòà: ");
    inorder_print(list);
    printf("\n");

    // Ñîçäàåì âòîðîé ñïèñîê.
    Node* list2 = NULL;
    list2 = insert_at(list2, 0, 40);
    list2 = insert_at(list2, 1, 50);

    // Ñöåïëÿåì äâà ñïèñêà: ýëåìåíòû ïåðâîãî ñïèñêà èäóò ïåðåä ýëåìåíòàìè âòîðîãî.
    Node* joined = join_trees(list, list2);
    printf("Ñöåïë¸ííûé ñïèñîê: ");
    inorder_print(joined);
    printf("\n");

    return 0;
}

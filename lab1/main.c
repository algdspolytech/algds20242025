#include <stdio.h>
#include <stdlib.h>
#include "labH.h"

// Функция для создания нового узла
SplayNode *newNode(int key) {
  SplayNode *node = (SplayNode *)malloc(sizeof(SplayNode));
  node->key = key;
  node->left = node->right = NULL;
  return node;
}

// Функция для правого вращения
SplayNode *rightRotate(SplayNode *y) {
  SplayNode *x = y->left;
  SplayNode *T2 = x->right;

  // Выполнение вращения
  x->right = y;
  y->left = T2;

  return x;
}

// Функция для левого вращения
SplayNode *leftRotate(SplayNode *x) {
  SplayNode *y = x->right;
  SplayNode *T2 = y->left;

  // Выполнение вращения
  y->left = x;
  x->right = T2;

  return y;
}

// Функция Splay: Перемещает узел с ключом 'key' в корень дерева.
SplayNode *splay(SplayNode *root, int key) {
  if (root == NULL || root->key == key)
    return root;

  // Ключ находится в левом поддереве
  if (key < root->key) {
    // Ключ не найден в левом поддереве
    if (root->left == NULL)
      return root;

    // Zig-Zig (Left Left)
    if (key < root->left->key) {
      root->left->left = splay(root->left->left, key);
      root = rightRotate(root);
    } else if (key > root->left->key) { // Zig-Zag (Left Right)
      root->left->right = splay(root->left->right, key);
      if (root->left->right != NULL)
        root->left = leftRotate(root->left);
    }

    return (root->left == NULL) ? root : rightRotate(root);
  } else { // Ключ находится в правом поддереве
    // Ключ не найден в правом поддереве
    if (root->right == NULL)
      return root;

    // Zag-Zig (Right Left)
    if (key < root->right->key) {
      root->right->left = splay(root->right->left, key);
      if (root->right->left != NULL)
        root->right = rightRotate(root->right);
    } else if (key > root->right->key) { // Zag-Zag (Right Right)
      root->right->right = splay(root->right->right, key);
      root = leftRotate(root);
    }

    return (root->right == NULL) ? root : leftRotate(root);
  }
}

// Функция поиска:  Перемещает узел с ключом 'key' в корень дерева и возвращает его.
SplayNode *search(SplayNode *root, int key) {
  return splay(root, key);
}

// Функция вставки узла с ключом 'key'
SplayNode *insert(SplayNode *root, int key) {
  SplayNode *node = newNode(key);

  if (root == NULL) {
    return node;
  }

  // Splay для ключа, чтобы корень был ближайшим к ключу вставки.
  root = splay(root, key);

  // Если ключ уже существует, ничего не вставляем. Можно изменить логику.
  if (root->key == key) {
    free(node);
    return root; // Или  return root; // Можно изменить логику.
  }

  if (key < root->key) {
    node->right = root;
    node->left = root->left;
    root->left = NULL;
  } else {
    node->left = root;
    node->right = root->right;
    root->right = NULL;
  }
  return node;
}

// Функция удаления узла с ключом 'key'
SplayNode *deleteNode(SplayNode *root, int key) {
  SplayNode *temp;

  if (root == NULL)
    return NULL;

  // Splay для ключа
  root = splay(root, key);

  // Если ключ не найден
  if (root->key != key)
    return root;

  // Если ключ найден
  if (root->left == NULL) {
    temp = root;
    root = root->right;
  } else {
    temp = root;
    root = splay(root->left, key); // Splay максимальный элемент в левом поддереве
    root->right = temp->right;
  }

  free(temp);
  return root;
}

// Функция для inorder обхода дерева (для отладки)
void inorder(SplayNode *root) {
  if (root != NULL) {
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
  }
}

// Функция для освобождения памяти, занимаемой деревом
void freeTree(SplayNode *root) {
  if (root != NULL) {
    freeTree(root->left);
    freeTree(root->right);
    free(root);
  }
}
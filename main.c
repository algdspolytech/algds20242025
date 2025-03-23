#include "assert.h"
#include "splaythree.h"
#include <stdio.h>

/*------------insert()----------*/
void instert_Standart_NewRoot() {
  Node root = {5, NULL, NULL, NULL};
  Node *root_ad = &root;
  Node left = {3, NULL, NULL, &root};
  root.left = &left;

  root_ad = insert(&root, 6);

  assert(root_ad->value == 6);
}
/*----------------------------------*/

void instert_Emptyroot_NULL() {

  Node *root_ad = NULL;

  root_ad = insert(root_ad, 6);

  assert(root_ad == NULL);
}

void instert_Duplicat_InputRoot() {
  Node root = {5, NULL, NULL, NULL};
  Node *root_ad = &root;
  Node left = {3, NULL, NULL, &root};
  root.left = &left;

  root_ad = insert(&root, 5);

  assert(root_ad == &root);
}

/*-------------search()---------------------*/
void search_Standart_NewRootWithNeededValue() {
  Node root = {5, NULL, NULL, NULL};
  Node *root_ad = &root;
  Node left = {3, NULL, NULL, &root};
  Node right = {6, NULL, NULL, root_ad};
  root.left = &left;
  root.right = &right;

  root_ad = search(root_ad, 3);
  assert(root_ad == &left);
}

void search_NotExistedValue_6() {

  Node root = {5, NULL, NULL, NULL};
  Node *root_ad = &root;
  Node left = {3, NULL, NULL, &root};
  Node right = {6, NULL, NULL, root_ad};
  root.left = &left;
  root.right = &right;

  root_ad = search(root_ad, 7);

  assert(root_ad->value == 6);
}

void search_EmptyRoot_NULL() {

  Node *root_ad = NULL;

  root_ad = search(root_ad, 3);
  assert(root_ad == NULL);
}
/*----------------------------------*/

/*-------------erase()--------------*/
void erase_NoChildren_InputRoot() {
  Node root = {5, NULL, NULL, NULL};
  Node *root_ad = &root;
  Node left = {3, NULL, NULL, root_ad};

  Node *right = malloc(sizeof(Node));
  (*right).value = 6;
  (*right).left = NULL;
  (*right).right = NULL;
  (*right).parent = root_ad;

  root.left = &left;
  root.right = right;
  root_ad = erase(root_ad, 6);
  assert(root_ad == &root);
}

void erase_OnlyLeftChildren_InputRoot() {
  Node root = {5, NULL, NULL, NULL};
  Node *root_ad = &root;
  Node left = {3, NULL, NULL, root_ad};

  Node *right = malloc(sizeof(Node));
  (*right).value = 7;

  Node child = {6, NULL, NULL, right};
  (*right).left = &child;

  (*right).right = NULL;
  (*right).parent = root_ad;

  root.left = &left;
  root.right = right;
  root_ad = erase(root_ad, 7);
  assert(root_ad->right == &child);
}

void erase_OnlyRightChildren_NodeWith8() {
  Node root = {5, NULL, NULL, NULL};
  Node *root_ad = &root;
  Node left = {3, NULL, NULL, root_ad};

  Node *right = malloc(sizeof(Node));
  (*right).value = 7;

  Node child = {8, NULL, NULL, right};
  (*right).right = &child;

  (*right).left = NULL;
  (*right).parent = root_ad;

  root.left = &left;
  root.right = right;
  root_ad = erase(root_ad, 7);
  assert(root_ad->value == 8);
}

void erase_CoupleChildren_NodeWith6() {
  Node root = {5, NULL, NULL, NULL};
  Node *root_ad = &root;
  Node left = {3, NULL, NULL, root_ad};

  Node *right = malloc(sizeof(Node));
  (*right).value = 7;

  Node child_r = {8, NULL, NULL, right};
  (*right).right = &child_r;
  Node child_l = {6, NULL, NULL, right};
  (*right).right = &child_l;

  (*right).left = NULL;
  (*right).parent = root_ad;

  root.left = &left;
  root.right = right;
  root_ad = erase(root_ad, 7);
  assert(root_ad->value == 6);
}

void erase_NUllRoot_NULL() {
  Node *root_ad = NULL;

  root_ad = erase(root_ad, 1);

  assert(root_ad == NULL);
}
/*----------------------------------*/

int main() {

  instert_Standart_NewRoot();
  instert_Emptyroot_NULL();
  instert_Duplicat_InputRoot();

  search_Standart_NewRootWithNeededValue();
  search_NotExistedValue_6();
  search_EmptyRoot_NULL();

  erase_NoChildren_InputRoot();
  erase_OnlyLeftChildren_InputRoot();
  erase_OnlyRightChildren_NodeWith8();
  erase_CoupleChildren_NodeWith6();
  erase_NUllRoot_NULL();

  return 0;
}
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct Tree {
  int data;
  struct Tree *left;
  struct Tree *right;
} tree;

/*
    FUNCTIONS ZONE
*/
/*⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛*/
tree *set(int data) {
  tree *tmp = (tree *)malloc(sizeof(tree));

  tmp->data = data;
  tmp->left = NULL;
  tmp->right = NULL;

  return tmp;
}

void add(tree **t, int data) {
  if (*t == NULL) {
    *t = set(data);
  } else {
    tree *cur = *t;
    if (data >= cur->data) {
      if (cur->right == NULL) {
        cur->right = set(data);
      } else {
        add(&(cur->right), data);
      }
    } else {
      if (cur->left == NULL) {
        cur->left = set(data);
      } else {
        add(&(cur->left), data);
      }
    }
  }
}

int findK(tree *t, int k, int *counter) {
  if (t == NULL || *counter >= k) {
    return 0;
  }

  int r = findK(t->left, k, counter);

  if (r != 0)
    return r;

  *counter = *counter + 1;
  if (*counter == k) {
    //*result = t->data;
    return t->data;
  }

  findK(t->right, k, counter);
}

void printToK(tree *tr, int k, int *counter) {
  if (tr == NULL || *counter >= k) {
    return;
  }

  printToK(tr->left, k, counter);

  *counter = *counter + 1;
  if (*counter < k) {
    printf("%d ", tr->data);
  }

  printToK(tr->right, k, counter);
}

/*Finally....*/
void QuestFunction(tree *t, int k) {
  int count = 0;

  int res = 0;
  res = findK(t, k, &count);
  printf("Founded element: %d\n", res);
  if (res % 2 == 0) {
    count = 0;
    printToK(t, k, &count);
    printf("\n");
  }
}
/*⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛*/

/*
    TESTS ZONE
*/
/*⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛*/

void set_Standart_settedCorrectValue() {
  tree *res = set(1);
  assert(res->data == 1);
}

void add_AddingIntoEmptyTree_correctAdding() {
  tree *t = NULL;
  add(&t, 1);
  assert(t->data == 1);
}

void add_OnlyRootElementLessThanRoot_AddingToLeft() {
  tree *t = malloc(sizeof(tree));
  t->data = 1;
  t->left = NULL;
  t->right = NULL;

  add(&t, -1);
  assert(t->left->data == -1);
}

void add_OnlyRootElementMoreThanRoot_AddingTRight() {
  tree *t = malloc(sizeof(tree));
  t->data = 1;
  t->left = NULL;
  t->right = NULL;

  add(&t, 2);
  assert(t->right->data == 2);
}

void add_OnlyRootElementEqualRoot_AddingTRight() {
  tree *t = malloc(sizeof(tree));
  t->data = 1;
  t->left = NULL;
  t->right = NULL;

  add(&t, 1);
  assert(t->right->data == 1);
}

void findK_KEqual1_return1() {
  tree *t = malloc(sizeof(tree));
  t->data = 2;
  t->left = malloc(sizeof(tree));
  t->right = malloc(sizeof(tree));

  t->left->data = 1;
  t->left->left = NULL;
  t->left->right = NULL;

  t->right->data = 3;
  t->right->left = NULL;
  t->right->right = NULL;

  int count = 0;
  int res = 0;
  res = findK(t, 1, &count);
  assert(res == 1);
}

void findK_KEqualAmountOfElements_return3() {
  tree *t = malloc(sizeof(tree));
  t->data = 2;
  t->left = malloc(sizeof(tree));
  t->right = malloc(sizeof(tree));

  t->left->data = 1;
  t->left->left = NULL;
  t->left->right = NULL;

  t->right->data = 3;
  t->right->left = NULL;
  t->right->right = NULL;

  int count = 0;
  int res = 0;
  res = findK(t, 3, &count);
  assert(res == 3);
}

void findK_KEqual0_return0() {
  tree *t = malloc(sizeof(tree));
  t->data = 2;
  t->left = malloc(sizeof(tree));
  t->right = malloc(sizeof(tree));

  t->left->data = 1;
  t->left->left = NULL;
  t->left->right = NULL;

  t->right->data = 3;
  t->right->left = NULL;
  t->right->right = NULL;

  int count = 0;
  int res = 0;
  res = findK(t, 0, &count);
  assert(res == 0);
}

void findK_KMoreThanAmountOfElements_return0() {
  tree *t = malloc(sizeof(tree));
  t->data = 2;
  t->left = malloc(sizeof(tree));
  t->right = malloc(sizeof(tree));

  t->left->data = 1;
  t->left->left = NULL;
  t->left->right = NULL;

  t->right->data = 3;
  t->right->left = NULL;
  t->right->right = NULL;

  int count = 0;
  int res = 0;
  res = findK(t, 4, &count);
  assert(res == 0);
}

void findK_EmptyTree_return0() {
  tree *t = NULL;

  int count = 0;
  int res = 0;
  res = findK(t, 1, &count);
  assert(res == 0);
}

void RunAllTests() {
  set_Standart_settedCorrectValue();

  add_AddingIntoEmptyTree_correctAdding();
  add_OnlyRootElementLessThanRoot_AddingToLeft();
  add_OnlyRootElementMoreThanRoot_AddingTRight();
  add_OnlyRootElementEqualRoot_AddingTRight();

  findK_KEqual1_return1();
  findK_KEqualAmountOfElements_return3();
  findK_KEqual0_return0();
  findK_KMoreThanAmountOfElements_return0();
  findK_EmptyTree_return0();
}
/*⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛*/

/*
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣶⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⡤⠾⠋⠀⠙⢦⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣀⣀⡀⠀⣠⡶⠋⠁⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠶⣤⣀⠀⠀⠀⠀⡄⠀⠀⠀
⠀⠀⠀⣼⠟⣯⡙⣿⡭⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⡶⠞⠋⣿⠀⠀⠀
⡀⠀⠀⣿⠉⠻⠀⠈⠀⠀⠀⢾⠆⢀⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡟⠀⠀⠀
⠉⠓⠒⢻⣦⣤⣀⣀⠀⠀⠀⠀⠀⠀⠉⠛⠃⠀⠀⢠⣦⡀⠀⠀⠀⠀⠀⠀⣼⠁⠀⠀⠀
⠀⣠⠚⠉⠁⠀⠀⠉⠉⠻⢗⠲⠦⢤⣄⣀⡀⠀⠀⠈⠉⠀⠀⠀⠀⠀⠀⠀⠘⣷⠀⠀⠀
⠀⣧⡀⠀⠀⠀⠀⠀⠀⠀⣸⣧⠶⠒⠚⠛⠛⣻⠂⠀⠀⠀⠀⣀⣀⠀⠀⠀⠀⠸⡇⠀⠀
⠀⢻⣝⠓⠦⠤⢤⢤⠶⣚⣿⡇⠀⠀⠀⢀⡼⢛⡷⡖⠒⠒⠛⢅⠈⠉⠙⠒⠲⠤⢧⣄⣀
⠀⠈⣏⠹⡟⠒⢲⠚⠋⡟⢹⣧⡀⠀⠀⠀⠀⠊⠀⠇⠀⠀⠀⠈⡇⠀⠀⠀⠀⠀⠀⠀⠉
⠀⠀⢸⡄⡇⠀⢸⠀⢠⡇⠘⣷⡙⠢⣄⣀⠀⠀⠀⠀⠀⢀⣠⡾⠁⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢳⣼⣀⣸⣇⣸⡦⣤⡇⡏⠓⠦⣬⣍⣙⣛⣛⡯⣽⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠈⠙⠛⠛⠁⠀⠈⣿⡇⠀⠀⡟⠀⠀⢀⡏⢠⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢷⣤⣰⠁⠀⢀⣞⣠⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠛⠛⠛⠋⠁⠀  */

int main() {

  /*Example of work*/
  tree *t = NULL;
  add(&t, -1);
  add(&t, -2);
  add(&t, -3);
  add(&t, -4);
  add(&t, 5);
  add(&t, 6);
  add(&t, 7);
  add(&t, 8);

  QuestFunction(t, 6);

  RunAllTests();

  return 0;
}

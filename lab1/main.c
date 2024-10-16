#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "test.h"

int main() {
  FILE *f1 = fopen("input1.txt", "r");
  FILE *f2 = fopen("input2.txt", "r");
  FILE *outp = fopen("output.txt", "w");

  Node l1 = {NULL, NULL};
  Node l2 = {NULL, NULL};

  char s[20];
  while (fscanf(f1, "%s", s) == 1) {
    push(&l1, s);
  }

  while (fscanf(f2, "%s", s) == 1) {
    push(&l2, s);
  }

  fclose(f1);
  fclose(f2);

  merge(&l1, &l2);

  Node *cur = l1.next;
  while (cur != NULL) {
    fprintf(outp, "%s\n", cur->val);
    cur = cur->next;
  }
  fclose(outp);

  runAllTests();

  destroyList(&l1);
  destroyList(&l2);

  return 0;
}
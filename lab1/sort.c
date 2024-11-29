#include "sort.h"

void push(Node *head, char *element) {
  Node *cur = head;

  int flag = 1;
  while (flag) {

    if (cur == head && cur->next == NULL) {
      flag = 0;
      cur->next = (Node *)malloc(sizeof(Node));
      cur->next->val = strdup(element);
      cur->next->next = NULL;
    }

    if (flag) {
      if (cur != head) {
        if (cur->next != NULL) {
          if (compareWords(cur->val, element) == -1 &&
              compareWords(element, cur->next->val) != 1) {
            insertAfter(cur, element);
            flag = 0;
          }
        } else {
          insertAfter(cur, element);
          flag = 0;
        }
      } else {
        if (compareWords(element, cur->next->val) != 1) {
          insertAfter(cur, element);
          flag = 0;
        }
      }
    }

    if (flag)
      cur = cur->next;
  }
}

void pop(Node *head, char *st) {
  Node *cur = head;
  Node *prev = NULL;
  while (cur->next != NULL) {
    prev = cur;
    cur = cur->next;
  }
  if (cur != head) {
    strcpy(st, cur->val);

    free(cur);

    if (prev != NULL) {
      prev->next = NULL;
    }
  } else {
    st = "\0";
  }
}

int compareWords(char *a, char *b) { return strcmp(a, b); }

void sortList(Node *head) {
  Node *cur = head->next;
  Node *prev = NULL;
  while (cur != NULL) {
    if (prev != NULL) {

      if (compareWords(prev->val, cur->val) == 1) {
        char *t = strdup(prev->val);
        prev->val = strdup(cur->val);
        cur->val = strdup(t);

        cur = prev;
      }
    }
    prev = cur;
    cur = cur->next;
  }
}

void insertAfter(Node *goal, char *val) {
  Node *oldNext = goal->next;

  goal->next = (Node *)malloc(sizeof(Node));

  goal->next->val = strdup(val);
  goal->next->next = oldNext;
}

void merge(Node *h1, Node *h2) {
  char buf[20];
  while (h2->next != NULL) {
    pop(h2, buf);

    Node *cur = h1->next;
    Node *prev = NULL;
    int flag = 0;
    while (cur != NULL && flag == 0) {
      if (prev != NULL) {
        if (compareWords(prev->val, buf) == -1 &&
            compareWords(cur->val, buf) == 1) {

          insertAfter(prev, buf);
          flag = 1;
        } else if (compareWords(prev->val, buf) == 1) {
          insertAfter(h1, buf);
          flag = 1;
        }
      }

      prev = cur;
      cur = cur->next;
    }
    if (flag == 0) {
      push(h1, buf);
    }
  }
}

void showList(Node *head) {
  Node *cur = head->next;
  while (cur != NULL) {
    printf("%s\n", cur->val);
    cur = cur->next;
  }
}

void destroyList(Node *head) {
  Node *cur = head->next;
  while (cur != NULL) {
    Node *prev = cur;
    cur = cur->next;
    free(prev);
  }
}
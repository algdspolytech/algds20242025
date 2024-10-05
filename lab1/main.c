#include <stdio.h>
#include <stdlib.h>

#include "Extended_Linked_List.h"
#define MAXLENGTH 10

void SwapInt(int *a, int *b) {
  int *c = a;
  a = b;
  b = c;
}

void RemoveElementFromArray(int *array, int length, int index) {
  for (int i = 0; i < length - index - 1; i++) {
    array[index + i] = array[index + i + 1];
  }
}

Node *CreateList() {
  Node *head = malloc(sizeof(Node));
  if (!head) {
    printf("Error while giving memory");
    exit(1);
  }
  head->current_length = 0;
  head->data = malloc(sizeof(int) * MAXLENGTH);
  if (!head->data) {
    printf("Error while giving memory");
    exit(1);
  }
  head->next = NULL;

  return head;
}
void InsertNodeAfter(Node *cur_node) {
  Node *temp = CreateList();
  temp->next = cur_node->next;
  cur_node->next = temp;
}

int InsertElement(Node *list, int index, int element) {
  int counter = 0;
  Node *temp = list;
  while (temp->next != NULL && counter != index) {
    temp = temp->next;
    counter++;
  }
  if (counter != index) {
    return 1;
  }
  if (temp->current_length == MAXLENGTH) {
    InsertNodeAfter(temp);
    for (int i = 0; i < MAXLENGTH / 2; i++) {
      temp->next->data[i] = temp->data[(MAXLENGTH / 2 + MAXLENGTH % 2) + i];
      temp->data[(MAXLENGTH / 2 + MAXLENGTH % 2) + i] = 0;
      temp->current_length--;
      temp->next->current_length++;
    }
  }
  temp->data[temp->current_length] = element;
  temp->current_length++;
  return 0;
}

int FindIndexWithKey(Node *list, int key) {
  Node *temp = list;
  int index = 0;
  while (temp) {
    for (int i = 0; i < temp->current_length; i++) {
      if (temp->data[i] == key) {
        return index * MAXLENGTH + i;
      }
    }

    temp = temp->next;
    index++;
  }
  return -1;
}

int RemoveElementWithIndex(Node *list, int index) {
  Node *temp = list;
  int counter = 0;
  if (index < 0) {
    return -1;
  }
  while (temp) {
    if (counter == index / MAXLENGTH) {
      if (temp->current_length > index % MAXLENGTH) {
        RemoveElementFromArray(temp->data, temp->current_length,
                               index % MAXLENGTH);
        temp->current_length--;
        break;
      } else {
        return 1;
      }
    }

    temp = temp->next;
    counter++;
  }
  if (counter != index / MAXLENGTH) {
    return 1;
  }
  while (temp->current_length < MAXLENGTH / 2 + MAXLENGTH % 2) {
    for (int i = 0; i < temp->next->current_length; i++) {
      temp->data[temp->current_length] = temp->next->data[0];
      RemoveElementFromArray(temp->next->data, temp->next->current_length, 0);
      temp->current_length++;
      temp->next->current_length--;
    }
  }
  if (temp->next->current_length < MAXLENGTH / 2 + MAXLENGTH % 2) {
    for (int i = 0; i < temp->next->current_length; i++) {
      temp->data[temp->current_length] = temp->next->data[i];
      temp->current_length++;
    }
    Node *t = temp->next;
    temp->next = t->next;
    free(t->data);
    free(t);
  }
  return 0;
}

int *FindElementWithIndex(Node *list, int index) {
  Node *temp = list;
  int counter = 0;
  int *result = malloc(sizeof(int) * 2);
  if (index < 0) {
    result[1] = -1;
    return result;
  }
  while (temp) {
    if (counter == index / MAXLENGTH) {
      result[0] = temp->data[index % MAXLENGTH];
      result[1] = 0;
      return result;
    }
    temp = temp->next;
    counter++;
  }
  result[1] = -1;
  return result;
}

void PrintList(Node *list) {
  Node *temp = list;
  while (temp) {
    for (int i = 0; i < temp->current_length; i++) {
      printf("%d ", temp->data[i]);
    }
    temp = temp->next;
    printf("\n");
  }
}

int CountElements(Node *list) {
  int result = 0;
  Node *temp = list;

  while (temp) {
    result += temp->current_length;

    temp = temp->next;
  }

  return result;
}

Node *NextElement(Node *list) {
  if (!list) {
    return NULL;
  }
  return list->next;
}

void DeleteList(Node *head) {
  while (head) {
    free(head->data);
    Node *temp = head;
    head = head->next;
    free(temp);
  }
}
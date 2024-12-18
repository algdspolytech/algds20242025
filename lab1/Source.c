#include "xor_list.h"

int main() {
    Node* head = NULL;

    // ��������� �������� � ������
    add(&head, "Hello");
    add(&head, "World");
    add(&head, "XOR");
    add(&head, "List");

    // ������� ������
    printList(head);

    // ����� ��������
    Node* found = find(head, "World");
    if (found) {
        printf("������ �������: %s\n", found->data);
    }

    // �������� �� �����
    deleteByKey(&head, "XOR");
    printf("����� �������� �������� �� �����:\n");
    printList(head);

    // �������� �� ������
    if (found) {
        deleteByAddress(&head, found);
        printf("����� �������� �������� �� ������:\n");
        printList(head);
    }

    // ����������� ������
    freeList(head);

    return 0;
}
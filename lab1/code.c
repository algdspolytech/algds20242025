#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* slots;
    int* flags;
    int count;
    int cap;
} LinearSet;

// ������� ���-������� ��� ����� �����
unsigned long hash(unsigned long x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    return (x >> 16) ^ x;
}

// ������� ����� ����� � �������� ��������
LinearSet* create_set(int cap) {
    LinearSet* set = malloc(sizeof(LinearSet));
    if (!set) {
        perror("Failed to allocate set");
        exit(EXIT_FAILURE);
    }
    set->slots = malloc(sizeof(int) * cap);
    set->flags = malloc(sizeof(int) * cap);
    if (!set->slots || !set->flags) {
        perror("Failed to allocate memory");
        free(set);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < cap; ++i)
        set->flags[i] = 0;
    set->cap = cap;
    set->count = 0;
    return set;
}

// ����������� ������ ������
void free_set(LinearSet* set) {
    if (!set)
        return;
    free(set->slots);
    free(set->flags);
    free(set);
}

// ������� ������� ��� �����: ���������� ������ � ������������� found=1 ���� ���� ����������
int find_position(LinearSet* set, int key, int* found) {
    unsigned long h = hash((unsigned long)key);
    int idx = h % set->cap;
    int first_deleted = -1;

    for (int i = 0; i < set->cap; ++i) {
        int pos = (idx + i) % set->cap;

        if (set->flags[pos] == 1 && set->slots[pos] == key) {
            *found = 1;
            return pos; // ����� ������������ �������
        }
        if (set->flags[pos] == 0) {
            *found = 0;
            // ���� ���� �������� ����, ���������� ��� ��� �������
            return (first_deleted != -1) ? first_deleted : pos;
        }
        if (set->flags[pos] == 2 && first_deleted == -1)
            first_deleted = pos; // ���������� ������ �������� ����
    }
    *found = 0;
    return -1; // ������� ��������� ��� �� ������� ���������� �����
}

// ��������� ������� ��� �������������
void reallocate(LinearSet* set) {
    int new_cap = set->cap * 2 + 1; // ����������� �������
    LinearSet* new_set = create_set(new_cap);

    // ��������� ��� �������� �������� � ����� �������
    for (int i = 0; i < set->cap; ++i) {
        if (set->flags[i] == 1) {
            int dummy_found;
            int pos = find_position(new_set, set->slots[i], &dummy_found);
            new_set->slots[pos] = set->slots[i];
            new_set->flags[pos] = 1;
            new_set->count++;
        }
    }

    // ����������� ������ ������� � ������������� ���������
    free(set->slots);
    free(set->flags);

    set->slots = new_set->slots;
    set->flags = new_set->flags;
    set->cap = new_set->cap;
    set->count = new_set->count;

    // �� ����������� new_set, ��� ��� ��� ��������� ������ ����������� ��������� ������
}

// ��������� ������� � ���������
void add(LinearSet* set, int key) {
    // �������� ������������� ���������� ������� �� ��������
    if ((double)(set->count + 1) / set->cap > 0.6)
        reallocate(set);

    int found;
    int pos = find_position(set, key, &found);

    if (!found && pos != -1) {
        set->slots[pos] = key;
        set->flags[pos] = 1;
        set->count++;
    }
}

// ������� ������� �� ���������
void del(LinearSet* set, int key) {
    int found;
    int pos = find_position(set, key, &found);

    if (found && pos != -1 && set->flags[pos] == 1) {
        set->flags[pos] = 2; // �������� ��� �������� ����
        set->count--;
    }
}

// ��������� ������� �������� � ���������
int find(LinearSet* set, int key) {
    int found;
    find_position(set, key, &found);
    return found;
}

int main(void) {
    LinearSet* set = create_set(100);
    char op;
    int key;

    while (scanf(" %c %d", &op, &key) == 2) {
        switch (op) {
        case 'a': // �������� �������
            add(set, key);
            break;
        case 'r': // ������� �������
            del(set, key);
            break;
        case 'f': // ��������� ������� ��������
            printf("%s\n", find(set, key) ? "yes" : "no");
            break;
        default:
            break;
        }
    }

    free_set(set);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 2124679
#define MAX_KEY_LEN 2048

typedef enum { EMPTY, OCCUPIED, DELETED } SlotStatus;

static char *table[TABLE_SIZE];
static SlotStatus status[TABLE_SIZE] = { EMPTY };
static unsigned int h1slots[TABLE_SIZE];
static unsigned int h2slots[TABLE_SIZE];

unsigned int hash1(const char *s) {
    unsigned int h = 0;
    while (*s) {
        h = (h << 5) ^ (h >> 27) ^ (unsigned char)*s++;
    }
    return h % TABLE_SIZE;
}

unsigned int hash2(const char *s) {
    unsigned int h = 0;
    while (*s) {
        h = (h << 7) ^ (h >> 25) ^ (unsigned char)*s++;
    }
    return (h % (TABLE_SIZE - 1)) + 1;
}

static unsigned int mod_inv(unsigned int a, unsigned int m) {
    long long m0 = m, x0 = 0, x1 = 1, aa = a;
    if (m == 1) return 0;
    while (aa > 1) {
        long long q = aa / m;
        long long t = m; m = aa % m; aa = t;
        t = x0; x0 = x1 - q * x0; x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return (unsigned int)x1;
}

int ht_find(const char *key) {
    unsigned int h1 = hash1(key), h2 = hash2(key);
    for (unsigned int i = 0; i < TABLE_SIZE; i++) {
        unsigned int idx = (h1 + i * h2) % TABLE_SIZE;
        if (status[idx] == EMPTY)       return -1;
        if (status[idx] == OCCUPIED &&
            strcmp(table[idx], key) == 0)
            return (int)idx;
    }
    return -1;
}

void ht_remove(const char *key) {
    int pos = ht_find(key);
    if (pos >= 0) {
        free(table[pos]);
        table[pos] = NULL;
        status[pos] = DELETED;
    }
}

void ht_insert(const char *key) {
    if (ht_find(key) >= 0) return;

    char *curr_key = strdup(key);
    unsigned int curr_h1 = hash1(curr_key);
    unsigned int curr_h2 = hash2(curr_key);
    unsigned int curr_d  = 0;

    while (curr_d < TABLE_SIZE) {
        unsigned int idx = (curr_h1 + curr_d * curr_h2) % TABLE_SIZE;
        if (status[idx] == OCCUPIED) {
            unsigned int eh1 = h1slots[idx];
            unsigned int eh2 = h2slots[idx];
            unsigned int inv  = mod_inv(eh2, TABLE_SIZE);
            unsigned int diff = (idx + TABLE_SIZE - eh1) % TABLE_SIZE;
            unsigned int d_e  = (unsigned long long)diff * inv % TABLE_SIZE;

            if (d_e < curr_d) {
                char *tmp = table[idx];
                table[idx] = curr_key;
                h1slots[idx] = curr_h1;
                h2slots[idx] = curr_h2;
                curr_key = tmp;
                curr_h1  = eh1;
                curr_h2  = eh2;
                curr_d   = d_e + 1;
                continue;
            }
        } else {
            table[idx]    = curr_key;
            status[idx]   = OCCUPIED;
            h1slots[idx]  = curr_h1;
            h2slots[idx]  = curr_h2;
            return;
        }
        curr_d++;
    }
    fprintf(stderr, "Error: full, cannot insert \"%s\"\n", key);
    free(curr_key);
}

int main(void) {
    char op, key[MAX_KEY_LEN];
    while (scanf(" %c %1023s", &op, key) == 2) {
        switch (op) {
            case 'a': ht_insert(key);  break;
            case 'r': ht_remove(key);  break;
            case 'f':
                printf("%s\n", ht_find(key) >= 0 ? "yes" : "no");
                break;
        }
    }
    return 0;
}
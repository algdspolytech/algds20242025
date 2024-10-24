#include "main.h"
int main() {
    Item list[MAX_LIST_SIZE];
    int size = 0;
    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Error");
        return EXIT_FAILURE;
    }
    while (size < MAX_LIST_SIZE && !feof(file)) {
        Item newItem;
        if (scan_check) {
            insert_sorted(list, &size, newItem);
        }
    }
    fclose(file);
    print_list(list, size);
    int key;
    printf("Enter keyword: ");
    scanf("%d", &key);
    if (!find_word_by_key(list, size, key)) {
        printf("Word for keyword %d didnt find \n", key);
    }
    return 0;
}